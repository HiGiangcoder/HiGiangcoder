import sqlite3
import os
import hashlib

def init_database():
    # Đường dẫn database
    db_path = "../data/english.db"
    os.makedirs(os.path.dirname(db_path), exist_ok=True)

    conn = sqlite3.connect(db_path)
    cur = conn.cursor()

    # XÓA CÁC BẢNG CŨ NẾU TỒN TẠI (theo thứ tự phụ thuộc)
    cur.execute("DROP TABLE IF EXISTS user_progress;")
    cur.execute("DROP TABLE IF EXISTS words;")
    cur.execute("DROP TABLE IF EXISTS lessons;")
    cur.execute("DROP TABLE IF EXISTS users;")

    # --- Bảng users ---
    cur.execute("""
    CREATE TABLE users (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        username TEXT UNIQUE NOT NULL,
        password_hash TEXT NOT NULL,
        email TEXT,
        created_at DATETIME DEFAULT CURRENT_TIMESTAMP
    );
    """)

    # --- Bảng lessons ---
    cur.execute("""
    CREATE TABLE lessons (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        title TEXT NOT NULL,
        type TEXT NOT NULL,
        description TEXT,
        created_by INTEGER,
        created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
        FOREIGN KEY (created_by) REFERENCES users(id)
    );
    """)

    # --- Bảng words ---
    cur.execute("""
    CREATE TABLE words (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        lesson_id INTEGER,
        word TEXT NOT NULL,
        meaning TEXT NOT NULL,
        example TEXT,
        FOREIGN KEY (lesson_id) REFERENCES lessons(id) ON DELETE CASCADE
    );
    """)

    # --- Bảng user_progress ---
    cur.execute("""
    CREATE TABLE user_progress (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        user_id INTEGER,
        lesson_id INTEGER,
        score INTEGER DEFAULT 0,
        completed_at DATETIME DEFAULT CURRENT_TIMESTAMP,
        FOREIGN KEY (user_id) REFERENCES users(id),
        FOREIGN KEY (lesson_id) REFERENCES lessons(id)
    );
    """)

    # Thêm user mẫu (password: "password123")
    sample_password_hash = hashlib.sha256("password123".encode()).hexdigest()
    cur.execute("INSERT INTO users (username, password_hash, email) VALUES (?, ?, ?)", 
                ("demo_user", sample_password_hash, "demo@example.com"))
    demo_user_id = cur.lastrowid

    # Thêm admin user (password: "admin123")
    admin_password_hash = hashlib.sha256("admin123".encode()).hexdigest()
    cur.execute("INSERT INTO users (username, password_hash, email) VALUES (?, ?, ?)", 
                ("admin", admin_password_hash, "admin@example.com"))

    # Thêm dữ liệu mẫu cho lessons
    lessons = [
        ("Animals Vocabulary", "vocabulary", "Learn common animals.", demo_user_id),
        ("Food Vocabulary", "vocabulary", "Learn common food items.", demo_user_id),
        ("Basic Grammar Rules", "grammar", "Learn basic grammar rules.", demo_user_id),
        ("Daily Conversations", "conversation", "Practice daily conversations.", demo_user_id)
    ]
    cur.executemany("INSERT INTO lessons (title, type, description, created_by) VALUES (?, ?, ?, ?);", lessons)

    # Thêm dữ liệu mẫu cho words
    words = [
        (1, "cat", "con mèo", "The cat is sleeping."),
        (1, "dog", "con chó", "I love my dog."),
        (1, "bird", "con chim", "The bird is singing."),
        (2, "apple", "quả táo", "I eat an apple every day."),
        (2, "rice", "gạo/cơm", "She cooks rice for dinner."),
        (2, "bread", "bánh mì", "We eat bread for breakfast."),
        (3, "present simple", "thì hiện tại đơn", "I work every day."),
        (4, "How are you?", "Bạn khỏe không?", "How are you? I'm fine, thank you.")
    ]
    cur.executemany("INSERT INTO words (lesson_id, word, meaning, example) VALUES (?, ?, ?, ?);", words)

    conn.commit()
    print("[Database] Initialized successfully with users, lessons, and words.")
    print("[Database] Demo user: demo_user / password123")
    print("[Database] Admin user: admin / admin123")
    conn.close()

if __name__ == "__main__":
    init_database()