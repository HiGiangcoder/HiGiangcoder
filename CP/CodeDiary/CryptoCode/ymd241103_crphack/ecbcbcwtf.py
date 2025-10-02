from Crypto.Util.number import long_to_bytes, bytes_to_long
import requests
from pwn import xor
from Crypto.Cipher import AES

def encrypt():
    url = 'https://aes.cryptohack.org/ecbcbcwtf/encrypt_flag/'
    response = requests.get(url)
    return response.json()['ciphertext']

flag = encrypt()

f = [flag[i:i+32] for i in [0, 32, 64]]
vi = f[0:(len(f) - 1)]
f = f[1:]

def decrypt(data):
    url = 'https://aes.cryptohack.org/ecbcbcwtf/decrypt/'
    response = requests.get(url + data + '/')
    return response.json()['plaintext']

for i in range(len(f)):
    f[i] = decrypt(f[i])

for i in range(len(f)):
    f[i] = xor(bytes.fromhex(f[i]), bytes.fromhex(vi[i]))

flag = ''
for i in f:
    flag += i.decode()

print(flag)
