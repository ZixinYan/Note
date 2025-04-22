import socket  
  
def get_domain_from_ip(ip):  
    try:  
        # 创建一个socket对象  
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  
        # 发送一个空的DNS请求到DNS服务器  
        s.sendto(b'\x00\x01\x00\x01\x00\x00\x00\x3c\x00\x04', (socket.gethostbyname('dns.google'), 53))  
        # 接收DNS响应  
        data, addr = s.recvfrom(1024)  
        # 解析DNS响应中的域名  
        domain = data[32:data[32:].index(b'\x00')].decode()  
        return domain  
    except Exception as e:  
        print(f"Error: {e}")  
        return None  
  
ip = '202.122.38.83'  # 替换为你要查询的IP地址  
domain = get_domain_from_ip(ip)  
print(domain)