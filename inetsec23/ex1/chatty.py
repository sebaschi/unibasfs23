import socket
import sys
import threading

def start_server(port):
    # Create a TCP/IP socket
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # Bind the socket to a specific address and port
    server_address = ('localhost', port)
    server_socket.bind(server_address)

    # Listen for incoming connections
    server_socket.listen(1)

    # Wait for a connection
    print('Waiting for a connection...')
    connection, client_address = server_socket.accept()
    print('Connection from', client_address)

    # Create a separate thread for receiving messages
    receive_thread = threading.Thread(target=receive_messages, args=(connection,))
    receive_thread.start()

    # Continuously send messages
    while True:
        message = input()
        if message == '':
            break
        connection.sendall(message.encode('utf-8'))

    # Close the connection and the server socket
    connection.close()
    server_socket.close()

def start_client(ip, port):
    # Create a TCP/IP socket
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # Connect the socket to the server's address and port
    server_address = (ip, port)
    client_socket.connect(server_address)

    # Create a separate thread for receiving messages
    receive_thread = threading.Thread(target=receive_messages, args=(client_socket,))
    receive_thread.start()

    # Continuously send messages
    while True:
        message = input()
        if message == '':
            break
        client_socket.sendall(message.encode('utf-8'))

    # Close the connection and the client socket
    client_socket.close()

def receive_messages(connection):
    while True:
        data = connection.recv(1024)
        if not data:
            break
        print(data.decode('utf-8'))

if len(sys.argv) == 1:
    start_server(10000)
elif len(sys.argv) == 2:
    port = int(sys.argv[1])
    start_server(port)
else:
    ip = sys.argv[1]
    port = int(sys.argv[2])
    start_client(ip, port)

