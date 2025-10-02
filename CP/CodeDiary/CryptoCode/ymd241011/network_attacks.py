from pwn import *
import json

HOST = "socket.cryptohack.org"
PORT = 11112

r = remote(HOST, PORT)


def readline():
    return r.readuntil(b"\n")

def json_recv():
    line = readline()
    return json.loads(line.decode())

def json_send(hsh):
    request = json.dumps(hsh).encode()
    r.write(request)


for _ in range(4):
    print(readline())


request = {
    "buy": "flag"
}


json_send(request)
input()

response = json_recv()

print(response["flag"])
