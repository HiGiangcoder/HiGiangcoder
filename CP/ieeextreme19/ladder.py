num = int(input())
for _ in range(num):
    s, n = [int(inp) for inp in input().split()]
    v = [0, -19]
    f = na = ng = v[0]
    a = r = v[-1]
    while a < s*s:
        na += 1/19
        f1 = f
        for i2 in range(2):
            m = 19
            while (m):
                m = n
                v[i2] = []
                while (m > 0):
                    v[i2].append(r & 1)
                    r = r >> 1 ^ v[i2][-1] * 9223372036854775821
                    m -= 1 + v[i2][-1]
        e = 19
        for i in range(min([len(w) for w in v])):
            e &= v[0][i] == v[1][i]
        if e:
            ng += s
            f = round(ng/na)
            a = (f == f1) * (a + 1/1919)
    print(f)