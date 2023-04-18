import socket
import sys
import select
import struct

if len(sys.argv) != 4:
    print("Usage: udp_multicast_chat_client.py serverIp serverPort username")
    sys.exit()

server_address = (sys.argv[1], int(sys.argv[2]))
nickname = sys.argv[3]

mcast_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM,socket.IPPROTO_UDP)

room_address = None
udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

def sendToRoom(msg):
    mcast_socket.sendto(msg.encode(), room_address)

def sendToServer(msg):
    udp_socket.sendto(msg.encode(), server_address)
    
sendToServer(f'login:{nickname}')

while True:
    readReady, writeReady, exceptReady = select.select([udp_socket, sys.stdin, mcast_socket], [], [], 1)
    if sys.stdin in readReady:
        input = sys.stdin.readline()
        

        if input.startswith('/'):
            input.rstrip()
            inputSplit = input.split(" ")
            if input == "/end\n":
                print(">Closing connection")
                udp_socket.close()
                mcast_socket.close()
                sys.exit()
            elif input.startswith("/rooms"):
                sendToServer("getChatRoomList")
            elif input.startswith("/join"):
                msg = "enterChatRoom:" + inputSplit[1]
                sendToServer(msg)
            else:
                print("Unknown command")
        else:
            if room_address == None:
                print("You can't send a chat message, because you are not connected to any chatroom!")
            else:
                msg = f"message:{nickname}:{input}"
                sendToRoom(msg)
    
    if udp_socket in readReady:
        data, addr = udp_socket.recvfrom(1024)
        message = data.decode().rstrip()
        messageSplit = message.split(":")

        if messageSplit[0] == "message":
            messageSplit.pop(0)
            print(":".join(messageSplit))
        elif messageSplit[0] == "getChatRoomList":
            print("Available chatrooms:")
            for i in messageSplit[1:]:
                print(i)
        elif messageSplit[0] == "enterChatRoom":
            if messageSplit[1] == "-1" and messageSplit[2] == "-1":
                print("This chatroom doesn't exist")
            else:
                room_address = (messageSplit[1],int(messageSplit[2]))
                mcast_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
                print(room_address)
                mcast_socket.bind(room_address)
                mreq = struct.pack('4sl', socket.inet_aton(messageSplit[1]), socket.INADDR_ANY)
                mcast_socket.setsockopt(socket.IPPROTO_IP, socket.IP_ADD_MEMBERSHIP, mreq)
                print("Connected to chatroom")
    
    if mcast_socket in readReady:
        data = mcast_socket.recv(1024)
        message = data.decode().rstrip()
        messageSplit = message.split(":")

        if messageSplit[0] == "message":
            messageSplit.pop(0)
            if messageSplit[0] != nickname:
                message =":".join(messageSplit)
                print(message)
