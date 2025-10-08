'''
5.  Định  nghĩa  lớp  cHocSinh  gồm  các  thuộc  tính: 
mã, họ tên, giới tính, năm sinh, điểm trung bình và 
các phương thức cần thiết.
Viết chương trình cho phép người dùng nhập thông 
tin 2 học sinh.
- Cho biết học sinh nào có điểm trung bình cao hơn.
- Cho biết học sinh nào có tuổi nhỏ hơn
'''

class cBook:
    def __init__(self, ma_sach="", ten_sach="", nam_xuat_ban=0, tong_so_trang=0):
        self.ma_sach = ma_sach
        self.ten_sach = ten_sach
        self.nam_xuat_ban = nam_xuat_ban
        self.tong_so_trang = tong_so_trang

    def nhap(self):
        self.ma_sach = input("Nhập mã sách: ")
        self.ten_sach = input("Nhập tên sách: ")
        self.nam_xuat_ban = int(input("Nhập năm xuất bản: "))
        self.tong_so_trang = int(input("Nhập tổng số trang: "))

    def xuat(self):
        print(f"Mã sách: {self.ma_sach}, Tên sách: {self.ten_sach}, Năm xuất bản: {self.nam_xuat_ban}, Tổng số trang: {self.tong_so_trang}")

    def cap_nhat(self, ma_sach=None, ten_sach=None, nam_xuat_ban=None, tong_so_trang=None):
        if ma_sach is not None:
            self.ma_sach = ma_sach
        if ten_sach is not None:
            self.ten_sach = ten_sach
        if nam_xuat_ban is not None:
            self.nam_xuat_ban = nam_xuat_ban
        if tong_so_trang is not None:
            self.tong_so_trang = tong_so_trang
    def truy_van(self):
        return {
            "ma_sach": self.ma_sach,
            "ten_sach": self.ten_sach,
            "nam_xuat_ban": self.nam_xuat_ban,
            "tong_so_trang": self.tong_so_trang
        }
class cListBook:
    def __init__(self):
        self.danh_sach_sach = []

    def nhap_danh_sach(self):
        n = int(input("Nhập số lượng sách: "))
        for _ in range(n):
            sach = cBook()
            sach.nhap()
            self.danh_sach_sach.append(sach)

    def xuat_danh_sach(self):
        for sach in self.danh_sach_sach:
            sach.xuat()

    def sach_moi_nhat(self):
        if not self.danh_sach_sach:
            print("Danh sách sách trống.")
            return None
        sach_moi_nhat = max(self.danh_sach_sach, key=lambda sach: sach.nam_xuat_ban)
        print("Sách được xuất bản gần đây nhất:")
        sach_moi_nhat.xuat()
        return sach_moi_nhat

if __name__ == "__main__":
    danh_sach = cListBook()
    danh_sach.nhap_danh_sach()
    print("\nDanh sách sách:")
    danh_sach.xuat_danh_sach()
    danh_sach.sach_moi_nhat()