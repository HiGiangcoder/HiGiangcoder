def extEuclid(a, b, x, y):
    if b == 0:
        x = 1
        y = 0
        return [a, x, y]

    q = a // b
    r = a - b * q
    x1, y1 = 0, 0

    [d, x1, y1] = extEuclid(b, r, x1, y1)

    x = y1
    y = x1 - q * y1
    return [d, x, y]

def find_reverse(a, m):
    [d, x, y] = extEuclid(a, m, 0, 0)

    x = (x % m + m) % m
    
    return x

import math
import sys

from Crypto.Util.number import bytes_to_long, long_to_bytes

sys.setrecursionlimit(2000)

with open("text.txt", "r") as file:
    n1 = int(file.readline())
    n2 = int(file.readline())
    n3 = int(file.readline())

    c1 = int(file.readline())
    c2 = int(file.readline())
    c3 = int(file.readline())

#print(math.gcd(n1, n2));
#print(math.gcd(n2, n3));
#print(math.gcd(n1, n3));

M = n1 * n2 * n3
m1 = M // n1
m2 = M // n2
m3 = M // n3

y1 = find_reverse(m1, n1)
y2 = find_reverse(m2, n2)
y3 = find_reverse(m3, n3)

ans = c1 * m1 % M * y1 % M + c2 * m2 % M * y2 % M + c3 * m3 % M * y3 % M

ans %= M


result = 0
l, r = 1, ans

while l <= r: 
    mid = (l + r) // 2
    if mid ** 3 <= ans: 
        result = mid
        l = mid + 1
    else :
        r = mid - 1

x = long_to_bytes(result)

print(x)
input()
