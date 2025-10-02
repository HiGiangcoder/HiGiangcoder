from ecdsa.curves import NIST256p, Curve
from ecdsa.ellipticcurve import PointJacobi

ec: Curve = NIST256p.curve
G: PointJacobi = NIST256p.generator
q = int(NIST256p.order)
p = int(ec.p())
a = int(ec.a())
b = int(ec.b())
