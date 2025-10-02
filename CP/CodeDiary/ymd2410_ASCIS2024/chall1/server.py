import json
import paillier
import ecc
import dlnproof

from secrets import randbelow
from Crypto.Util.number import *

from secret import flag, P, Q
from mta import *


# paillier key A
_p = getPrime(1024)
_q = getPrime(1024)
pk = paillier.PublicKey(_p * _q)
sk = paillier.PrivateKey(_p, _q)
assert isPrime((P-1)//2)
assert isPrime((Q-1)//2)

print("""
*************************************************************
    Welcome to the MtA Protocol!
    We are developing an Threshhold Signature Scheme,
    so we decided to implement the MtA (Multiplicative to Additive) 
    share conversion protocol to play around how it work.
    Try to find the secret that have been hidden!!!!
*************************************************************
> Start!!!!!
""")

NTildeA = P * Q
Lambda = (P-1)*(Q-1) // 4
h1A = randbelow(NTildeA)
while pow(h1A, Lambda, NTildeA) != 1:
    h1A = pow(h1A, 2, NTildeA)
xi = randbelow(Lambda)
xi_inv = pow(xi, -1, Lambda)
h2A = pow(h1A, xi, NTildeA)

print("Alice Public Key = " + json.dumps({
    "NTildeA": NTildeA,
    "h1A": h1A,
    "h2A": h2A,
    "dlnproof": [
        dlnproof.getDLNProof(h1A, h2A, xi, Lambda, NTildeA),
        dlnproof.getDLNProof(h2A, h1A, xi_inv, Lambda, NTildeA),
    ]
}))

line = json.loads(input("Bob Public Key = "))
NTildeB, h1B, h2B, dln_pf = (line[name] for name in ["NTildeB", "h1B", "h2B", "dlnproof"])

assert dlnproof.verify(h1B, h2B, NTildeB, *dln_pf[0])
assert dlnproof.verify(h2B, h1B, NTildeB, *dln_pf[1])

print("Alice Paillier Public Key = " + json.dumps({
    "N": pk.N
}))

a = int.from_bytes(flag, "big")
assert a < ecc.q
gBPointRaw = bytes.fromhex(input("gBPoint (hex) = "))

gBPoint = PointJacobi.from_bytes(ecc.ec, gBPointRaw)
cA, pf = round1(pk, a, NTildeB, h1B, h2B)
#
print("Round1Msg = " + json.dumps({
    "cA": cA,
    "proofA": pf.__dict__,
}))


r2m = json.loads(input("Round2Msg = "))
cB = r2m["cB"]
pfB = ProofBob.deserialize(r2m["proofB"])

alpha = round3(
    b"hello",
    pk, pfB, gBPoint, NTildeA, h1A, h2A, cA, cB, sk
)

# if the protocol is successful, alpha + beta = a * b
print("Done!!! We will implement more in tbe future")