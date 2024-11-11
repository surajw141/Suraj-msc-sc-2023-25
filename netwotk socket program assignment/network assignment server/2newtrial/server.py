import socket
import threading
import sys

# Server setup
HOST = '192.168.6.5'  # Localhost, change this to your server's IP on the network
PORT = 12345        # Arbitrary port
SHUTDOWN_MESSAGE = "shutdown_server"  # Unique message to shut down server

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind((HOST, PORT))
server_socket.listen()

clients = []  # List to keep track of connected clients
server_running = True  # Flag to check if the server is running

# Handle incoming messages from clients
def handle_client(client_socket, client_address):
    global server_running
    print(f"New connection from {client_address}")
    while server_running:
        try:
            message = client_socket.recv(1024).decode('utf-8')
            if message:
                print(f"Message from {client_address}: {message}")
                
                if message == SHUTDOWN_MESSAGE:
                    # Shutdown the server if the special shutdown message is received
                    broadcast("Server is shutting down...")
                    server_running = False
                    break
                
                broadcast(f"{client_address}: {message}", client_socket)
            else:
                remove_client(client_socket)
                break
        except:
            continue

# Broadcast message to all clients except sender
def broadcast(message, sender_socket=None):
    for client in clients:
        if client != sender_socket:
            try:
                client.send(message.encode('utf-8'))
            except:
                remove_client(client)

# Function to remove client from the list
def remove_client(client_socket):
    if client_socket in clients:
        clients.remove(client_socket)

# Server sending message to all clients
def send_messages():
    global server_running
    while server_running:
        message = input("Me: ")  # Get message from server admin
        
        if message == SHUTDOWN_MESSAGE:
            # Shutdown the server from admin input
            broadcast("Server is shutting down...")
            server_running = False
            break
        
        broadcast(f"{message}")

# Start the server and listen for incoming clients
def start_server():
    global server_running
    print(f"Server is running on {HOST}:{PORT}")
    
    # Start a new thread to allow the server admin to send messages
    threading.Thread(target=send_messages).start()
    
    while server_running:
        try:
            client_socket, client_address = server_socket.accept()
            clients.append(client_socket)
            threading.Thread(target=handle_client, args=(client_socket, client_address)).start()
        except:
            break
    
    # When the server is shutting down, close all client connections
    close_server()

def close_server():
    print("Closing all connections...")
    for client in clients:
        client.close()
    server_socket.close()
    print("Server shut down successfully")
    sys.exit()

if __name__ == "__main__":
    start_server()
