import sqlite3
import hashlib
import os
from datetime import datetime

class UserManager:
    def __init__(self, db_path="data/english.db"):
        self.db_path = db_path
        self.current_user = None
        self.ensure_tables_exist()

    def ensure_tables_exist(self):
        """Đảm bảo các bảng tồn tại"""
        if not os.path.exists(self.db_path):
            print(f"Database file {self.db_path} does not exist. Please run init_database.py first.")
            return False
        return True

    def hash_password(self, password):
        """Băm mật khẩu"""
        return hashlib.sha256(password.encode()).hexdigest()

    def register(self, username, password, email=None):
        """Đăng ký user mới"""
        try:
            conn = sqlite3.connect(self.db_path)
            cur = conn.cursor()
            
            # Kiểm tra username đã tồn tại chưa
            cur.execute("SELECT id FROM users WHERE username = ?", (username,))
            if cur.fetchone():
                return False, "Username already exists"
            
            # Hash password và lưu user
            password_hash = self.hash_password(password)
            cur.execute(
                "INSERT INTO users (username, password_hash, email) VALUES (?, ?, ?)",
                (username, password_hash, email)
            )
            conn.commit()
            conn.close()
            return True, "Registration successful"
            
        except sqlite3.Error as e:
            return False, f"Database error: {str(e)}"

    def login(self, username, password):
        """Đăng nhập"""
        try:
            conn = sqlite3.connect(self.db_path)
            cur = conn.cursor()
            
            password_hash = self.hash_password(password)
            cur.execute(
                "SELECT id, username, email FROM users WHERE username = ? AND password_hash = ?",
                (username, password_hash)
            )
            user_data = cur.fetchone()
            conn.close()
            
            if user_data:
                self.current_user = {
                    'id': user_data[0],
                    'username': user_data[1],
                    'email': user_data[2]
                }
                return True, "Login successful"
            else:
                return False, "Invalid username or password"
                
        except sqlite3.Error as e:
            return False, f"Database error: {str(e)}"

    def logout(self):
        """Đăng xuất"""
        self.current_user = None
        return True, "Logout successful"

    def save_progress(self, lesson_id, score):
        """Lưu tiến độ học tập"""
        if not self.current_user:
            return False, "No user logged in"
        
        try:
            conn = sqlite3.connect(self.db_path)
            cur = conn.cursor()
            
            # Kiểm tra xem đã có progress cho lesson này chưa
            cur.execute(
                "SELECT id FROM user_progress WHERE user_id = ? AND lesson_id = ?",
                (self.current_user['id'], lesson_id)
            )
            existing = cur.fetchone()
            
            if existing:
                # Update existing progress
                cur.execute(
                    "UPDATE user_progress SET score = ? WHERE id = ?",
                    (score, existing[0])
                )
            else:
                # Insert new progress
                cur.execute(
                    """INSERT INTO user_progress (user_id, lesson_id, score) 
                       VALUES (?, ?, ?)""",
                    (self.current_user['id'], lesson_id, score)
                )
            
            conn.commit()
            conn.close()
            return True, "Progress saved"
            
        except sqlite3.Error as e:
            return False, f"Database error: {str(e)}"

    def get_user_progress(self):
        """Lấy tiến độ học tập của user"""
        if not self.current_user:
            return []
        
        try:
            conn = sqlite3.connect(self.db_path)
            cur = conn.cursor()
            
            cur.execute("""
                SELECT l.id, l.title, up.score, up.completed_at 
                FROM user_progress up
                JOIN lessons l ON up.lesson_id = l.id
                WHERE up.user_id = ?
                ORDER BY up.completed_at DESC
            """, (self.current_user['id'],))
            
            progress = cur.fetchall()
            conn.close()
            return progress
            
        except sqlite3.Error as e:
            print(f"Error getting user progress: {e}")
            return []

    def is_logged_in(self):
        """Kiểm tra trạng thái đăng nhập"""
        return self.current_user is not None

    def get_current_user(self):
        """Lấy thông tin user hiện tại"""
        return self.current_user

    # ===== LESSON MANAGEMENT METHODS =====
    
    def get_all_lessons(self):
        """Lấy tất cả lessons từ database"""
        try:
            conn = sqlite3.connect(self.db_path)
            cur = conn.cursor()
            
            cur.execute("""
                SELECT l.id, l.title, l.type, l.description, u.username, l.created_at
                FROM lessons l 
                LEFT JOIN users u ON l.created_by = u.id
                ORDER BY l.created_at DESC
            """)
            
            lessons = cur.fetchall()
            conn.close()
            return lessons
            
        except sqlite3.Error as e:
            print(f"Error getting lessons: {e}")
            return []

    def get_lesson_words(self, lesson_id):
        """Lấy tất cả words của một lesson"""
        try:
            conn = sqlite3.connect(self.db_path)
            cur = conn.cursor()
            
            cur.execute("""
                SELECT id, word, meaning, example 
                FROM words 
                WHERE lesson_id = ?
                ORDER BY id
            """, (lesson_id,))
            
            words = cur.fetchall()
            conn.close()
            return words
            
        except sqlite3.Error as e:
            print(f"Error getting lesson words: {e}")
            return []

    def create_lesson(self, title, lesson_type, description=""):
        """Tạo lesson mới"""
        if not self.current_user:
            return False, "No user logged in"
        
        try:
            conn = sqlite3.connect(self.db_path)
            cur = conn.cursor()
            
            cur.execute(
                "INSERT INTO lessons (title, type, description, created_by) VALUES (?, ?, ?, ?)",
                (title, lesson_type, description, self.current_user['id'])
            )
            lesson_id = cur.lastrowid
            conn.commit()
            conn.close()
            return True, lesson_id
            
        except sqlite3.Error as e:
            return False, f"Database error: {str(e)}"

    def update_lesson(self, lesson_id, title, lesson_type, description):
        """Cập nhật lesson"""
        if not self.current_user:
            return False, "No user logged in"
        
        try:
            conn = sqlite3.connect(self.db_path)
            cur = conn.cursor()
            
            # Kiểm tra quyền sở hữu
            cur.execute("SELECT created_by FROM lessons WHERE id = ?", (lesson_id,))
            result = cur.fetchone()
            
            if not result:
                return False, "Lesson not found"
            
            # Chỉ cho phép sửa lesson của chính user hoặc nếu là admin
            if result[0] != self.current_user['id'] and self.current_user['username'] != 'admin':
                return False, "You can only edit your own lessons"
            
            cur.execute(
                """UPDATE lessons 
                   SET title = ?, type = ?, description = ? 
                   WHERE id = ?""",
                (title, lesson_type, description, lesson_id)
            )
            conn.commit()
            conn.close()
            return True, "Lesson updated successfully"
            
        except sqlite3.Error as e:
            return False, f"Database error: {str(e)}"

    def delete_lesson(self, lesson_id):
        """Xóa lesson"""
        if not self.current_user:
            return False, "No user logged in"
        
        try:
            conn = sqlite3.connect(self.db_path)
            cur = conn.cursor()
            
            # Kiểm tra quyền sở hữu
            cur.execute("SELECT created_by FROM lessons WHERE id = ?", (lesson_id,))
            result = cur.fetchone()
            
            if not result:
                return False, "Lesson not found"
            
            # Chỉ cho phép xóa lesson của chính user hoặc nếu là admin
            if result[0] != self.current_user['id'] and self.current_user['username'] != 'admin':
                return False, "You can only delete your own lessons"
            
            # Xóa words trước (cascade)
            cur.execute("DELETE FROM words WHERE lesson_id = ?", (lesson_id,))
            # Xóa progress
            cur.execute("DELETE FROM user_progress WHERE lesson_id = ?", (lesson_id,))
            # Xóa lesson
            cur.execute("DELETE FROM lessons WHERE id = ?", (lesson_id,))
            
            conn.commit()
            conn.close()
            return True, "Lesson deleted successfully"
            
        except sqlite3.Error as e:
            return False, f"Database error: {str(e)}"

    def add_word_to_lesson(self, lesson_id, word, meaning, example=""):
        """Thêm word vào lesson"""
        if not self.current_user:
            return False, "No user logged in"
        
        try:
            conn = sqlite3.connect(self.db_path)
            cur = conn.cursor()
            
            # Kiểm tra quyền sở hữu
            cur.execute("SELECT created_by FROM lessons WHERE id = ?", (lesson_id,))
            result = cur.fetchone()
            
            if not result:
                return False, "Lesson not found"
            
            # Chỉ cho phép thêm word vào lesson của chính user hoặc nếu là admin
            if result[0] != self.current_user['id'] and self.current_user['username'] != 'admin':
                return False, "You can only add words to your own lessons"
            
            cur.execute(
                "INSERT INTO words (lesson_id, word, meaning, example) VALUES (?, ?, ?, ?)",
                (lesson_id, word, meaning, example)
            )
            conn.commit()
            conn.close()
            return True, "Word added successfully"
            
        except sqlite3.Error as e:
            return False, f"Database error: {str(e)}"

    def update_word(self, word_id, word, meaning, example):
        """Cập nhật word"""
        if not self.current_user:
            return False, "No user logged in"
        
        try:
            conn = sqlite3.connect(self.db_path)
            cur = conn.cursor()
            
            # Kiểm tra quyền sở hữu thông qua lesson
            cur.execute("""
                SELECT l.created_by 
                FROM words w 
                JOIN lessons l ON w.lesson_id = l.id 
                WHERE w.id = ?
            """, (word_id,))
            result = cur.fetchone()
            
            if not result:
                return False, "Word not found"
            
            # Chỉ cho phép sửa word trong lesson của chính user hoặc nếu là admin
            if result[0] != self.current_user['id'] and self.current_user['username'] != 'admin':
                return False, "You can only edit words in your own lessons"
            
            cur.execute(
                "UPDATE words SET word = ?, meaning = ?, example = ? WHERE id = ?",
                (word, meaning, example, word_id)
            )
            conn.commit()
            conn.close()
            return True, "Word updated successfully"
            
        except sqlite3.Error as e:
            return False, f"Database error: {str(e)}"

    def delete_word(self, word_id):
        """Xóa word"""
        if not self.current_user:
            return False, "No user logged in"
        
        try:
            conn = sqlite3.connect(self.db_path)
            cur = conn.cursor()
            
            # Kiểm tra quyền sở hữu thông qua lesson
            cur.execute("""
                SELECT l.created_by 
                FROM words w 
                JOIN lessons l ON w.lesson_id = l.id 
                WHERE w.id = ?
            """, (word_id,))
            result = cur.fetchone()
            
            if not result:
                return False, "Word not found"
            
            # Chỉ cho phép xóa word trong lesson của chính user hoặc nếu là admin
            if result[0] != self.current_user['id'] and self.current_user['username'] != 'admin':
                return False, "You can only delete words from your own lessons"
            
            cur.execute("DELETE FROM words WHERE id = ?", (word_id,))
            conn.commit()
            conn.close()
            return True, "Word deleted successfully"
            
        except sqlite3.Error as e:
            return False, f"Database error: {str(e)}"
    def get_lessons_for_display(self):
        """Lấy lessons định dạng đơn giản cho hiển thị"""
        lessons = self.get_all_lessons()
        simple_lessons = []
        for lesson in lessons:
            lesson_id, title, lesson_type, description, author, created_at = lesson
            simple_lessons.append({
                'id': lesson_id,
                'title': title,
                'type': lesson_type,
                'description': description,
                'author': author
            })
        return simple_lessons

    def get_lesson_by_id(self, lesson_id):
        """Lấy thông tin lesson theo ID"""
        try:
            conn = sqlite3.connect(self.db_path)
            cur = conn.cursor()
            
            cur.execute("""
                SELECT l.id, l.title, l.type, l.description, u.username
                FROM lessons l 
                LEFT JOIN users u ON l.created_by = u.id
                WHERE l.id = ?
            """, (lesson_id,))
            
            lesson = cur.fetchone()
            conn.close()
            return lesson
            
        except sqlite3.Error as e:
            print(f"Error getting lesson: {e}")
            return None