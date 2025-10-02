from Crypto.Util.number import *
import os

BITS = 256
d = 30

def poly(x):
    return sum([coeffs[i] * x ** i for i in range(d + 1)])

FLAG = b'W1{???????????????????????????}'
FLAG = bytes_to_long(FLAG)

coeffs = [FLAG] + [bytes_to_long(os.urandom(BITS // 8)) for _ in range(d)]

shares = []
x = []
for i in range(19):
    p = getPrime(15)
    x.append(p)
    shares.append(poly(p))

print(x)
print(shares)
