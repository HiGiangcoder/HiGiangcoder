import math

class cComplex:
    def __init__(self, real, imag=0.0):
        self.real = float(real)
        self.imag = float(imag)
        
    def Input(self):
        while True:
            try:
                s = input("Nhap phan thuc va phan ao (cach nhau boi dau cach): ").split()
                assert len(s) == 2
                self.real = float(s[0])
                self.imag = float(s[1])
                break
            except ValueError:
                print("Error: Khac kieu du lieu (yeu cau so thuc).")
            except AssertionError:
                print("Error: Ban phai nhap dung 2 so (phan thuc, phan ao).")

    def Input(self):
        while True:
            try:
                s = input("Nhap so phuc gom phan thuc, phan ao (cach nhau boi dau cach):").split()
                assert len(s) == 2
                self.real = float(s[0])
                self.imag = float(s[1])
                break
            except ValueError:
                print("Error: Khac kieu du lieu")
            except AssertionError:
                print("Error: Ban phai nhap dung 2 so")
        
    def Output(self):
        print(self)

    def __str__(self):
        # dang hien thi a + bi hoac a - bi
        if self.imag >= 0:
            return f"{self.real} + {self.imag}i"
        else:
            return f"{self.real} - {abs(self.imag)}i"

    # cac toan tu
    def __add__(self, other):
        return cComplex(self.real + other.real, self.imag + other.imag)

    def __sub__(self, other):
        return cComplex(self.real - other.real, self.imag - other.imag)

    def __mul__(self, other):
        real = self.real * other.real - self.imag * other.imag
        imag = self.real * other.imag + self.imag * other.real
        return cComplex(real, imag)

    def __truediv__(self, other):
        denom = other.real**2 + other.imag**2
        if denom == 0:
            raise ZeroDivisionError("Khong the chia cho so phuc 0.")
        real = (self.real * other.real + self.imag * other.imag) / denom
        imag = (self.imag * other.real - self.real * other.imag) / denom
        return cComplex(real, imag)

    def __eq__(self, other):
        EPS = 1e-12
        return abs(self.real - other.real) < EPS and abs(self.imag - other.imag) < EPS
