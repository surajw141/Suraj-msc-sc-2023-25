##Name: Suraj Waghmare (MS2321)
##Date: 19/10/2024

import socket


def run_server():
    # create a socket object
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    server_ip = "192.168.6.5"
    port = 8000

    # bind the socket to a specific address and port
    server.bind((server_ip, port))
    # listen for incoming connections
    server.listen(0)
    print(f"Listening on {server_ip}:{port}")

    # accept incoming connections
    client_socket, client_address = server.accept()
    print(f"Accepted connection from {client_address[0]}:{client_address[1]}")

    while True:
        # receive data from the client
        request = client_socket.recv(1024).decode("utf-8")

        # if the client sends "see you soon...", we close the connection
        if request.lower() == "see you soon...":
            print("Client disconnected with exit message.")
            client_socket.send("see you soon...".encode("utf-8"))
            break

        print(f"Client: {request}")

        # send response to the client
        response = input("Enter message to send: ")
        client_socket.send(response.encode("utf-8"))

        # if the server sends "see you soon...", we close the connection
        if response.lower() == "see you soon...":
            break

    # close connection socket with the client
    client_socket.close()
    print("Connection to client closed")
    # close server socket
    server.close()


run_server()
