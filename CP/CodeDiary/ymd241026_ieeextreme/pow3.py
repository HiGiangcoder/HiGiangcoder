from math import sqrt
pows = [3]
while True:
    if pows[-1]**2 <= 10**3000:
        pows += [pows[-1] ** 2]
    else:
        break
S = input()

def Div(s, k):
    num = ''
    i = 0
    rem = 0

    LEN = 1600
    while i < len(s):
        n = s[i:i+LEN]
        LEN = len(n)
        i += LEN

        rem = int(n) + rem * (10**(LEN))

        tmp = str(rem // k)
        if num == '':
            if tmp != '0':
                num += tmp
        else:
            for _ in range(LEN - len(tmp)):
                num += '0'
            num += tmp

        rem %= k

#        print("n, LEN, tmp, rem, num", n, LEN, tmp, rem, num)

    if num == '':
        num = '0'
    return num, rem

ans = 0

numid = len(pows) - 1

while numid >= 0:
    num, rem = Div(S, pows[numid])
    if rem == 0:
        S = num
        ans += 2**numid
    else:
        numid -= 1

#        print(num, rem, ans, check)


if S != '1':
    print(-1)
else:
    print(ans)

