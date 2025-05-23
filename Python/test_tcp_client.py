import socket

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect(("localhost", 12345))
    message = "Hello, TCP!\n".encode()
    s.sendall(message)
    data = s.recv(1024)
    print(f"Recieved: {data.decode()}")