import socket
import sys

localSock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print("New TCP Socket")


ip = "127.0.0.1"
port = 8080

if (len(sys.argv) > 3):
    localSock.bind((ip,port))
else:
    localSock.bind(("0.0.0.0",0))
print("Address bound at IP:", localSock.getsockname()[0], "Port:", localSock.getsockname()[1])

