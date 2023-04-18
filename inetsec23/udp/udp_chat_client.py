import socket
import sys
import select

if len(sys.argv) != 4:
    print("Usage: udp_chat_client.py serverIp serverPort username")
    sys.exit()

server_address = (sys.argv[1], int(sys.argv[2]))
nickname = sys.argv[3]
chat_address = None
udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

def sendToUser(msg):
    udp_socket.sendto(msg.encode(), chat_address)

def sendToServer(msg):
    udp_socket.sendto(msg.encode(), server_address)

sendToServer(f'login:{nickname}')

while True:
    readReady, writeReady, exceptReady = select.select([udp_socket, sys.stdin], [], [], 1)
    
    if sys.stdin in readReady:
        input = sys.stdin.readline()
        

        if input.startswith('/'):
            input.rstrip()
            inputSplit = input.split(" ")
            if input == "/end\n":
                print(">Closing connection")
                udp_socket.close()
                sys.exit()
            elif input.startswith("/connectTo"):
                if inputSplit[1].rstrip() == nickname:
                    print("You can't connect to yourself!")
                    continue
                if chat_address != None:
                    print("You are already connected to another user!")
                else:
                    msg = "getAddr:" + inputSplit[1]
                    sendToServer(msg)
            elif input.startswith("/users"):
                msg = "getUsers:" + nickname
                sendToServer(msg)
            else:
                print("Unknown command")
        else:
            if chat_address == None:
                print("You can't send a chat message, because you are not connected to any user!")
            else:
                sendToUser(f'message:{nickname}: {input}')
    
    if udp_socket in readReady:
        data, addr = udp_socket.recvfrom(1024)
        message = data.decode().rstrip()
        messageSplit = message.split(":")

        if messageSplit[0] == "message":
            messageSplit.pop(0)
            print(":".join(messageSplit))
        elif messageSplit[0] == "getAddr":
            getAddr = (messageSplit[1],int(messageSplit[2]))
            if(getAddr[0] == -1 and getAddr[1] == -1):
                print("This user is not connected to the server")
            else:
                chat_address = getAddr
                msg = "join:" + nickname
                sendToUser(msg)
                print("Succesfully connected")
        elif messageSplit[0] == "sendUsers":
            print("Connected users:")
            for x in messageSplit[1:]:
                print(x)
        elif messageSplit[0] == "join":
            chat_address = addr
            print(f'User {messageSplit[1]} joined')
