import random
import math

class PhanSo:
    def __init__(self, tu, mau):
        if mau == 0:
            raise ValueError("Mẫu số không được bằng 0")
        self.tu = tu
        self.mau = mau
        self.rut_gon()

    # Rút gọn phân số
    def rut_gon(self):
        gcd = math.gcd(self.tu, self.mau)
        self.tu //= gcd
        self.mau //= gcd
        if self.mau < 0:   # đảm bảo mẫu dương
            self.tu *= -1
            self.mau *= -1

    # Chuyển sang float để so sánh
    def value(self):
        return self.tu / self.mau

    # So sánh <, <=, >
    def __lt__(self, other):
        return self.tu * other.mau < other.tu * self.mau

    def __le__(self, other):
        return self.tu * other.mau <= other.tu * self.mau

    def __str__(self):
        return f"{self.tu}/{self.mau}"

# Kiểm tra số nguyên tố
def is_prime(n):
    if n < 2:
        return False
    for i in range(2, int(n**0.5)+1):
        if n % i == 0:
            return False
    return True

class arrPhanSo:
    def __init__(self):
        self.arr = []

    def input_frac(self, n):
        self.arr = []
        for i in range(n):
            while True:
                try:
                    tu = int(input(f"Tử số phân số {i+1}: "))
                    mau = int(input(f"Mẫu số phân số {i+1}: "))
                    self.arr.append(PhanSo(tu, mau))
                    break
                except ValueError as e:
                    print("Lỗi:", e)

    def output(self):
        print("Danh sách phân số:", [str(f) for f in self.arr])

    def make_random(self, n, max_value=10):
        self.arr = [PhanSo(random.randint(1, max_value), random.randint(1, max_value)) for _ in range(n)]

    def max_frac(self):
        if not self.arr:
            return None
        max_f = self.arr[0]
        for f in self.arr[1:]:
            if f > max_f:
                max_f = f
        return max_f
    
    def count_prime_numerators(self):
        return sum(1 for f in self.arr if is_prime(f.tu))

    def sort_ascending(self):
        self.arr.sort()
