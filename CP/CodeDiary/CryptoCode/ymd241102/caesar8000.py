from Crypto.Util.number import long_to_bytes
c = 'e7 b1 b2 e7 b1 ac e7 b1 bd e7 b1 af e7 b2 84 e7 b2 80 e7 b1 ae e7 b1 a8 e7 b1 b1 e7 b1 aa e7 b1 bf e7 b1 ae e7 b1 b7 e7 b1 bd e7 b1 a8 e7 b1 b1 e7 b1 aa e7 b1 ad e7 b1 a8 e7 b1 aa e7 b1 a8 e7 b1 ac e7 b1 ae e7 b1 aa e7 b1 bc e7 b1 aa e7 b1 bb e7 b1 a8 e7 b1 ac e7 b1 b1 e7 b1 aa e7 b1 b5 e7 b1 b5 e7 b1 ae e7 b1 b7 e7 b1 b0 e7 b1 ae e7 b1 a8 e7 b1 b2 e7 b1 b7 e7 b1 a8 e7 b1 ba e7 b1 be e7 b1 b2 e7 b1 bd e7 b1 ae e7 b1 a8 e7 b1 bc e7 b1 b8 e7 b1 b6 e7 b1 ae e7 b1 a8 e7 b1 bd e7 b1 b2 e7 b1 b6 e7 b1 ae e7 b2 86'
m = b''
for x in c.split():
    m += bytes.fromhex(x)

m = m.decode('utf-8')

for i in range(256):
    curm = ''
    for x in m:
        curm += chr((ord(x) + i) % 256)

    flag = curm.encode('utf-8')
    if b'ictf' in flag:
        print(flag)
