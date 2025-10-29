# schema_full_filled_fixed.py
import sqlite3
import random
from faker import Faker
from datetime import datetime

# --- Khởi tạo faker và seed
fake = Faker("vi_VN")
random.seed(42)

# --- Kết nối database
conn = sqlite3.connect("db_UIT.db")
cur = conn.cursor()

# ============================
# 1. TẠO CÁC BẢNG DANH MỤC
# ============================
cur.execute("""
CREATE TABLE IF NOT EXISTS Khoa (
    MaKhoa TEXT PRIMARY KEY,
    TenKhoa TEXT NOT NULL
)
""")

cur.execute("""
CREATE TABLE IF NOT EXISTS TinhTP (
    MaTinh TEXT PRIMARY KEY,
    TenTinh TEXT NOT NULL
)
""")

cur.execute("""
CREATE TABLE IF NOT EXISTS LopSH (
    MaLop TEXT PRIMARY KEY,
    TenLop TEXT NOT NULL,
    MaKhoa TEXT,
    FOREIGN KEY (MaKhoa) REFERENCES Khoa(MaKhoa)
)
""")

cur.execute("""
CREATE TABLE IF NOT EXISTS Hedt (
    MaHedt TEXT PRIMARY KEY,
    TenHedt TEXT NOT NULL
)
""")

cur.execute("""
CREATE TABLE IF NOT EXISTS ChuyenNganh (
    MaCN TEXT PRIMARY KEY,
    TenCN TEXT NOT NULL
)
""")

cur.execute("""
CREATE TABLE IF NOT EXISTS TinhTrang (
    MaTT INTEGER PRIMARY KEY,
    MoTa TEXT NOT NULL
)
""")

cur.execute("""
CREATE TABLE IF NOT EXISTS MoCoi (
    MaMC INTEGER PRIMARY KEY,
    MoTa TEXT NOT NULL
)
""")
conn.commit()

# ============================
# 2. TẠO CÁC BẢNG CHÍNH
# ============================
cur.execute("""
CREATE TABLE IF NOT EXISTS SV (
    MaSV TEXT PRIMARY KEY CHECK (LENGTH(MaSV) = 10),
    HoTen TEXT NOT NULL CHECK (LENGTH(HoTen) <= 50),
    NgaySinh TEXT NOT NULL,
    NoiSinh_Tinhtp TEXT,
    NoiSinh_Phuongxa TEXT,
    Email TEXT,
    DienThoai TEXT CHECK (LENGTH(DienThoai) = 10),
    GioiTinh INTEGER CHECK (GioiTinh IN (0, 1)),
    CCCD TEXT NOT NULL UNIQUE CHECK (LENGTH(CCCD) = 12),
    CCCD_NgayCap TEXT,
    CCCD_NoiCap TEXT,
    TamTru TEXT,
    TamTru_Tinhtp TEXT,
    TamTru_Phuongxa TEXT,
    ThuongTru TEXT,
    LopSH TEXT,
    KhoaHoc TEXT,
    Khoa TEXT,
    Hedt TEXT,
    ChuyenNganh TEXT,
    TinhTrang INTEGER,
    MoCoi INTEGER,
    FOREIGN KEY (LopSH) REFERENCES LopSH(MaLop),
    FOREIGN KEY (Khoa) REFERENCES Khoa(MaKhoa),
    FOREIGN KEY (Hedt) REFERENCES Hedt(MaHedt),
    FOREIGN KEY (ChuyenNganh) REFERENCES ChuyenNganh(MaCN),
    FOREIGN KEY (TinhTrang) REFERENCES TinhTrang(MaTT),
    FOREIGN KEY (MoCoi) REFERENCES MoCoi(MaMC)
)
""")

cur.execute("""
CREATE TABLE IF NOT EXISTS MonHoc (
    MaMH TEXT PRIMARY KEY,
    TenMH TEXT NOT NULL,
    KhoaQL TEXT,
    SoTinChi INTEGER CHECK (SoTinChi > 0),
    FOREIGN KEY (KhoaQL) REFERENCES Khoa(MaKhoa)
)
""")

cur.execute("""
CREATE TABLE IF NOT EXISTS TKB (
    MaMH TEXT NOT NULL,
    MaLop TEXT PRIMARY KEY,
    TgianHoc TEXT,
    TGDay TEXT,
    LT_HT TEXT CHECK (LT_HT IN ('LT','HT1','HT2')),
    ThucHanh INTEGER CHECK (ThucHanh IN (0,1)),
    HK INTEGER CHECK (HK BETWEEN 1 AND 3),
    NH TEXT,
    TinhTrang INTEGER CHECK (TinhTrang IN (0,1,2)),
    FOREIGN KEY (MaMH) REFERENCES MonHoc(MaMH)
)
""")

cur.execute("""
CREATE TABLE IF NOT EXISTS DKHP (
    MaDK INTEGER PRIMARY KEY AUTOINCREMENT,
    MaSV TEXT NOT NULL,
    MaLop TEXT NOT NULL,
    TGianDangKy TEXT NOT NULL,
    FOREIGN KEY (MaSV) REFERENCES SV(MaSV),
    FOREIGN KEY (MaLop) REFERENCES TKB(MaLop)
)
""")

