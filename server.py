import socket
import string
import random
import time


HOST = '127.0.0.1'
PORT = 8000

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    s.bind((HOST, PORT))
    s.listen()
    conn, addr = s.accept()
    with conn:
#        while True:
        for i in range(10):
#            data = random.choice(string.ascii_letters).encode('utf-8')
            data = ""
            for i in range(4000):
                data += ("a")
            length = len(data)
            data = str(length) + ":" + data + "0"
            data = data.encode('utf-8')
#            print(data)
            conn.sendall(data)
            received = conn.recv(1024)
            print(received)
            if received != b'Received':
                break
        conn.sendall("3:END".encode('utf-8'))

