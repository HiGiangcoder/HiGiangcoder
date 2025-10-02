import random
from dataclasses import dataclass
from Crypto.Util.number import GCD
from common import SHA512_256i
import paillier

q = 0xfffffffffffffffffffffffffffffffebaaedce6af48a03bbfd25e8cd0364141


@dataclass
class ProofAlice:
    Z: int
    U: int
    W: int
    S: int
    S1: int
    S2: int


def ProveAliceRange(
    pk: paillier.PublicKey,
    c: int,
    NTilde, h1, h2,
    m: int,
    r: int
):
    N = pk.N
    q3 = q * q * q
    q3NTilde = q3 * NTilde
    qNTilde = q * NTilde
    NSquare = pk.N2

    # 1.
    alpha = random.randint(1, q3 - 1)
    beta = random.randint(1, N - 1)
    while GCD(beta, N) != 1:
        beta = random.randint(1, N - 1)
    gamma = random.randint(1, q3NTilde - 1)
    rho = random.randint(1, qNTilde - 1)

    # h1^m * h2^rho
    # m: 256 bits
    # rho: q * NTilde => 256 * 9 bits
    #
    z = (pow(h1, m, NTilde) * pow(h2, rho, NTilde)) % NTilde
    u = (pow(N + 1, alpha, NSquare) * pow(beta, N, NSquare)) % NSquare
    w = (pow(h1, alpha, NTilde) * pow(h2, gamma, NTilde)) % NTilde

    e = SHA512_256i([N, N + 1, c, z, u, w]) % q

    s = (pow(r, e, N) * beta) % N

    s1 = e * m + alpha
    s2 = e * rho + gamma

    return ProofAlice(z, u, w, s, s1, s2)


def VerifyAlice(
    pf: ProofAlice,
    pk: paillier.PublicKey,
    NTilde, h1, h2,
    c: int
):
    N = pk.N
    q3 = q * q * q
    NSquare = pk.N2

    pf.Z %= NTilde
    pf.U %= NSquare
    pf.W %= NTilde
    pf.S %= N

    if GCD(pf.Z, NTilde) != 1:
        return False

    if GCD(pf.U, N**2) != 1:
        return False

    if GCD(pf.W, NTilde) != 1:
        return False

    if pf.S1 > q3:
        return False

    e = SHA512_256i([N, N + 1, c, pf.Z, pf.U, pf.W]) % q

    minusE = -e

    cExpMinusE = pow(c, minusE, NSquare)
    sExpN = pow(pf.S, N, NSquare)
    gammaExpS1 = pow(N + 1, pf.S1, NSquare)
    products = (gammaExpS1 * sExpN) % NSquare
    products = (products * cExpMinusE) % NSquare

    if pf.U != products:
        return False

    h1ExpS1 = pow(h1, pf.S1, NTilde)
    h2ExpS2 = pow(h2, pf.S2, NTilde)
    zExpMinusE = pow(pf.Z, minusE, NTilde)
    products = (h1ExpS1 * h2ExpS2) % NTilde
    products = (products * zExpMinusE) % NTilde

    if pf.W != products:
        return False

    return True


if __name__ == '__main__':
    from Crypto.Util.number import *
    NTilde = 20198128794572047398059046800657931427203985062045251760936172533864221560669653106445667691978831076298048953188668736235852917296765355504469613297390220570572902517942048385939574361277238435184771455821873082855370244601994919025145871408553267186799875788171848261947368863491518895283097500946816313153189029095800368344242150862360965399672107170707791143648454115018067459502021930311570770374142885328620441215508381811424175550149099897143415601932965619041092782150339862245487195559831433375075315943748906761998355474770238025562778449601492882937496116496725747679394623107966359733545334415547832452947
    phi = 20198128794572047398059046800657931427203985062045251760936172533864221560669653106445667691978831076298048953188668736235852917296765355504469613297390220570572902517942048385939574361277238435184771455821873082855370244601994919025145871408553267186799875788171848261947368863491518895283097500946816313153189029095800368344242150862360965399672107170707791143648454115018067459502021930311570770374142885328620441215508381811424175550149099897143415601932965619041092782150339862245487195559831433375075315943748906761998355474770238025562778449601492882937496116496725747679394623107966359733545334415547832452946
    phi //= 2
    h1 = 4
    assert phi % 2 == 1
    assert pow(h1, phi, NTilde) == 1
    x = 2**256
    h2 = pow(h1, x, NTilde)

    # paillier key
    p = getPrime(1024)
    q = getPrime(1024)
    pk = paillier.PublicKey(p * q)

    # sensitive info
    m = random.randint(1, q - 1)

    c, r = pk.Encrypt(m)

    pf = ProveAliceRange(pk, c, NTilde, h1, h2, m, r)

    assert VerifyAlice(pf, pk, NTilde, h1, h2, c)
