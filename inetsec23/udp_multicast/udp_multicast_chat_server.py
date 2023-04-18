import socket
import sys


if len(sys.argv) != 2:
    print("Usage: udp_multicast_chat_server.py port")
    sys.exit()
    
sSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sSocket.bind(("0.0.0.0", int(sys.argv[1])))

print("Server started on port",sys.argv[1])

chatRoomList = {}

chatRoomList["roomA"] = ('224.0.0.1',6000)
chatRoomList["roomB"] = ('224.0.0.1',6001)
chatRoomList["roomC"] = ('224.0.0.2',6002)

def sendToUser(addr, msg):
		sSocket.sendto(msg.encode(), addr)

while True:
    data, addr = sSocket.recvfrom(1024)
    data = data.decode().rstrip()
    
    message = data.split(':')

    if message[0] == "login":
        chatrooms =  "getChatRoomList:" 
        for c in chatRoomList:
            chatrooms += c +":"
        chatrooms = chatrooms[:-1]
        sendToUser(addr, chatrooms + "\n")
    elif message[0] == "enterChatRoom":
          if message[1] in chatRoomList:
                ip, port = chatRoomList[message[1]]
                sendToUser(addr, f"enterChatRoom:{ip}:{port}\n")
          else:
                sendToUser(addr, "enterChatRoom:-1:-1\n")