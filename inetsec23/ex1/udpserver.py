import socket
import sys
import threading

PORT = 8081
#Create TCP Socket for Mediating Server
server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

#Bind socket to addressa and port
server_socket.bind(("0.0.0.0", PORT))
i = 0
while True:
    buf, inet = server_socket.recvfrom(512)
    msg = buf.decode('utf-8')
    msg = msg.split('::')

    #Client is Registering with the server
    if len(msg)<2:
        clientsDict[msg[0]] = inet      #dict to maintain pairs of name and inet
        response = 'OKOKOK'
        server_socket.sendto(response.encode(), inet)
    # if len(msg)==2 client must have sent a request to connect to other client
    elif len(msg) == 2:
        name = msg[1]
        registeredClients = clientsDict.keys().count(name)
        if registeredClients == 0:
            buf = "No Such Client"
            server_socket.sendto(buf.encode(), inet)
        else:
            inetReq = clientsDict[name]
            bufFrom = inetReq[0] + "::" + inetReq[1]
            bufTo = name + "::" + inet[0] + "::" + inet[1]
            server_socket.sendto(bufFrom.encode(), inet)
            server_socket.sendto(bufTo.encode(), inetReq)
