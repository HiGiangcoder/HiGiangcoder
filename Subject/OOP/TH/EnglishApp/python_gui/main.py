import sys
import os
from PyQt5.QtWidgets import (
    QApplication, QWidget, QPushButton, QLabel, QVBoxLayout, 
    QHBoxLayout, QLineEdit, QMessageBox, QStackedWidget, QListWidget,
    QTextEdit, QDialog, QFormLayout, QTabWidget
)
from PyQt5.QtGui import QFont
from PyQt5.QtCore import Qt

from user_manager import UserManager
from lesson_manager import LessonManagerDialog
from backend_client import BackendClient

# Login Dialog (giữ nguyên)
class LoginDialog(QDialog):
    def __init__(self, user_manager, parent=None):
        super().__init__(parent)
        self.user_manager = user_manager
        self.setWindowTitle("Login to English Learning App")
        self.resize(400, 300)
        self.setup_ui()

    def setup_ui(self):
        layout = QVBoxLayout()
        self.setLayout(layout)

        title = QLabel("Welcome Back!")
        title.setFont(QFont("Arial", 20, QFont.Bold))
        title.setAlignment(Qt.AlignCenter)
        layout.addWidget(title)

        form_layout = QFormLayout()
        self.username_input = QLineEdit()
        self.username_input.setPlaceholderText("Enter your username")
        self.password_input = QLineEdit()
        self.password_input.setPlaceholderText("Enter your password")
        self.password_input.setEchoMode(QLineEdit.Password)
        
        form_layout.addRow("Username:", self.username_input)
        form_layout.addRow("Password:", self.password_input)
        layout.addLayout(form_layout)

        login_btn = QPushButton("Login")
        login_btn.clicked.connect(self.login)
        layout.addWidget(login_btn)

        signup_btn = QPushButton("Don't have an account? Sign up")
        signup_btn.setStyleSheet("QPushButton { background-color: transparent; color: blue; text-decoration: underline; }")
        signup_btn.clicked.connect(self.open_signup)
        layout.addWidget(signup_btn)

    def login(self):
        username = self.username_input.text().strip()
        password = self.password_input.text().strip()

        if not username or not password:
            QMessageBox.warning(self, "Error", "Please fill in all fields")
            return

        success, message = self.user_manager.login(username, password)
        if success:
            self.accept()
        else:
            QMessageBox.warning(self, "Login Failed", message)

    def open_signup(self):
        self.done(2)


# Signup Dialog (giữ nguyên)
class SignupDialog(QDialog):
    def __init__(self, user_manager, parent=None):
        super().__init__(parent)
        self.user_manager = user_manager
        self.setWindowTitle("Create New Account")
        self.resize(400, 350)
        self.setup_ui()

    def setup_ui(self):
        layout = QVBoxLayout()
        self.setLayout(layout)

        title = QLabel("Create Account")
        title.setFont(QFont("Arial", 20, QFont.Bold))
        title.setAlignment(Qt.AlignCenter)
        layout.addWidget(title)

        form_layout = QFormLayout()
        self.username_input = QLineEdit()
        self.username_input.setPlaceholderText("Choose a username")
        self.email_input = QLineEdit()
        self.email_input.setPlaceholderText("Your email (optional)")
        self.password_input = QLineEdit()
        self.password_input.setPlaceholderText("Choose a password")
        self.password_input.setEchoMode(QLineEdit.Password)
        self.confirm_password_input = QLineEdit()
        self.confirm_password_input.setPlaceholderText("Confirm your password")
        self.confirm_password_input.setEchoMode(QLineEdit.Password)
        
        form_layout.addRow("Username:", self.username_input)
        form_layout.addRow("Email:", self.email_input)
        form_layout.addRow("Password:", self.password_input)
        form_layout.addRow("Confirm Password:", self.confirm_password_input)
        layout.addLayout(form_layout)

        signup_btn = QPushButton("Sign Up")
        signup_btn.clicked.connect(self.signup)
        layout.addWidget(signup_btn)

        back_btn = QPushButton("Back to Login")
        back_btn.setStyleSheet("QPushButton { background-color: transparent; color: blue; text-decoration: underline; }")
        back_btn.clicked.connect(self.back_to_login)
        layout.addWidget(back_btn)

    def signup(self):
        username = self.username_input.text().strip()
        email = self.email_input.text().strip() or None
        password = self.password_input.text().strip()
        confirm_password = self.confirm_password_input.text().strip()

        if not username or not password:
            QMessageBox.warning(self, "Error", "Username and password are required")
            return

        if password != confirm_password:
            QMessageBox.warning(self, "Error", "Passwords do not match")
            return

        if len(password) < 6:
            QMessageBox.warning(self, "Error", "Password must be at least 6 characters")
            return

        success, message = self.user_manager.register(username, password, email)
        if success:
            QMessageBox.information(self, "Success", message)
            self.accept()
        else:
            QMessageBox.warning(self, "Signup Failed", message)

    def back_to_login(self):
        self.reject()


