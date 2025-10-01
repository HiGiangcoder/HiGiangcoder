from math import gcd

class PhanSo:
    def __init__(self, tu, mau):
        self.tu = tu
        self.mau = mau
        self.__fix()

    def __fix(self):
        if self.mau < 0:
            self.tu = -self.tu
            self.mau = -self.mau
        
        if self.mau == 0:
            raise ValueError("Mau so khong duoc bang 0")
        
        if type(self.tu) is not int or type(self.mau) is not int:
            raise ValueError("Tu so va mau so phai la so nguyen")

        self.gcd = gcd(abs(self.tu), abs(self.mau))
        self.tu //= self.gcd
        self.mau //= self.gcd

    def __eq__(self, value):
        return self.tu == value.tu and self.mau == value.mau

    def __lt__(self, value):
        return self.tu * value.mau < self.mau * value.tu
    
    def __str__(self):
        return f"{self.tu}/{self.mau}"
    
    def __add__(self, value):
        tu = self.tu * value.mau + self.mau * value.tu
        mau = self.mau * value.mau
        return PhanSo(tu, mau)    
    
    def __neg__(self):
        return PhanSo(-self.tu, self.mau)
    
    def __sub__(self, value):
        return self + (-value)
    
    def __mul__(self, value):
        tu = self.tu * value.tu
        mau = self.mau * value.mau
        return PhanSo(tu, mau)
    
    def __truediv__(self, value):
        tu = self.tu * value.mau
        mau = self.mau * value.tu
        return PhanSo(tu, mau)
    
    def Set(self, tu, mau):
        self.tu = tu
        self.mau = mau
        self.__fix()
    
    def Set(self, ps):
        self.tu = ps.tu
        self.mau = ps.mau
        self.__fix()
    
    @classmethod
    def Input(cls):
        tu, mau = map(int, input("Nhap tu va mau (cach nhau boi khoang trang): ").split())
        return cls(tu, mau)

if __name__ == "__main__":

    ps = PhanSo.Input()
    print(ps)

    ps1 = PhanSo.Input()
    ps2 = PhanSo.Input()
    print(f"Phan so lon nhat la: {max(ps1, ps2)}")

    print(f"Tong: {ps1 + ps2}")
    print(f"Hieu: {ps1 - ps2}")
    print(f"Tich: {ps1 * ps2}")
    print(f"Thuong: {ps1 / ps2}")

