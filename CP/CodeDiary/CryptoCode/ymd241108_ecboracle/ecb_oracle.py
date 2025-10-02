from Crypto.Cipher import AES
from Crypto.Util.Padding import pad, unpad
import requests
import string
import time

def encrypt(plaintext):
    url = 'https://aes.cryptohack.org/ecb_oracle/encrypt/' + plaintext + '/'
    r = requests.get(url)
    js = r.json()
    return js['ciphertext']

def print_blk(data, block_size):
    for i in range(0, len(data), block_size):
        print(data[i:i+block_size])

def bruteforce():
    flag = ''
    total = 32 - 1
    alphabet = '_'+'@' + '{' +'}'+string.digits+string.ascii_lowercase+string.ascii_uppercase

    while True:
        payload = '1' * (total-len(flag))
        expected = encrypt(payload.encode().hex())
        print('E', '', end='')
        print_blk(expected, 32)

        for c in alphabet:
            res = encrypt(bytes.hex((payload + flag + c).encode()))
            print(b'          ' + bytes.fromhex(bytes.hex((payload + flag + c).encode())))

            print(c, '', end='')
            print_blk(res, 32)
            if res[32:64] == expected[32:64]:
                flag += c
                print(flag)
                break
#            time.sleep(1)

        if flag.endswith('}'): break

    print(flag)

print(bruteforce())
