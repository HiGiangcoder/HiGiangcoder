class DaThuc:
    def __init__(self, bac=0, he_so=None):
        self.bac = bac
        if he_so is None:
            self.he_so = [0]*(bac+1)
        else:
            
            if len(he_so) != bac + 1:
                raise ValueError("Số hệ số không đúng với bậc")
            self.he_so = he_so[:]  

   
    def input_dathuc(self):
        self.bac = int(input("Nhập bậc của đa thức: "))
        self.he_so = []
        for i in range(self.bac, -1, -1):
            a = float(input(f"Nhập hệ số của x^{i}: "))
            self.he_so.append(a)
        self.he_so.reverse() 

    def __str__(self):
        terms = []
        n = self.bac
        for i in range(n + 1):
            a = self.he_so[i]
            b = n - i
            if a == 0:
                continue
            if b == 0:
                terms.append(f"{a}")
            elif b == 1:
                terms.append(f"{a}x")
            else:
                terms.append(f"{a}x^{b}")
        return " + ".join(terms) if terms else "0"

    def evaluate(self, x):
        result = 0
        n = self.bac
        for i in range(n + 1):
            result += self.he_so[i] * (x ** (n - i))
        return result

    def __add__(self, other):
        max_bac = max(self.bac, other.bac)
        he_so1 = [0]*(max_bac - self.bac) + self.he_so
        he_so2 = [0]*(max_bac - other.bac) + other.he_so
        he_so_tong = [he_so1[i] + he_so2[i] for i in range(max_bac + 1)]
        return DaThuc(max_bac, he_so_tong)

    def __sub__(self, other):
        max_bac = max(self.bac, other.bac)
        he_so1 = [0]*(max_bac - self.bac) + self.he_so
        he_so2 = [0]*(max_bac - other.bac) + other.he_so
        he_so_hieu = [he_so1[i] - he_so2[i] for i in range(max_bac + 1)]
        return DaThuc(max_bac, he_so_hieu)
