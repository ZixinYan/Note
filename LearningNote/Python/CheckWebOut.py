from ipaddress import ip_network
from socket import TCP_CONNECTION_INFO
from telnetlib import IP
from scapy.all import *  
  
def scan_port(ip, port):  
    # 创建并发送TCP包  
    response = sr1(IP(dst=ip)/TCP_CONNECTION_INFO(dport=port), verbose=0, timeout=1)  
      
    # 检查响应  
    if response:  
        if response.flags == 0b10: # SYN-ACK  
            print(f"Port {port} is open on {ip}")  
  
# 扫描指定网段中的所有IP地址  
def scan_subnet(network, ports):  
    network = ip_network(network)  
    for ip in network.hosts():  
        for port in ports:  
            scan_port(ip, port)  
  
# 扫描指定网段中的所有IP地址，并输出对外网开放的IP地址  
scan_subnet("202.122.38.0/24", [80, 443])