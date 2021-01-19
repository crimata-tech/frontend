import time
import socket
import threading

from packages import pull, push

IP = '127.0.0.1'
PORT = 1040


server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

server_socket.bind((IP, PORT))
server_socket.listen()

print(f'Listening for connections on {IP}:{PORT}')

def server_loop():
    while True:
        client_socket, client_address = server_socket.accept()
        print(f"Accepted new connection from {client_address}")

        package = pull(client_socket)
        if package:

            if package['type'] != 'con':
                continue

            user_id = int(package['data'].decode('ascii'))

            print(f"Received user ID: {user_id}")
            push(client_socket, "Hello from the Server!")

            while True:
                push(client_socket, "Connection still alive!")
                time.sleep(2)

server_loop()