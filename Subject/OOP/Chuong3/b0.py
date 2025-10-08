'''
Định nghĩa lớp cPhanSo biểu diễn khái niệm phân số gồm 2 
thành phần dữ liệu: tử số, mẫu số và các thao tác:
 - Nhập phân số
 - Khởi tạo tử số và mẫu số cho phân số
 - Xuất phân số
 - Lấy giá trị phấn số
 - Tính tổng 2 phân số
Viết chương trình cho phép người dùng nhập vào 2 phân số, 
tính  tổng  2  phân  số  và  xuất  kết  quả  ra  màn  hình  dưới  dạng 
phân số.
'''

class cPhanSo:
    def __init__(self, tu=0, mau=1):
        self.tu = tu
        self.mau = mau if mau != 0 else 1  # Mẫu số không được bằng 0

    def nhap(self):
        self.tu = int(input("Nhập tử số: "))
        self.mau = int(input("Nhập mẫu số (không được bằng 0): "))
        while self.mau == 0:
            print("Mẫu số không được bằng 0. Vui lòng nhập lại.")
            self.mau = int(input("Nhập mẫu số (không được bằng 0): "))

    def xuat(self):
        print(f"{self.tu}/{self.mau}")

    def gia_tri(self):
        return self.tu / self.mau

    def tong(self, other):
        tu_moi = self.tu * other.mau + other.tu * self.mau
        mau_moi = self.mau * other.mau
        return cPhanSo(tu_moi, mau_moi)