cur.execute("""
CREATE TABLE IF NOT EXISTS DKHP_Luu (
    MaLuu INTEGER PRIMARY KEY AUTOINCREMENT,
    MaSV TEXT NOT NULL,
    MaLop TEXT NOT NULL,
    TGianDangKy TEXT NOT NULL,
    FOREIGN KEY (MaSV) REFERENCES SV(MaSV),
    FOREIGN KEY (MaLop) REFERENCES TKB(MaLop)
)
""")

cur.execute("""
CREATE TABLE IF NOT EXISTS Diem (
    MaSV TEXT NOT NULL,
    MaLop TEXT NOT NULL,
    MaMH TEXT NOT NULL,
    DTB REAL CHECK (DTB BETWEEN 0 AND 10),
    PRIMARY KEY (MaSV, MaLop, MaMH),
    FOREIGN KEY (MaSV) REFERENCES SV(MaSV),
    FOREIGN KEY (MaMH) REFERENCES MonHoc(MaMH),
    FOREIGN KEY (MaLop) REFERENCES TKB(MaLop)
)
""")
conn.commit()

# ============================
# 3. DỮ LIỆU DANH MỤC
# ============================
cur.executemany("INSERT OR IGNORE INTO Khoa VALUES (?, ?)", [
    ("CNTT", "Công nghệ thông tin"),
    ("DTVT", "Điện tử - Viễn thông"),
    ("CK", "Cơ khí"),
    ("KT", "Kinh tế")
])

cur.executemany("INSERT OR IGNORE INTO TinhTP VALUES (?, ?)", [
    ("HCM", "TP. Hồ Chí Minh"),
    ("HN", "Hà Nội"),
    ("DN", "Đà Nẵng"),
    ("CT", "Cần Thơ"),
    ("BD", "Bình Dương"),
    ("HP", "Hải Phòng"),
    ("NA", "Nghệ An"),
    ("QN", "Quảng Nam")
])

cur.executemany("INSERT OR IGNORE INTO LopSH VALUES (?, ?, ?)", [
    ("DHKTPM18A", "DHKTPM18A", "CNTT"),
    ("DHKTPM18B", "DHKTPM18B", "CNTT"),
    ("DHMMT18A", "DHMMT18A", "CNTT"),
    ("DHMMT18B", "DHMMT18B", "CNTT"),
    ("DHHTTT18A", "DHHTTT18A", "CNTT")
])

cur.executemany("INSERT OR IGNORE INTO Hedt VALUES (?, ?)", [
    ("DH", "Đại học"),
    ("CD", "Cao đẳng")
])

cur.executemany("INSERT OR IGNORE INTO ChuyenNganh VALUES (?, ?)", [
    ("CNPM", "Kỹ thuật phần mềm"),
    ("MMT", "Mạng máy tính"),
    ("AI", "Trí tuệ nhân tạo"),
    ("DS", "Khoa học dữ liệu")
])

cur.executemany("INSERT OR IGNORE INTO TinhTrang VALUES (?, ?)", [
    (1, "Đang học"),
    (2, "Bảo lưu"),
    (3, "Đình chỉ"),
    (4, "Tốt nghiệp")
])

cur.executemany("INSERT OR IGNORE INTO MoCoi VALUES (?, ?)", [
    (1, "Đủ cha mẹ"),
    (2, "Mồ côi cha hoặc mẹ"),
    (3, "Mồ côi cả cha mẹ")
])
conn.commit()

# ============================
# 4. SINH DỮ LIỆU GIẢ
# ============================
monhoc_data = [
    ("CT101", "Lập trình C", "CNTT", 3),
    ("CT102", "Cấu trúc dữ liệu", "CNTT", 3),
    ("CT103", "Cơ sở dữ liệu", "CNTT", 3),
    ("CT104", "Toán rời rạc", "CNTT", 2),
    ("CT105", "Hệ điều hành", "CNTT", 3),
    ("CT201", "Mạng máy tính", "CNTT", 3),
    ("CT202", "Kỹ thuật phần mềm", "CNTT", 3),
    ("CT203", "Trí tuệ nhân tạo", "CNTT", 3),
    ("CT204", "Xử lý ảnh", "CNTT", 3),
    ("CT205", "Công nghệ web", "CNTT", 2)
]
cur.executemany("INSERT OR IGNORE INTO MonHoc VALUES (?, ?, ?, ?)", monhoc_data)

tkb_data = []
for MaMH, _, KhoaQL, _ in monhoc_data:
    for sec in range(1, 3):
        MaLop = f"{MaMH}_L{sec}"
        TgianHoc = random.choice(["7:00-9:30", "9:30-12:00", "13:00-15:30"])
        TGDay = random.choice(["Thứ 2", "Thứ 3", "Thứ 4", "Thứ 5", "Thứ 6"])
        LT_HT = random.choice(["LT", "HT1", "HT2"])
        ThucHanh = random.choice([0, 1])
        HK = random.choice([1, 2])
        NH = random.choice(["2023-2024", "2024-2025"])
        TinhTrang = random.choice([0, 1, 2])
        tkb_data.append((MaMH, MaLop, TgianHoc, TGDay, LT_HT, ThucHanh, HK, NH, TinhTrang))
