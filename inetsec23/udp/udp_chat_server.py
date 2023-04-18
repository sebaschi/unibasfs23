import socket
import sys


if len(sys.argv) != 2:
    print("Usage: udp_chat_server.py port")
    sys.exit()
    
sSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sSocket.bind(("0.0.0.0", int(sys.argv[1])))
print("Server started on port",sys.argv[1])

users = {}

def sendToUser(addr, msg):
		sSocket.sendto(msg.encode(), addr)

while True:
    data, addr = sSocket.recvfrom(1024)
    data = data.decode().rstrip()
    
    message = data.split(':')

    if message[0] == "login":
        users[message[1]] = addr
        sendToUser(addr, "message:logged in with nickname: " + message[1] + "\n")
    elif message[0] == "getAddr":
        if message[1] in users:
            ip, port = users[message[1]]
            sendToUser(addr, f'getAddr:{ip}:{port}\n')      
        else:
           sendToUser(x.addr, "getAddr:-1:-1")
    elif message[0] == "getUsers":
        msg = "sendUsers:"
        for x in users:
            msg += x + ":"
        msg = msg[:-1]
        sendToUser(addr,msg) 