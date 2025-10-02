from Crypto.Util.number import long_to_bytes, bytes_to_long

s = 'e7 86 b2 e7 b1 e7 bc b1 ae b1 e7 bd e7 bc b1 e7 b1 e7 a8 b1 b7 b1 e7 bd e7 b2 b1 e7 b1 e7 b8 b1 bc b1 e7 b3 e7 b2 b1 e7 b1 e7 ad b1 b7 b1 e7 a8 e7 ae b1 e7 b1 e7 bd b1 b8 b1 e7 af e7 a8 b1 e7 b1 e7 ae b1 aa b1 e7 bb e7 a8 b1 e7 b1 e7 bc b1 b5 b1 e7 b5 e7 aa b1 e7 b1 e7 b1 b1 a8 b1 e7 ac e7 82 b2 e7 b1 e7 bc b1 ae b1 e7 aa e7 a8 b1 e7 b1 e7 ad b1 aa b1 e7 b7 e7 a8 b1 e7 b1 e7 bc b1 b5 b1 e7 b5 e7 aa b1 e7 b1 e7 b1 b1 a8 b1 e7 ac e7 ae b1 e7 b1 e7 bf b1 bd b1 e7 b2 e7 aa b1 e7 b1 e7 ae b1 8c b1 e7 bb e7 84 b2 e7 b1 e7 af b1 ac b1 e7 bd 00 b2 b1 e7'

s = [int(x, 16) for x in s.split()]

print(bytes_to_long(b'ic'))


numShift = bytes_to_long(b'ic') - s[0]

flag = ''
for x in s:
    flag += long_to_bytes(x + numShift)

print(flag)
