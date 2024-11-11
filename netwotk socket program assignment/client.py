##Name: Suraj Waghmare (MS2321)
##Date: 19/10/2024

import socket


def run_client():
    # create a socket object
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    server_ip = "192.168.6.5"  # replace with the server's IP address
    server_port = 8000  # replace with the server's port number
    # establish connection with server
    client.connect((server_ip, server_port))

    while True:
        # input message and send it to the server
        msg = input("Enter message: ")
        client.send(msg.encode("utf-8"))

        # if the client sends "see you soon...", we break out of the loop and close the socket
        if msg.lower() == "see you soon...":
            break

        # receive message from the server
        response = client.recv(1024).decode("utf-8")

        # if server sent us "see you soon...", we break out of the loop and close the socket
        if response.lower() == "see you soon...":
            print("Server disconnected with exit message.")
            break

        print(f"Server: {response}")

    # close client socket (connection to the server)
    client.close()
    print("Connection to server closed")


run_client()
