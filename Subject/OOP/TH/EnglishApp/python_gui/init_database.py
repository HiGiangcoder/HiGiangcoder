import sqlite3, os

db_path = os.path.join("data", "english.db")
os.makedirs(os.path.dirname(db_path), exist_ok=True)

conn = sqlite3.connect(db_path)
cur = conn.cursor()

# --- Bảng lessons ---
cur.execute("""
CREATE TABLE IF NOT EXISTS lessons (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    title TEXT NOT NULL,
    type TEXT NOT NULL,
    description TEXT
);
""")

# --- Bảng words ---
cur.execute("""
CREATE TABLE IF NOT EXISTS words (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    lesson_id INTEGER,
    word TEXT NOT NULL,
    meaning TEXT NOT NULL,
    example TEXT,
    FOREIGN KEY (lesson_id) REFERENCES lessons(id)
);
""")

# Thêm dữ liệu mẫu nếu chưa có
cur.execute("DELETE FROM lessons;")
cur.execute("DELETE FROM words;")

lessons = [
    ("Animals Vocabulary", "vocabulary", "Learn common animals."),
    ("Food Vocabulary", "vocabulary", "Learn common food items.")
]
cur.executemany("INSERT INTO lessons (title, type, description) VALUES (?, ?, ?);", lessons)

words = [
    (1, "cat", "con mèo", "The cat is sleeping."),
    (1, "dog", "con chó", "I love my dog."),
    (2, "apple", "quả táo", "I eat an apple every day."),
    (2, "rice", "gạo/cơm", "She cooks rice for dinner.")
]
cur.executemany("INSERT INTO words (lesson_id, word, meaning, example) VALUES (?, ?, ?, ?);", words)

conn.commit()
print("[Database] Initialized successfully with lessons + words.")
conn.close()
