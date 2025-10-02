from secrets import randbelow
from dataclasses import dataclass, field
from Crypto.Util.number import GCD

def L(u: int, N: int):
    return (u - 1) // N

@dataclass
class PublicKey():
    N: int
    N2: int = field(init=False)
    Gamma: int = field(init=False)

    def __post_init__(self):
        self.N2 = self.N * self.N
        self.Gamma = self.N + 1

    def Encrypt(self, m: int):
        N = self.N
        N2 = self.N2
        r: int = randbelow(N)
        while GCD(r, N) != 1:
            r = randbelow(N)
        Gm = pow(self.Gamma, m, N2)
        xN = pow(r, N, N2)
        c = (Gm * xN) % N2
        return c, r

    def HomoMult(self, m: int, c1: int):
        N2 = self.N2
        return pow(c1, m, N2)

    def HomoAdd(self, c1: int, c2: int):
        N2 = self.N2
        return (c1 * c2) % N2


@dataclass
class PrivateKey():
    P: int
    Q: int
    Pk: PublicKey = field(init=False)
    LambdaN: int = field(init=False)
    PhiN: int = field(init=False)

    def __post_init__(self):
        self.Pk = PublicKey(self.P * self.Q)
        self.PhiN = (self.P - 1) * (self.Q - 1)
        self.LambdaN = self.PhiN // GCD(self.P - 1, self.Q - 1)

    def Decrypt(self, c: int):
        N  = self.Pk.N
        N2 = self.Pk.N2
        
        # 1. L(u) = (c^LambdaN-1 mod N2) / N
        Lc = L(pow(c, self.LambdaN, N2), N)
        # 2. L(u) = (Gamma^LambdaN-1 mod N2) / N
        Lg = L(pow(self.Pk.Gamma, self.LambdaN, N2), N)
        # 3. (1) * modInv(2) mod N
        inv = pow(Lg, -1, N)
        return (Lc * inv) % N


if __name__ == "__main__":
    from Crypto.Util.number import *
    # paillier key A
    p = getPrime(1024)
    q = getPrime(1024)
    pk = PublicKey(p * q)
    sk = PrivateKey(p, q)
    assert sk.Decrypt(pk.Encrypt(12345)[0]) == 12345
