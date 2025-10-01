from math import gcd

class PhanSo:
    def __init__(self, tu, mau):
        self.tu = tu
        self.mau = mau
        self.__fix()
        
    def __add__(self, other):
        tu = self.tu * other.mau + other.tu * self.mau
        mau = self.mau * other.mau
        return PhanSo(tu, mau)

    def __sub__(self, other):
        tu = self.tu * other.mau - other.tu * self.mau
        mau = self.mau * other.mau
        return PhanSo(tu, mau)

    def __mul__(self, other):
        tu = self.tu * other.tu
        mau = self.mau * other.mau
        return PhanSo(tu, mau)

    def __truediv__(self, other):
        tu = self.tu * other.mau
        mau = self.mau * other.tu
        self.__fix()
        return PhanSo(tu, mau)
    
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
    print("Nhap phan so 1:")
    tu1 = int(input("Tu so: "))
    mau1 = int(input("Mau so: "))
    ps1 = PhanSo(tu1, mau1)
    
    print("Nhap phan so 2:")
    tu2 = int(input("Tu so: "))
    mau2 = int(input("Mau so: "))
    ps2 = PhanSo(tu2, mau2)
    
    print(f"Phan so 1: {ps1}")
    print(f"Phan so 2: {ps2}")
    
    print(f"Tong: {ps1 + ps2}")
    print(f"Hieu: {ps1 - ps2}")
    print(f"Tich: {ps1 * ps2}")
    print(f"Thuong: {ps1 / ps2}")