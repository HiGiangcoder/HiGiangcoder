import sqlite3

# Connect to SQLite database (or create it if it doesn't exist)
conn = sqlite3.connect('db_UIT.db')
cur = conn.cursor()

cur.execute('''
CREATE TABLE IF NOT EXISTS bangmonhoc (
    MaMH TEXT PRIMARY KEY,
    MaLop TEXT NOT NULL,
    SoTinChi INTEGER NOT NULL CHECK (SoTinChi > 0),
    TenMH TEXT NOT NULL,
    NgayHoc TEXT NOT NULL,
    TietHoc TEXT NOT NULL,
    PhongHoc TEXT NOT NULL,
    MaGV TEXT NOT NULL,
    FOREIGN KEY (MaGV) REFERENCES GiangVien(MaGV)
    FOREIGN KEY (MaLop) REFERENCES Lop(MaLop)
)         
''')

cur.execute('''
INSERT INTO bangmonhoc (MaMH, MaLop, SoTinChi, TenMH, NgayHoc, TietHoc, PhongHoc, MaGV)
VALUES ('MH001', 'Lop001', 3, 'Toan Cao Cap', '2024-09-01', '1-3', 'P101', 'GV001');          
''')

conn.commit()
conn.close()