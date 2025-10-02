from Crypto.Util.number import long_to_bytes, bytes_to_long
from hashlib import sha256


def SHA512_256i_TAGGED(tag: bytes, ints: list[int]):
    ints.append(int.from_bytes(tag, 'big'))
    return SHA512_256i(ints)


def SHA512_256i(ints):
    msg = b','.join([long_to_bytes(i) for i in ints])
    return bytes_to_long(sha256(msg).digest())


def long_to_bin(num):
    return list(map(int, bin(num)[2:].zfill(256)))
