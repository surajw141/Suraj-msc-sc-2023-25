import socket
import threading

# Server setup
HOST = '192.168.6.5'  # Localhost, change this to your server's IP on the network
PORT = 12345        # Arbitrary port

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind((HOST, PORT))
server_socket.listen()

clients = []  # List to keep track of connected clients

def handle_client(client_socket, client_address):
    print(f"New connection from {client_address}")
    while True:
        try:
            message = client_socket.recv(1024).decode('utf-8')
            if message:
                print(f"Message from {client_address}: {message}")
                broadcast(message, client_socket)
            else:
                remove_client(client_socket)
                break
        except:
            continue

def broadcast(message, sender_socket):
    for client in clients:
        if client != sender_socket:
            try:
                client.send(message.encode('utf-8'))
            except:
                remove_client(client)

def remove_client(client_socket):
    if client_socket in clients:
        clients.remove(client_socket)

def start_server():
    print(f"Server is running on {HOST}:{PORT}")
    while True:
        client_socket, client_address = server_socket.accept()
        clients.append(client_socket)
        threading.Thread(target=handle_client, args=(client_socket, client_address)).start()

if __name__ == "__main__":
    start_server()

