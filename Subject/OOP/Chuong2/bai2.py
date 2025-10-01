from math import gcd

class PhanSo:
    def __init__(self, tu, mau):
        self.tu = tu
        self.mau = mau
        self.__fix()
        
    def __add__(self, other):
        tu = self.tu * other.mau + other.tu * self.mau
        mau = self.mau * other.mau
        self.__fix()
        return PhanSo(tu, mau)
    
    def __lt__(self, value):
        return self.tu * value.mau < value.tu * self.mau
    
    def __fix(self):
        if self.mau == 0:
            raise ValueError("Mau so khong duoc bang 0")
        if self.mau < 0:
            self.tu = -self.tu
            self.mau = -self.mau
        
        self.gcd = gcd(self.tu, self.mau)
        
        if self.tu != 0:
            self.tu //= self.gcd
        self.mau //= self.gcd

    def __str__(self):
        return f"{self.tu}/{self.mau}"
    
if __name__ == "__main__":
    list_ps = []
    n = int(input("Nhap so luong phan so: "))
    for i in range(n):
        print(f"Nhap phan so {i+1}:")
        tu = int(input("Tu so: "))
        mau = int(input("Mau so: "))
        ps = PhanSo(tu, mau)
        list_ps.append(ps)
    
    sum_ps = PhanSo(0, 1)
    max_ps = list_ps[0]
    for ps in list_ps:
        sum_ps += ps
        if ps > max_ps:
            max_ps = ps
    
    print(f"Tong cac phan so: {sum_ps}")
    print(f"Phan so lon nhat: {max_ps}")