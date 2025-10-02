from Crypto.Util.number import long_to_bytes
c = '1a 10 07 15 08 1e 12 1d 17 12 07 1c 01 0a 2c 0b 1c 01 2c 10 1b 12 1f 1f 2c 4a 41 40 11 12 10 46 47 4a 0e'
c = c.split()
c = [int(x, 16) for x in c]

for i in range(2**8):
    flag = b''
    for x in c:
        flag += long_to_bytes(x^i)
    if b'ictf' in flag:
        print(flag)

# ictf{mandatory_xor_chall_923bac549}'

