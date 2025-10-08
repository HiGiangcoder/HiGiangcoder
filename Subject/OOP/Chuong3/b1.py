'''
1. Viết chương trình nhập họ tên, điểm toán, điểm văn
của một học sinh. Tính điểm trung bình,  xếp  loại và
xuất kết quả.
'''

class HocSinh:
    def __init__(self, ho_ten="", diem_toan=0.0, diem_van=0.0):
        self.ho_ten = ho_ten
        self.diem_toan = diem_toan
        self.diem_van = diem_van

    def nhap(self):
        self.ho_ten = input("Nhập họ tên học sinh: ")
        self.diem_toan = float(input("Nhập điểm toán: "))
        self.diem_van = float(input("Nhập điểm văn: "))

    def diem_trung_binh(self):
        return (self.diem_toan + self.diem_van) / 2

    def xep_loai(self):
        dtb = self.diem_trung_binh()
        if dtb >= 8:
            return "Giỏi"
        elif dtb >= 6.5:
            return "Khá"
        elif dtb >= 5:
            return "Trung bình"
        else:
            return "Yếu"

    def xuat(self):
        print(f"Họ tên: {self.ho_ten}")
        print(f"Điểm Toán: {self.diem_toan}")
        print(f"Điểm Văn: {self.diem_van}")
        print(f"Điểm Trung Bình: {self.diem_trung_binh()}")
        print(f"Xếp loại: {self.xep_loai()}")

if __name__ == "__main__":
    hs = HocSinh()
    hs.nhap()
    hs.xuat()