cur.executemany("INSERT OR IGNORE INTO TKB VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)", tkb_data)
conn.commit()

# --- Sinh 5000 sinh viên
N = 5000
students = []
used_cccd, used_phone = set(), set()

def gen_unique_number_str(length, used):
    while True:
        n = str(random.randint(10**(length-1), 10**length - 1))
        if n not in used:
            used.add(n)
            return n

lop_list = [r[0] for r in cur.execute("SELECT MaLop FROM LopSH").fetchall()]
khoa_list = [r[0] for r in cur.execute("SELECT MaKhoa FROM Khoa").fetchall()]
hedt_list = [r[0] for r in cur.execute("SELECT MaHedt FROM Hedt").fetchall()]
cn_list = [r[0] for r in cur.execute("SELECT MaCN FROM ChuyenNganh").fetchall()]
tt_list = [r[0] for r in cur.execute("SELECT MaTT FROM TinhTrang").fetchall()]
mc_list = [r[0] for r in cur.execute("SELECT MaMC FROM MoCoi").fetchall()]
tinh_list = [r[0] for r in cur.execute("SELECT TenTinh FROM TinhTP").fetchall()]

for i in range(N):
    MaSV = f"{2025000000 + i}"
    HoTen = fake.name()
    NgaySinh = fake.date_of_birth(minimum_age=18, maximum_age=22).strftime("%Y-%m-%d")
    GioiTinh = random.choice([0, 1])
    CCCD = gen_unique_number_str(12, used_cccd)
    CCCD_NgayCap = fake.date_between(datetime(2010,1,1), datetime(2020,12,31)).strftime("%Y-%m-%d")
    CCCD_NoiCap = random.choice(tinh_list)
    NoiSinh_Tinhtp = random.choice(tinh_list)
    NoiSinh_Phuongxa = fake.street_name()
    Email = fake.email()
    DienThoai = "0" + gen_unique_number_str(9, used_phone)
    TamTru = random.choice(["KTX khu A", "KTX khu B", "Nhà trọ Thủ Đức", "Quận 9", "Bình Thạnh"])
    TamTru_Tinhtp = random.choice(tinh_list)
    TamTru_Phuongxa = fake.street_name()
    ThuongTru = fake.address().replace("\n", ", ")
    LopSH = random.choice(lop_list)
    KhoaHoc = random.choice(["K2020", "K2021", "K2022", "K2023"])
    Khoa = random.choice(khoa_list)
    Hedt = random.choice(hedt_list)
    ChuyenNganh = random.choice(cn_list)
    TinhTrang = random.choice(tt_list)
    MoCoi = random.choice(mc_list)

    students.append((
        MaSV, HoTen, NgaySinh, NoiSinh_Tinhtp, NoiSinh_Phuongxa,
        Email, DienThoai, GioiTinh, CCCD, CCCD_NgayCap, CCCD_NoiCap,
        TamTru, TamTru_Tinhtp, TamTru_Phuongxa, ThuongTru, LopSH,
        KhoaHoc, Khoa, Hedt, ChuyenNganh, TinhTrang, MoCoi
    ))

cur.executemany("""
INSERT OR IGNORE INTO SV VALUES (
 ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?
)
""", students)
conn.commit()

# --- DKHP & Diem
all_lops = [r[0] for r in cur.execute("SELECT MaLop FROM TKB").fetchall()]
dkhp, dkhp_luu, diem = [], [], []
for sv in students:
    MaSV = sv[0]
    chosen = random.sample(all_lops, 3)
    for MaLop in chosen:
        TGianDangKy = fake.date_between(start_date="-1y", end_date="today").strftime("%Y-%m-%d")
        dkhp.append((MaSV, MaLop, TGianDangKy))
        if random.random() < 0.5:
            dkhp_luu.append((MaSV, MaLop, TGianDangKy))
        MaMH = MaLop.split("_")[0]
        DTB = round(random.uniform(0, 10), 2)
        diem.append((MaSV, MaLop, MaMH, DTB))

cur.executemany("INSERT OR IGNORE INTO DKHP (MaSV, MaLop, TGianDangKy) VALUES (?, ?, ?)", dkhp)
cur.executemany("INSERT OR IGNORE INTO DKHP_Luu (MaSV, MaLop, TGianDangKy) VALUES (?, ?, ?)", dkhp_luu)
cur.executemany("INSERT OR IGNORE INTO Diem VALUES (?, ?, ?, ?)", diem)
conn.commit()

# --- Thống kê
for tbl in ["SV", "Khoa", "TinhTP", "LopSH", "Hedt", "ChuyenNganh", "TinhTrang", "MoCoi", "MonHoc", "TKB", "DKHP", "Diem"]:
    cur.execute(f"SELECT COUNT(*) FROM {tbl}")
    print(f"{tbl}: {cur.fetchone()[0]} hàng")

conn.close()
print("✅ Hoàn tất: DB 'db_UIT.db' đã được tạo và điền dữ liệu thành công!")
