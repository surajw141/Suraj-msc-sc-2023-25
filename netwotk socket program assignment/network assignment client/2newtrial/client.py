import socket
import threading

# Server details
SERVER_IP = '192.168.6.5'  # Server IP, use actual network address if necessary
SERVER_PORT = 12345

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect((SERVER_IP, SERVER_PORT))
Message = input("enter your chat participent(server): ")
def receive_messages():
    while True:
        try:
            message = client_socket.recv(1024).decode('utf-8')
            if message:
                print(f"{Message}: {message}")
        except:
            print("Error receiving message")
            break

def send_messages():
    while True:
        message = input("Me: ")
        client_socket.send(message.encode('utf-8'))

# Start threads for sending and receiving
receive_thread = threading.Thread(target=receive_messages)
receive_thread.start()

send_thread = threading.Thread(target=send_messages)
send_thread.start()
