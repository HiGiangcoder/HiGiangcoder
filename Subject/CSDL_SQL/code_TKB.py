import sqlite3

# Connect to SQLite database (or create it if it doesn't exist)
conn = sqlite3.connect('db_UIT.db')
cur = conn.cursor()

cur.execute("""
CREATE TABLE TKB (
    MaLop TEXT NOT NULL,
    MaMH TEXT NOT NULL,
    Thu TEXT NOT NULL,
    TietHoc TEXT NOT NULL,
    PhongHoc TEXT NOT NULL,
    FOREIGN KEY (MaLop) REFERENCES bangmonhoc(MaLop),
    FOREIGN KEY (MaMH) REFERENCES bangmonhoc(MaMH)
)
""")

cur.execute("""
INSERT INTO TKB (MaLop, MaMH, Thu, TietHoc, PhongHoc)
VALUES ('Lop001', 'MH001', '2', '1-3', 'P101');
""")

cur.execute("""
INSERT INTO TKB (MaLop, MaMH, Thu, TietHoc, PhongHoc)
VALUES ('Lop001', 'MH002', '4', '4-6', 'P102');
""")
conn.commit()
conn.close()