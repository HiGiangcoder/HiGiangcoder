import sqlite3

# Connect to SQLite database (or create it if it doesn't exist)
conn = sqlite3.connect('db_UIT.db')
cur = conn.cursor()
cur.execute('''
CREATE TABLE IF NOT EXISTS GiangVien (
    MaGV TEXT PRIMARY KEY,
    HoTen TEXT NOT NULL,
    NgaySinh TEXT NOT NULL,
    GioiTinh TEXT NOT NULL,
    CCCD TEXT NOT NULL UNIQUE,
    Khoa TEXT NOT NULL
)
''')

cur.execute("""
INSERT INTO GiangVien (MaGV, HoTen, NgaySinh, GioiTinh, CCCD, Khoa)
VALUES ('GV001', 'Nguyen Van A', '1980-01-15', 'Nam', '123456789', 'CNTT');
""")
cur.execute("""
INSERT INTO GiangVien (MaGV, HoTen, NgaySinh, GioiTinh, CCCD, Khoa)
VALUES ('GV002', 'Le Thi B', '1975-03-22', 'Nu', '987654321', 'Toan');
""")
cur.execute("""
INSERT INTO GiangVien (MaGV, HoTen, NgaySinh, GioiTinh, CCCD, Khoa)
VALUES ('GV003', 'Tran Van C', '1985-07-30', 'Nam', '456789123', 'Ly');
""")
cur.execute("""
INSERT INTO GiangVien (MaGV, HoTen, NgaySinh, GioiTinh, CCCD, Khoa)
VALUES ('GV004', 'Pham Thi D', '1990-11-05', 'Nu', '789123456', 'Hoa');
""")
cur.execute("""
INSERT INTO GiangVien (MaGV, HoTen, NgaySinh, GioiTinh, CCCD, Khoa)
VALUES ('GV005', 'Hoang Van E', '1978-09-12', 'Nam', '321654987', 'Sinh');
""")

conn.commit()
conn.close()

