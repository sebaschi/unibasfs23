import socket
import sys
import threading

client_socket = socket.socket(socket.AF_INET, sock.SOCK_DGRAM)

#Bind Socket
client_socket.bind(("0.0.0.0", 0))

name = sys.argv[1]
sIP = sys.argv[2]
sPort = sys.argv[3]

# register with server
response = ''
while (response != 'OKOKOK'):
    client_socket.sendto(name.encode(), (htonl(sIP), htons(sPort)))
    response = client_socket.recvfrom(512)
    response = response.decode()

#When registered listen to stdin

name = ''
print("Who do you want to connect to?")
client = input()
ip = ''
port = ''

while (name != client):
    client_socket.sendto(name.encode(), (htonl(sIP), htons(sPort)))
    buf = client_socket.recvfrom(512)
    response = buf.decode()
    response = response.split('::')
    if(len(response) != 3):
        name = response[0]
        ip = response[1]
        port = response[2]
        break
