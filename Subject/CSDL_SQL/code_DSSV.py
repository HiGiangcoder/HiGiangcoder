import sqlite3

# Connect to SQLite database (or create it if it doesn't exist)
conn = sqlite3.connect('db_UIT.db')
cur = conn.cursor()

cur.execute('''
CREATE TABLE IF NOT EXISTS DSSV (
    MSSV TEXT PRIMARY KEY,
    HoTen TEXT NOT NULL,
    NgaySinh TEXT NOT NULL,
    GioiTinh TEXT NOT NULL,
    CCCD TEXT NOT NULL UNIQUE
)
''')

# Thêm dữ liệu
cur.execute("""
INSERT INTO DSSV (MSSV, HoTen, NgaySinh, GioiTinh, CCCD)
VALUES ('22520002', 'Tran Thi B', '2006-05-20', 'Nu', '987654321');
""")

conn.commit()
conn.close()