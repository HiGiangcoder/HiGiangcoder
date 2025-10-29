import math

class PhanSo:
    def __init__(self, tu=0, mau=1):
        if mau == 0:
            raise ValueError("Mau so khong duoc bang 0.")
        self.tuso = tu
        self.mauso = mau
        self.RutGon()

    # --- Các hàm nhập/xuất ---
    def Nhap(self):
        while True:
            try:
                s = input("Nhap tu so va mau so (cach nhau boi dau cach): ").split()
                assert len(s) == 2
                tu = int(s[0])
                mau = int(s[1])
                assert mau != 0
                self.tuso, self.mauso = tu, mau
                self.RutGon()
                break
            except ValueError:
                print("Error: Khac kieu du lieu (yeu cau so nguyen).")
            except AssertionError:
                print("Error: Mau so phai khac 0 va nhap dung 2 so!")

    def Xuat(self):
        print(self)

    def __str__(self):
        if self.mauso == 1:
            return f"{self.tuso}"
        return f"{self.tuso}/{self.mauso}"

    # --- Các hàm tiện ích ---
    def RutGon(self):
        ucln = math.gcd(self.tuso, self.mauso)
        if self.mauso < 0:
            ucln = -ucln  # đổi dấu để mẫu dương
        self.tuso //= ucln
        self.mauso //= ucln

    def GiaTri(self):
        return self.tuso / self.mauso

    # --- Toán tử ---
    def __add__(self, other):
        tu = self.tuso * other.mauso + other.tuso * self.mauso
        mau = self.mauso * other.mauso
        return PhanSo(tu, mau)

    def __sub__(self, other):
        tu = self.tuso * other.mauso - other.tuso * self.mauso
        mau = self.mauso * other.mauso
        return PhanSo(tu, mau)

    def __gt__(self, other):
        return self.GiaTri() > other.GiaTri()

    def __eq__(self, other):
        return self.tuso == other.tuso and self.mauso == other.mauso


class DSPhanSo:
    def __init__(self):
        self.arr = []

    def Size(self):
        return len(self.arr)

    def Input(self, n):
        self.arr = []
        for i in range(n):
            print(f"Nhap phan so thu {i+1}:")
            ps = PhanSo()
            ps.Nhap()
            self.arr.append(ps)

    def Output(self):
        print(f"Danh sach {self.Size()} phan so:")
        for i, ps in enumerate(self.arr, 1):
            print(f"[{i}] {ps}")

    def Tong(self):
        if not self.arr:
            return PhanSo(0, 1)
        tong = PhanSo(0, 1)
        for ps in self.arr:
            tong = tong + ps
        return tong

    def LonNhat(self):
        if not self.arr:
            return None
        return max(self.arr, key=lambda x: x.GiaTri())

    def __str__(self):
        return "{" + ", ".join(str(x) for x in self.arr) + "}"

# test
if __name__ == "__main__":
    print("=== Chuong trinh xu ly phan so ===")

    # Phần a: kiểm tra toán tử >
    a = PhanSo(1, 2)
    b = PhanSo(3, 5)
    print(f"a = {a}, b = {b}")
    print(f"a > b ? {a > b}")

    # Phần b, c: dùng lớp DSPhanSo
    print("\n=== Nhap danh sach phan so ===")
    n = int(input("Nhap so luong phan so: "))
    ds = DSPhanSo()
    ds.Input(n)

    print("\n=== Danh sach phan so vua nhap ===")
    ds.Output()

    tong = ds.Tong()
    lonnhat = ds.LonNhat()

    print(f"\nTong cac phan so = {tong}")
    print(f"Phan so lon nhat = {lonnhat}")
