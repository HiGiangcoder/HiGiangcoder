from Crypto.Cipher import AES
import os
from Crypto.Util.Padding import pad, unpad
from datetime import datetime, timedelta
import requests
from pwn import xor


def check_admin(cookie, iv):
    url = 'https://aes.cryptohack.org/flipping_cookie/check_admin/'
    url += cookie + '/'
    url += iv + '/'

    r = requests.get(url)
    js = r.json()
    return js

def get_cookie():
    url = 'https://aes.cryptohack.org/flipping_cookie/get_cookie/'
    r = requests.get(url)
    js = r.json()
    return js


expires_at = (datetime.today() + timedelta(days=1)).strftime("%s")

realCookie = get_cookie()['cookie']
realCookie = bytes.fromhex(realCookie)
iv = realCookie[0:16]
realCookie = realCookie[16:]

fakeCookie = "admin=True;".encode()
curCookie =  "admin=False".encode()
cookie = b''
for i in range(len(fakeCookie)):
    cookie += xor(xor(realCookie[i], fakeCookie[i]), curCookie[i])

cookie += realCookie[len(fakeCookie):]

print(check_admin(bytes.hex(cookie), bytes.hex(iv)))
