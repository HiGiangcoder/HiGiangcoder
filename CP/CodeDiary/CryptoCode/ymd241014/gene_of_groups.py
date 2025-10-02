p = 28151

for g in range(1, p):
    fre = [0 for _ in range(p)]
    num = g
    for x in range(p):
        if num != 0:
            fre[num] = 1
        num = num * g % p

    res = 0
    for i in range(p):
        res += fre[i]

    if res == p - 1:
        print(g)
