import sqlite3

# Connect to SQLite database (or create it if it doesn't exist)
conn = sqlite3.connect('db_UIT.db')
cur = conn.cursor()

cur.execute('''
CREATE TABLE DKHP (
    MSSV TEXT NOT NULL,
    MaLop TEXT NOT NULL,
    HK TEXT NOT NULL,
    NgayDK DATE NOT NULL,
    TrangThai TEXT NOT NULL CHECK (TrangThai In ('Dang ky', 'Huy')),

    FOREIGN KEY (MSSV) REFERENCES DSSV(MSSV),
    FOREIGN KEY (MaLop) REFERENCES BangMonHoc(MaLop),
    PRIMARY KEY (MSSV, MaLop, HK)
)
''')

cur.execute("""
INSERT INTO DKHP (MSSV, MaLop, HK, NgayDK, TrangThai)
VALUES ('22520002', 'Lop001', '2024A', '2024-06-01', 'Dang ky');
""")

conn.commit()
conn.close()