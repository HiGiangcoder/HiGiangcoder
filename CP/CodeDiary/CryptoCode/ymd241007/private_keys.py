# a*x + b*y = gcd(a, b) = d
def ExtEuclid(a, b):
    if b == 0:
        return a, 1, 0

    q = a // b
    r = a - b * q
    
    d, x1, y1 = ExtEuclid(b, r)

    x = y1
    y = x1 - q * y1

    return d, x, y

# x = num^(-1) (mod M)
def ModInverse(num, M):
    gcd, x, y = ExtEuclid(num, M)

    if gcd != 1: return -1

    return (x % M + M) % M


p = 857504083339712752489993810777
q = 1029224947942998075080348647219
e = 65537

phiN = (p - 1) * (q - 1)

d = ModInverse(e, phiN)

print(d)
input()
