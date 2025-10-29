'''
2. Viết  chương  trình  nhập  tọa  độ  tâm  và  bán  kính  của 
đường tròn. Tính diện tích và chu vi của đường tròn.
'''

import math
class DuongTron:
    def __init__(self, x=0, y=0, r=1):
        self.x = x  # Tọa độ x của tâm
        self.y = y  # Tọa độ y của tâm
        self.r = r  # Bán kính

    def nhap(self):
        self.x = float(input("Nhập tọa độ x của tâm: "))
        self.y = float(input("Nhập tọa độ y của tâm: "))
        self.r = float(input("Nhập bán kính: "))
        if self.r < 0:
            print("Bán kính không thể âm. Đặt lại bán kính thành 1.")
            self.r = 1

    def xuat(self):
        print(f"Tâm: ({self.x}, {self.y}), Bán kính: {self.r}")

    def dien_tich(self):
        return math.pi * self.r ** 2

    def chu_vi(self):
        return 2 * math.pi * self.r

if __name__ == "__main__":
    dt = DuongTron()
    dt.nhap()
    dt.xuat()
    print(f"Diện tích: {dt.dien_tich()}")
    print(f"Chu vi: {dt.chu_vi()}")