import socket
# program to find devices nearby ip addresses starts with 192.168.6.x
def run_server():
    # create a socket object
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # get local machine name
    host = socket.gethostname()

    # bind the socket to a public host, and a well-known port
    server.bind((host, 8000))

    # become a server socket
    server.listen(5)

    while True:
        # accept connections from outside
        (clientsocket, address) = server.accept()

        # print the client's IP address
        print(f"Connection from {address[0]} has been established!")

        # send a message to the client
        clientsocket.send(bytes("Welcome to the server!", "utf-8"))

        # close the client socket
        clientsocket.close()
