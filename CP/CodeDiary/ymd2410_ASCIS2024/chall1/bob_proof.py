import ecc
import paillier
import common

from Crypto.Util.number import GCD
from dataclasses import dataclass
from secrets import randbelow
from ecc import PointJacobi, q, G


@dataclass
class ProofBob:
    Z: int
    ZPrm: int
    T: int
    V: int
    W: int
    S: int
    S1: int
    S2: int
    T1: int
    T2: int
    U: PointJacobi
    
    def serialize(self):
        return {
            "Z": self.Z,
            "ZPrm": self.ZPrm,
            "T": self.T,
            "V": self.V,
            "W": self.W,
            "S": self.S,
            "S1": self.S1,
            "S2": self.S2,
            "T1": self.T1,
            "T2": self.T2,
            "U": self.U.to_bytes().hex()
        }
    
    @staticmethod
    def deserialize(raw):
        U = PointJacobi.from_bytes(ecc.ec, bytes.fromhex(raw["U"]))
        return ProofBob(
            raw["Z"],
            raw["ZPrm"],
            raw["T"],
            raw["V"],
            raw["W"],
            raw["S"],
            raw["S1"],
            raw["S2"],
            raw["T1"],
            raw["T2"],
            U
        )


def ProveBob(
    Session: bytes,
    pk: paillier.PublicKey,
    NTilde, h1, h2,
    c1: int, c2: int,
    x: int,
    y: int,
    r: int,
    X: PointJacobi
):
    N = pk.N
    N2 = pk.N2

    q3 = q**3
    q7 = q**7
    qNTilde = q * NTilde
    q3NTilde = q3 * NTilde

    # steps are numbered as shown in Fig. 10, but diverge slightly for Fig. 11
    # 1.
    alpha = randbelow(q3)

    # 2.
    rho = randbelow(qNTilde)
    sigma = randbelow(qNTilde)
    tau = randbelow(q3NTilde)

    # 3.
    rhoPrm = randbelow(q3NTilde)

    # 4.
    beta = randbelow(N)

    gamma = randbelow(q7)

    # 5.
    u = alpha * G

    # 6.
    z = pow(h1, x, NTilde)
    z *= pow(h2, rho, NTilde)
    z %= NTilde

    # 7.
    zPrm = pow(h1, alpha, NTilde)
    zPrm *= pow(h2, rhoPrm, NTilde)
    zPrm %= NTilde

    # 8.
    t = pow(h1, y, NTilde)
    t *= pow(h2, sigma, NTilde)
    t %= NTilde

    # 9.
    v = pow(c1, alpha, N2)
    v *= pow(pk.Gamma, gamma, N2)
    v %= N2
    v *= pow(beta, N, N2)
    v %= N2

    # 10.
    w = pow(h1, gamma, NTilde)
    w *= pow(h2, tau, NTilde)
    w %= NTilde

    # 11-12. e'
    eHash = common.SHA512_256i_TAGGED(
        Session,
        [N, X.x(), X.y(), c1, c2, u.x(), u.y(), z, zPrm, t, v, w]
    )
    e = eHash % q

    # 13.
    s = pow(r, e, N)
    s *= beta
    s %= N

    # 14.
    s1 = e * x + alpha

    # 15.
    s2 = e * rho + rhoPrm

    # 16.
    t1 = e * y + gamma

    # 17.
    t2 = e * sigma + tau

    return ProofBob(z, zPrm, t, v, w, s, s1, s2, t1, t2, u)


def VerifyBob(
    pf: ProofBob,
    Session: bytes,
    pk: paillier.PublicKey,
    NTilde, h1, h2,
    c1: int, c2: int,
    X: PointJacobi
):
    N = pk.N
    N2 = pk.N2
    q3 = q**3
    q7 = q**7

    pf.Z %= NTilde
    pf.ZPrm %= NTilde
    pf.T %= NTilde
    pf.V %= N2
    pf.W %= NTilde
    pf.S %= N
    pf.V %= N

    if GCD(pf.Z, NTilde) != 1:
        return False
    if GCD(pf.ZPrm, NTilde) != 1:
        return False
    if GCD(pf.T, NTilde) != 1:
        return False
    if GCD(pf.V, N2) != 1:
        return False
    if GCD(pf.W, NTilde) != 1:
        return False
    if GCD(pf.S, N) != 1:
        return False
    if GCD(pf.V, N) != 1:
        return False

    if pf.S1 < q:
        return False
    if pf.S2 < q:
        return False
    if pf.T1 < q:
        return False
    if pf.T2 < q:
        return False

    # 3.
    if pf.S1 > q3:
        return False
    if pf.T1 > q7:
        return False
    # 1-2. e'
    eHash = common.SHA512_256i_TAGGED(
        Session,
        [N, X.x(), X.y(), c1, c2, pf.U.x(), pf.U.y(),
         pf.Z, pf.ZPrm, pf.T, pf.V, pf.W]
    )
    e = eHash % q

    # 4. runs only in the "with check" mode from Fig. 10
    s1ModQ = pf.S1 % q
    gS1 = s1ModQ * G
    xEU = e * X + pf.U
    if gS1 != xEU:
        return False

    # 5.
    h1ExpS1 = pow(h1, pf.S1, NTilde)
    h2ExpS2 = pow(h2, pf.S2, NTilde)
    left = (h1ExpS1 * h2ExpS2) % NTilde
    zExpE = pow(pf.Z, e, NTilde)
    right = (zExpE * pf.ZPrm) % NTilde
    if left != right:
        return False

    # 6.
    h1ExpT1 = pow(h1, pf.T1, NTilde)
    h2ExpT2 = pow(h2, pf.T2, NTilde)
    left = (h1ExpT1 * h2ExpT2) % NTilde
    tExpE = pow(pf.T, e, NTilde)
    right = (tExpE * pf.W) % NTilde
    if left != right:
        return False

    # 7.
    c1ExpS1 = pow(c1, pf.S1, N2)
    sExpN = pow(pf.S, N, N2)
    gammaExpT1 = pow(pk.Gamma, pf.T1, N2)
    left = (c1ExpS1 * sExpN) % N2
    left = (left * gammaExpT1) % N2
    c2ExpE = pow(c2, e, N2)
    right = (c2ExpE * pf.V) % N2
    if left != right:
        return False

    return True
