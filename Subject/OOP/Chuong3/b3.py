'''
3. Viết chương trình nhập vào tọa độ 2 điểm trong mặt
phẳng Oxy. Tính khoảng cách giữa chúng và xuất kết
quả.
'''

import math
class Diem:
    def __init__(self, x=0, y=0):
        self.x = x
        self.y = y

    def nhap(self):
        self.x = float(input("Nhập hoành độ (x): "))
        self.y = float(input("Nhập tung độ (y): "))

    def xuat(self):
        print(f"Điểm({self.x}, {self.y})")

    def khoang_cach(self, other):
        return math.sqrt((self.x - other.x) ** 2 + (self.y - other.y) ** 2)

if __name__ == "__main__":
    print("Nhập điểm thứ nhất:")
    diem1 = Diem()
    diem1.nhap()
    
    print("Nhập điểm thứ hai:")
    diem2 = Diem()
    diem2.nhap()
    
    diem1.xuat()
    diem2.xuat()
    
    print(f"Khoảng cách giữa hai điểm: {diem1.khoang_cach(diem2)}")