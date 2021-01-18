import time
import socket
import threading

import packages

# port settings
IP = '127.0.0.1'
PORT = 1040


class Server(pkgs.PackageHandler):

    def __init__(self, ip, port):
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

        # Socket settings
        self.server_socket.setsockopt(
            socket.SOL_SOCKET, 
            socket.SO_REUSEADDR, 
            1)

        self.server_socket.bind((ip, port))
        self.server_socket.listen()

        print(f'Listening for connections on {ip}:{port}')
        self.server_loop()

    def server_loop(self):
        while True:
            client_socket, client_address = self.server_socket.accept()
            print(f"Accepted new connection from {client_address}")

            package = self.pull(client_socket)
            if package:

                if package['type'] != 'con':
                    continue

                user_id = int(package['data'].decode('ascii'))

                print(f"Received user ID: {user_id}")
                self.push(client_socket, "Hello from the Server!")

                while True:
                    self.push(client_socket, "Connection still alive!")
                    time.sleep(2)

if __name__ == '__main__':
    server = Server(IP, PORT)