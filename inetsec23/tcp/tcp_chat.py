import sys
import socket
import select


if len(sys.argv) == 2:
    sSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sSocket.bind(('0.0.0.0', int(sys.argv[1])))
    sSocket.listen()
    print("Waiting for other client to connect...")
    cSocket, cAddr = sSocket.accept()
    print("Connected")
elif len(sys.argv) == 3:
    cSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    cSocket.connect((sys.argv[1], int(sys.argv[2])))
    print("Connected")
else:
    print("Usage:\nFor server: tcp_chat.py port\nFor client: tcp_chat.py serverIp serverPort")
    sys.exit()

while True:
    readReady, writeReady, exceptReady = select.select([cSocket, sys.stdin], [], [], 1)

    if sys.stdin in readReady:
        input = sys.stdin.readline()
        
        if input == "/end\n":
            print(">Closing connection")
            cSocket.close()
            sys.exit()
        else:
            cSocket.send(input.encode())
    if cSocket in readReady:
        message = cSocket.recv(1024).decode()
        if len(message) == 0:
            print(">Connection closed by another user")
            cSocket.close()
            sys.exit()
        print("received:", message, end="")