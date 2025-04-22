import tkinter as tk
from tkinter import ttk, messagebox, scrolledtext
import threading
import scapy.all as scapy
from scapy.layers.l2 import ARP, Ether
from scapy.layers.inet import IP, TCP
import netifaces
import time
import sys
import logging
import re
import subprocess
import nmap
import os
from ArpSpoof import SpooferARP

# 设置 Nmap 路径
NMAP_PATH = r"C:\Program Files (x86)\Nmap"
NMAP_EXE = os.path.join(NMAP_PATH, "nmap.exe")

def check_nmap():
    """检查 Nmap 是否可用"""
    if not os.path.exists(NMAP_EXE):
        messagebox.showerror("错误", f"找不到 Nmap，请确保已安装在: {NMAP_PATH}")
        return False
    return True

if sys.platform == 'win32':
    if os.path.exists(NMAP_PATH):
        os.environ['PATH'] = NMAP_PATH + os.pathsep + os.environ['PATH']
        if hasattr(nmap.nmap, 'NMAP_INSTALLATION_PATH'):
            nmap.nmap.NMAP_INSTALLATION_PATH = NMAP_PATH

class NetworkToolGUI:
    def __init__(self, root):
        self.root = root
        self.root.title("网络工具集")
        self.root.geometry("800x600")
        
        # 检查 Nmap 是否可用
        self.nmap_available = check_nmap()
        
        # 设置日志
        self.setup_logging()
        
        # 存储运行状态
        self.arp_spoof_running = False
        self.scan_running = False
        self.spoofer = None
        
        # 存储接口映射
        self.interface_map = {}
        self.update_interface_map()
        
        # 创建选项卡
        self.notebook = ttk.Notebook(root)
        self.notebook.pack(expand=True, fill='both', padx=5, pady=5)
        
        # 创建各个功能页面
        self.create_arp_spoof_tab()
        self.create_network_scan_tab()
        self.create_interface_info_tab()

    def setup_logging(self):
        self.log_frame = ttk.Frame(self.root)
        self.log_frame.pack(fill='x', padx=5, pady=5)
        
        self.log_text = scrolledtext.ScrolledText(self.log_frame, height=8)
        self.log_text.pack(fill='both', expand=True)
        
        # 配置日志处理
        logging.basicConfig(level=logging.INFO)
        self.logger = logging.getLogger(__name__)
        
        # 添加日志处理器
        handler = logging.StreamHandler(stream=sys.stdout)
        handler.setFormatter(logging.Formatter('%(asctime)s - %(levelname)s - %(message)s'))
        self.logger.addHandler(handler)

    def update_interface_map(self):
        """更新接口名称映射"""
        try:
            self.interface_map = {}
            if sys.platform == 'win32':
                for iface in scapy.get_if_list():
                    try:
                        iface_obj = scapy.conf.ifaces.get(iface, None)
                        if iface_obj:
                            self.interface_map[f"{iface} ({iface_obj.description if hasattr(iface_obj, 'description') else 'Unknown'})"] = iface
                    except Exception as e:
                        self.logger.error(f"获取接口信息失败: {str(e)}")
            else:
                self.interface_map = {iface: iface for iface in scapy.get_if_list()}
        except Exception as e:
            self.logger.error(f"更新接口映射失败: {str(e)}")

    def create_arp_spoof_tab(self):
        """创建ARP欺骗标签页"""
        arp_frame = ttk.Frame(self.notebook)
        self.notebook.add(arp_frame, text='ARP欺骗')
        
        # 创建左侧输入框架
        input_frame = ttk.LabelFrame(arp_frame, text="配置", padding=10)
        input_frame.pack(side='left', fill='y', padx=5, pady=5)
        
        # 目标网关IP输入
        ttk.Label(input_frame, text="目标网关IP:").grid(row=0, column=0, padx=5, pady=5, sticky='w')
        self.gateway_ip = ttk.Entry(input_frame, width=30)
        self.gateway_ip.grid(row=0, column=1, padx=5, pady=5)
        
        # 攻击者IP输入（自动获取本机IP）
        ttk.Label(input_frame, text="攻击者IP:").grid(row=1, column=0, padx=5, pady=5, sticky='w')
        self.attacker_ip = ttk.Entry(input_frame, width=30)
        self.attacker_ip.grid(row=1, column=1, padx=5, pady=5)
        
        # 获取本机IP按钮
        get_ip_button = ttk.Button(input_frame, text="获取本机IP", command=self.get_local_ip)
        get_ip_button.grid(row=1, column=2, padx=5, pady=5)
        
        # 攻击间隔设置
        ttk.Label(input_frame, text="攻击间隔(秒):").grid(row=2, column=0, padx=5, pady=5, sticky='w')
        self.attack_interval = ttk.Entry(input_frame, width=30)
        self.attack_interval.insert(0, "0.5")
        self.attack_interval.grid(row=2, column=1, padx=5, pady=5)
        
        # 开始/停止按钮
        self.arp_button = ttk.Button(input_frame, text="开始ARP欺骗", command=self.toggle_arp_spoof)
        self.arp_button.grid(row=3, column=0, columnspan=2, pady=10)
        
        # 创建右侧状态显示框架
        status_frame = ttk.LabelFrame(arp_frame, text="状态", padding=10)
        status_frame.pack(side='right', fill='both', expand=True, padx=5, pady=5)
        
        # 状态显示文本框
        self.arp_status = scrolledtext.ScrolledText(status_frame, height=15)
        self.arp_status.pack(fill='both', expand=True)

    def get_local_ip(self):
        """获取本机IP地址"""
        try:
            # 获取默认网卡的IP地址
            for iface_name, iface in self.interface_map.items():
                iface_obj = scapy.conf.ifaces.get(iface, None)
                if iface_obj and hasattr(iface_obj, 'ip'):
                    if iface_obj.ip:
                        self.attacker_ip.delete(0, tk.END)
                        self.attacker_ip.insert(0, iface_obj.ip)
                        return
            
            messagebox.showwarning("警告", "无法获取本机IP地址")
        except Exception as e:
            messagebox.showerror("错误", f"获取本机IP失败: {str(e)}")

    def add_arp_status(self, message):
        """添加ARP状态信息"""
        timestamp = time.strftime("%Y-%m-%d %H:%M:%S")
        self.arp_status.insert(tk.END, f"[{timestamp}] {message}\n")
        self.arp_status.see(tk.END)
        self.root.update_idletasks()

    def toggle_arp_spoof(self):
        """切换ARP欺骗状态"""
        if not self.arp_spoof_running:
            gateway_ip = self.gateway_ip.get()
            attacker_ip = self.attacker_ip.get()
            
            if not gateway_ip or not attacker_ip:
                messagebox.showerror("错误", "请输入目标网关IP和攻击者IP")
                return
            
            try:
                interval = float(self.attack_interval.get())
                if interval < 0.1:
                    messagebox.showwarning("警告", "攻击间隔不能小于0.1秒")
                    return
            except ValueError:
                messagebox.showerror("错误", "请输入有效的攻击间隔时间")
                return
                
            self.arp_spoof_running = True
            self.arp_button.config(text="停止ARP欺骗")
            self.arp_status.delete(1.0, tk.END)
            self.add_arp_status("开始ARP欺骗攻击...")
            threading.Thread(target=self.run_arp_spoof, args=(gateway_ip, attacker_ip, interval), daemon=True).start()
        else:
            self.arp_spoof_running = False
            self.arp_button.config(text="开始ARP欺骗")
            self.add_arp_status("正在停止ARP欺骗...")

    def run_arp_spoof(self, gateway_ip, attacker_ip, interval):
        """执行ARP欺骗"""
        try:
            self.spoofer = SpooferARP(
                gateway=gateway_ip,    # 目标网关IP
                targets=attacker_ip,   # 攻击者IP
                semi=False,
                inter=interval
            )
            
            self.add_arp_status(f"目标网关: {gateway_ip}")
            self.add_arp_status(f"攻击者IP: {attacker_ip}")
            self.add_arp_status(f"攻击间隔: {interval}秒")
            
            while self.arp_spoof_running:
                self.spoofer.active_spoof()
                self.add_arp_status(f"发送ARP欺骗包 -> {gateway_ip}")
                time.sleep(interval)
                
        except Exception as e:
            error_msg = f"ARP欺骗错误: {str(e)}"
            self.logger.error(error_msg)
            self.add_arp_status(f"错误: {error_msg}")
            self.arp_spoof_running = False
            self.root.after(0, lambda: self.arp_button.config(text="开始ARP欺骗"))
        finally:
            if self.spoofer:
                self.spoofer.run = False
                self.spoofer.restore()
                self.add_arp_status("ARP欺骗已停止，ARP表已恢复")
                self.spoofer = None

    def create_network_scan_tab(self):
        """创建网络扫描标签页"""
        scan_frame = ttk.Frame(self.notebook)
        self.notebook.add(scan_frame, text='网络扫描')
        
        # 创建输入框架
        input_frame = ttk.LabelFrame(scan_frame, text="扫描配置", padding=10)
        input_frame.pack(fill='x', padx=5, pady=5)
        
        # IP范围输入
        ttk.Label(input_frame, text="IP范围:").grid(row=0, column=0, padx=5, pady=5)
        self.ip_range = ttk.Entry(input_frame, width=30)
        self.ip_range.grid(row=0, column=1, padx=5, pady=5)
        ttk.Label(input_frame, text="(例如: 192.168.1.1 或 192.168.1.0/24)").grid(row=0, column=2, padx=5, pady=5)
        
        # 端口范围输入
        ttk.Label(input_frame, text="端口范围:").grid(row=1, column=0, padx=5, pady=5)
        self.port_range = ttk.Entry(input_frame, width=30)
        self.port_range.insert(0, "21-23,25,80,443,3389,8080")
        self.port_range.grid(row=1, column=1, padx=5, pady=5)
        ttk.Label(input_frame, text="(例如: 80,443 或 20-1000)").grid(row=1, column=2, padx=5, pady=5)
        
        # 扫描按钮
        self.scan_button = ttk.Button(input_frame, text="开始扫描", command=self.start_network_scan)
        self.scan_button.grid(row=2, column=0, columnspan=3, pady=10)
        
        # 结果显示
        result_frame = ttk.LabelFrame(scan_frame, text="扫描结果", padding=10)
        result_frame.pack(fill='both', expand=True, padx=5, pady=5)
        
        self.scan_result = scrolledtext.ScrolledText(result_frame, height=20)
        self.scan_result.pack(fill='both', expand=True)

    def start_network_scan(self):
        """开始网络扫描"""
        if not self.scan_running:
            ip_range = self.ip_range.get()
            port_range = self.port_range.get()
            
            if not ip_range:
                messagebox.showerror("错误", "请输入IP范围")
                return
            
            if not port_range:
                messagebox.showerror("错误", "请输入端口范围")
                return
                
            self.scan_running = True
            self.scan_button.config(text="扫描中...", state="disabled")
            self.scan_result.delete(1.0, tk.END)
            
            # 启动扫描线程
            threading.Thread(target=self.run_network_scan, 
                           args=(ip_range, port_range), 
                           daemon=True).start()

    def run_network_scan(self, ip_range, port_range):
        """执行网络扫描"""
        try:
            self.scan_result.insert(tk.END, f"开始扫描...\nIP范围: {ip_range}\n端口范围: {port_range}\n\n")
            self.root.update()

            # 使用 subprocess 直接调用 nmap
            cmd = [
                NMAP_EXE,
                f"-p{port_range}",     # 指定端口范围（无空格）
                "-Pn",                 # 将目标视为在线
                "-sS",                 # SYN扫描
                "-T3",                 # 降低扫描强度
                "-n",                  # 不进行DNS解析
                "--max-retries", "2",  # 增加重试次数
                "--open",              # 只显示开放的端口
                ip_range
            ]
            
            self.scan_result.insert(tk.END, f"执行命令: {' '.join(cmd)}\n\n")
            
            # 执行扫描
            process = subprocess.Popen(
                cmd,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                universal_newlines=True
            )
            
            stdout, stderr = process.communicate()
            
            if stderr and "RTTVAR" not in stderr:  # 忽略 RTTVAR 警告
                self.scan_result.insert(tk.END, f"错误输出:\n{stderr}\n")
            
            if not stdout.strip():
                self.scan_result.insert(tk.END, "未发现开放的端口。\n建议：\n1. 确认目标主机是否在线\n2. 尝试扫描更多端口\n3. 检查防火墙设置\n")
            
            # 解析并显示结果
            current_host = None
            for line in stdout.split('\n'):
                if "Nmap scan report for" in line:
                    if current_host:
                        self.scan_result.insert(tk.END, "-" * 70 + "\n")
                    current_host = line.split()[-1]
                    self.scan_result.insert(tk.END, f"\n主机: {current_host}\n")
                    self.scan_result.insert(tk.END, "-" * 30 + "\n")
                elif "MAC Address:" in line:
                    mac_info = line.split("MAC Address:")[1].strip()
                    self.scan_result.insert(tk.END, f"MAC地址: {mac_info}\n")
                elif '/tcp' in line and 'open' in line:
                    port_info = line.strip()
                    self.scan_result.insert(tk.END, f"开放端口: {port_info}\n")
                
                self.root.update()
                
        except Exception as e:
            error_msg = f"扫描错误: {str(e)}"
            self.logger.error(error_msg)
            self.scan_result.insert(tk.END, f"\n错误: {error_msg}\n")
            if "权限不足" in str(e) or "administrator" in str(e).lower():
                self.scan_result.insert(tk.END, "\n提示: 请以管理员权限运行程序\n")
        finally:
            self.scan_running = False
            self.root.after(0, lambda: self.scan_button.config(text="开始扫描", state="normal"))
            self.scan_result.insert(tk.END, "\n扫描完成\n")

    def create_interface_info_tab(self):
        info_frame = ttk.Frame(self.notebook)
        self.notebook.add(info_frame, text='接口信息')
        
        # 接口信息显示
        self.info_text = scrolledtext.ScrolledText(info_frame, height=20)
        self.info_text.pack(fill='both', expand=True, padx=5, pady=5)
        
        # 刷新按钮
        refresh_button = ttk.Button(info_frame, text="刷新", command=self.refresh_interface_info)
        refresh_button.pack(pady=5)
        
        # 初始化显示接口信息
        self.refresh_interface_info()
        
    def refresh_interface_info(self):
        """刷新接口信息显示"""
        self.info_text.delete(1.0, tk.END)
        try:
            if sys.platform == 'win32':
                for iface_name, iface in self.interface_map.items():
                    self.info_text.insert(tk.END, f"\n接口: {iface_name}\n")
                    try:
                        iface_obj = scapy.conf.ifaces.get(iface, None)
                        if iface_obj:
                            self.info_text.insert(tk.END, f"  MAC地址: {iface_obj.mac if hasattr(iface_obj, 'mac') else 'N/A'}\n")
                            self.info_text.insert(tk.END, f"  IPv4地址: {iface_obj.ip if hasattr(iface_obj, 'ip') else 'N/A'}\n")
                    except Exception as e:
                        self.info_text.insert(tk.END, f"  获取详细信息失败: {str(e)}\n")
            else:
                for interface in scapy.get_if_list():
                    try:
                        addrs = netifaces.ifaddresses(interface)
                        self.info_text.insert(tk.END, f"\n接口: {interface}\n")
                        
                        if netifaces.AF_INET in addrs:
                            for addr in addrs[netifaces.AF_INET]:
                                self.info_text.insert(tk.END, f"  IPv4地址: {addr['addr']}\n")
                                self.info_text.insert(tk.END, f"  子网掩码: {addr.get('netmask', 'N/A')}\n")
                        
                        if netifaces.AF_LINK in addrs:
                            for addr in addrs[netifaces.AF_LINK]:
                                self.info_text.insert(tk.END, f"  MAC地址: {addr.get('addr', 'N/A')}\n")
                    except Exception as e:
                        self.info_text.insert(tk.END, f"  获取信息失败: {str(e)}\n")
        except Exception as e:
            self.logger.error(f"刷新接口信息失败: {str(e)}")

if __name__ == "__main__":
    root = tk.Tk()
    app = NetworkToolGUI(root)
    root.mainloop() 