class EnglishAppGUI(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("English Learning App")
        self.resize(800, 600)
        
        # Khởi tạo các thành phần
        self.user_manager = UserManager()
        self.backend_client = BackendClient()
        
        # Hiển thị dialog đăng nhập đầu tiên
        if not self.show_auth_dialog():
            sys.exit(0)
            
        self.setup_ui()

    def setup_ui(self):
        # Main layout
        main_layout = QVBoxLayout()
        self.setLayout(main_layout)

        # Header với thông tin user
        header_layout = QHBoxLayout()
        user_info = self.user_manager.get_current_user()
        self.user_label = QLabel(f"Welcome, {user_info['username']}!")
        self.user_label.setFont(QFont("Arial", 14, QFont.Bold))
        
        # Hiển thị backend info
        backend_info = "C++ Backend" if self.backend_client.is_cpp_backend() else "Python Backend"
        self.backend_label = QLabel(f"Backend: {backend_info}")
        self.backend_label.setFont(QFont("Arial", 10))
        self.backend_label.setStyleSheet("color: #666;")
        
        self.manage_btn = QPushButton("Manage Lessons")
        self.manage_btn.clicked.connect(self.show_lesson_manager)
        
        self.logout_btn = QPushButton("Logout")
        self.logout_btn.clicked.connect(self.logout)
        
        header_layout.addWidget(self.user_label)
        header_layout.addWidget(self.backend_label)
        header_layout.addStretch()
        header_layout.addWidget(self.manage_btn)
        header_layout.addWidget(self.logout_btn)
        main_layout.addLayout(header_layout)

        # Main content area
        self.tab_widget = QTabWidget()
        main_layout.addWidget(self.tab_widget)

        # Tạo các tab
        self.lessons_tab = QWidget()
        self.progress_tab = QWidget()
        self.profile_tab = QWidget()

        self.setup_lessons_tab()
        self.setup_progress_tab()
        self.setup_profile_tab()

        self.tab_widget.addTab(self.lessons_tab, "Learn")
        self.tab_widget.addTab(self.progress_tab, "My Progress")
        self.tab_widget.addTab(self.profile_tab, "Profile")

    def show_auth_dialog(self):
        """Hiển thị dialog authentication (login/signup)"""
        while True:
            login_dialog = LoginDialog(self.user_manager, self)
            result = login_dialog.exec_()
            
            if result == QDialog.Accepted:
                return True
            elif result == 2:
                signup_dialog = SignupDialog(self.user_manager, self)
                if signup_dialog.exec_() == QDialog.Accepted:
                    QMessageBox.information(self, "Success", "Account created successfully! Please login.")
                    continue
                else:
                    continue
            else:
                return False

    def show_lesson_manager(self):
        """Hiển thị dialog quản lý lesson"""
        dialog = LessonManagerDialog(self.user_manager, self)
        dialog.exec_()
        self.load_lessons()

    def setup_lessons_tab(self):
        layout = QVBoxLayout()
        self.lessons_tab.setLayout(layout)

        title = QLabel("Available Lessons")
        title.setFont(QFont("Arial", 18, QFont.Bold))
        layout.addWidget(title)

        refresh_btn = QPushButton("Refresh Lessons")
        refresh_btn.clicked.connect(self.load_lessons)
        layout.addWidget(refresh_btn)

        self.lessons_list = QListWidget()
        layout.addWidget(self.lessons_list)

        start_btn = QPushButton("Start Selected Lesson")
        start_btn.clicked.connect(self.start_selected_lesson)
        layout.addWidget(start_btn)

        # Load lessons ban đầu
        self.load_lessons()

    def setup_progress_tab(self):
        layout = QVBoxLayout()
        self.progress_tab.setLayout(layout)

        title = QLabel("My Learning Progress")
        title.setFont(QFont("Arial", 18, QFont.Bold))
        layout.addWidget(title)

        self.progress_text = QTextEdit()
        self.progress_text.setReadOnly(True)
        layout.addWidget(self.progress_text)

        refresh_btn = QPushButton("Refresh Progress")
        refresh_btn.clicked.connect(self.refresh_progress)
        layout.addWidget(refresh_btn)

        self.refresh_progress()

    def setup_profile_tab(self):
        layout = QVBoxLayout()
        self.profile_tab.setLayout(layout)

        title = QLabel("User Profile")
        title.setFont(QFont("Arial", 18, QFont.Bold))
        layout.addWidget(title)

        user_info = self.user_manager.get_current_user()
        backend_type = "C++" if self.backend_client.is_cpp_backend() else "Python"
        
        profile_text = f"""
        <h3>Account Information</h3>
        <b>Username:</b> {user_info['username']}<br>
        <b>Email:</b> {user_info.get('email', 'Not provided')}<br>
        <b>User ID:</b> {user_info['id']}<br>
        <b>Backend:</b> {backend_type}<br>
        <br>
        <h3>Statistics</h3>
        <b>Lessons Completed:</b> {len(self.user_manager.get_user_progress())}<br>
        """
        
        profile_label = QLabel(profile_text)
        profile_label.setTextFormat(Qt.RichText)
        layout.addWidget(profile_label)

    def load_lessons(self):
        """Load lessons từ backend"""
        try:
            lessons = self.backend_client.get_lessons()
            self.lessons_list.clear()
            
            for lesson in lessons:
                item_text = f"{lesson.getTitle()} ({lesson.getType()})"
                self.lessons_list.addItem(item_text)
                
            self.current_lessons = lessons  # Lưu lessons hiện tại
                
        except Exception as e:
            print(f"Error loading lessons: {e}")
            QMessageBox.critical(self, "Error", f"Cannot load lessons: {str(e)}")

    def refresh_progress(self):
        """Refresh và hiển thị tiến độ user"""
        progress_data = self.user_manager.get_user_progress()
        
        if not progress_data:
            self.progress_text.setText("No progress recorded yet. Complete some lessons to see your progress here!")
            return

        progress_html = "<h3>Your Learning Journey</h3><table width='100%'>"
        progress_html += "<tr><th>Lesson</th><th>Score</th><th>Completed</th></tr>"
        
        for progress_item in progress_data:
            if len(progress_item) >= 4:
                lesson_id, lesson_title, score, completed_at = progress_item
                progress_html += f"<tr><td>{lesson_title}</td><td>{score}%</td><td>{completed_at}</td></tr>"
        
        progress_html += "</table>"
        self.progress_text.setHtml(progress_html)

    def start_selected_lesson(self):
        current_row = self.lessons_list.currentRow()
        if current_row >= 0:
            self.start_lesson(current_row)
        else:
            QMessageBox.warning(self, "Selection Required", "Please select a lesson first.")

    def start_lesson(self, idx):
        """Bắt đầu lesson được chọn"""
        if idx >= len(self.current_lessons):
            QMessageBox.critical(self, "Error", "Invalid lesson selection.")
            return
            
        selected_lesson = self.current_lessons[idx]
        
        # Kiểm tra loại lesson
        if "vocabulary" in selected_lesson.getType().lower():
            self.start_vocabulary_lesson(selected_lesson)
        else:
            QMessageBox.information(self, "Coming Soon", 
                                  "Grammar and conversation lessons are under development. Please try vocabulary lessons for now.")

    def start_vocabulary_lesson(self, lesson):
        """Bắt đầu lesson vocabulary"""
        try:
            words = lesson.getWords()
            if not words:
                QMessageBox.information(self, "No Words", "This lesson doesn't have any words yet.")
                return
                
            self.current_lesson = lesson
            self.words = words
            self.current_quiz_index = 0
            self.correct_answers = 0
            self.show_vocabulary_question()
            
        except Exception as e:
            QMessageBox.critical(self, "Error", f"Cannot start lesson: {str(e)}")

    def show_vocabulary_question(self):
        """Hiển thị câu hỏi vocabulary"""
        if self.current_quiz_index >= len(self.words):
            self.finish_quiz()
            return

        word = self.words[self.current_quiz_index]
        
        # Tạo dialog quiz
        self.quiz_dialog = QDialog(self)
        self.quiz_dialog.setWindowTitle(f"Vocabulary Quiz - {self.current_lesson.getTitle()}")
        self.quiz_dialog.resize(500, 300)
        
        layout = QVBoxLayout()
        self.quiz_dialog.setLayout(layout)

        question = QLabel(f"What is the meaning of '{word.getText()}'?")
        question.setFont(QFont("Arial", 16))
        layout.addWidget(question)

        # Hiển thị ví dụ nếu có
        if hasattr(word, 'getExample') and word.getExample():
            example_label = QLabel(f"Example: {word.getExample()}")
            example_label.setFont(QFont("Arial", 12))
            example_label.setStyleSheet("color: #666; font-style: italic;")
            layout.addWidget(example_label)

        self.answer_input = QLineEdit()
        self.answer_input.setFont(QFont("Arial", 14))
        layout.addWidget(self.answer_input)

        submit_btn = QPushButton("Submit Answer")
        submit_btn.clicked.connect(lambda: self.check_vocabulary_answer(word))
        layout.addWidget(submit_btn)

        progress = QLabel(f"Progress: {self.current_quiz_index + 1}/{len(self.words)}")
        layout.addWidget(progress)

        self.quiz_dialog.exec_()

    def check_vocabulary_answer(self, word):
        """Kiểm tra câu trả lời vocabulary"""
        user_answer = self.answer_input.text().strip().lower()
        correct_answer = word.getMeaning().strip().lower()

        if user_answer == correct_answer:
            QMessageBox.information(self.quiz_dialog, "Correct!", "✅ Correct answer!")
            self.correct_answers += 1
        else:
            QMessageBox.warning(self.quiz_dialog, "Incorrect", 
                              f"❌ The correct answer is: {word.getMeaning()}")

        self.current_quiz_index += 1
        self.quiz_dialog.close()
        self.show_vocabulary_question()

    def finish_quiz(self):
        """Kết thúc quiz và lưu kết quả"""
        if len(self.words) > 0:
            score = int((self.correct_answers / len(self.words)) * 100)
        else:
            score = 0
        
        # Lưu tiến độ
        lesson_id = self.current_lesson.getId() if hasattr(self.current_lesson, 'getId') else 1
        self.user_manager.save_progress(lesson_id, score)
        
        QMessageBox.information(self, "Quiz Completed",
                              f"🎉 Quiz finished!\n"
                              f"Score: {self.correct_answers}/{len(self.words)} ({score}%)\n\n"
                              f"Your progress has been saved!")
        
        # Refresh progress display
        self.refresh_progress()

    def logout(self):
        """Đăng xuất user"""
        reply = QMessageBox.question(self, "Logout", 
                                   "Are you sure you want to logout?",
                                   QMessageBox.Yes | QMessageBox.No)
        
        if reply == QMessageBox.Yes:
            self.user_manager.logout()
            if self.show_auth_dialog():
                # Update UI cho user mới
                user_info = self.user_manager.get_current_user()
                self.user_label.setText(f"Welcome, {user_info['username']}!")
                self.load_lessons()
                self.refresh_progress()
            else:
                self.close()


if __name__ == "__main__":
    app = QApplication(sys.argv)
    
    # Set application style
    app.setStyle('Fusion')
    
    gui = EnglishAppGUI()
    gui.show()
    sys.exit(app.exec_())