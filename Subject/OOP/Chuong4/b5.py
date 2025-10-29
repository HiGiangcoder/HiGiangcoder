class cBook:
    def __init__(self, ma_sach="", ten_sach="", nam_xuat_ban=0, tong_trang=0):
        self.ma_sach = ma_sach
        self.ten_sach = ten_sach
        self.nam_xuat_ban = nam_xuat_ban
        self.tong_trang = tong_trang

    # Thiết lập thông tin sách
    def set_info(self, ma_sach, ten_sach, nam_xuat_ban, tong_trang):
        self.ma_sach = ma_sach
        self.ten_sach = ten_sach
        self.nam_xuat_ban = nam_xuat_ban
        self.tong_trang = tong_trang

    # Nhập thông tin từ bàn phím
    def input_info(self):
        self.ma_sach = input("Nhập mã sách: ")
        self.ten_sach = input("Nhập tên sách: ")
        while True:
            try:
                self.nam_xuat_ban = int(input("Nhập năm xuất bản: "))
                break
            except ValueError:
                print("Lỗi: vui lòng nhập số nguyên cho năm xuất bản.")
        while True:
            try:
                self.tong_trang = int(input("Nhập tổng số trang: "))
                break
            except ValueError:
                print("Lỗi: vui lòng nhập số nguyên cho tổng số trang.")

    # Xuất thông tin sách
    def output_info(self):
        print(f"Mã sách: {self.ma_sach}")
        print(f"Tên sách: {self.ten_sach}")
        print(f"Năm xuất bản: {self.nam_xuat_ban}")
        print(f"Tổng số trang: {self.tong_trang}")

    # Truy vấn thông tin
    def get_info(self):
        return {
            "ma_sach": self.ma_sach,
            "ten_sach": self.ten_sach,
            "nam_xuat_ban": self.nam_xuat_ban,
            "tong_trang": self.tong_trang
        }

    # Cập nhật thông tin
    def update_info(self, ma_sach=None, ten_sach=None, nam_xuat_ban=None, tong_trang=None):
        if ma_sach is not None:
            self.ma_sach = ma_sach
        if ten_sach is not None:
            self.ten_sach = ten_sach
        if nam_xuat_ban is not None:
            self.nam_xuat_ban = nam_xuat_ban
        if tong_trang is not None:
            self.tong_trang = tong_trang
