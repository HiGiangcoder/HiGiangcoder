import sys
from PyQt5.QtWidgets import (
    QApplication, QWidget, QPushButton, QLabel,
    QVBoxLayout, QLineEdit, QMessageBox
)
from PyQt5.QtGui import QFont
from englishapp import EnglishApp


class EnglishAppGUI(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("English Learning App")
        self.resize(500, 400)

        # Dữ liệu từ module C++
        self.app = EnglishApp()
        self.lessons = self.app.getLessons()

        # Biến trạng thái quiz
        self.current_lesson = None
        self.words = []
        self.index = 0
        self.correct = 0

        # Layout chính
        self.layout = QVBoxLayout()
        self.setLayout(self.layout)
        self.show_main_menu()

    def clear_layout(self):
        while self.layout.count():
            child = self.layout.takeAt(0)
            if child.widget():
                child.widget().deleteLater()

    # ---------------------- GIAO DIỆN CHÍNH ----------------------
    def show_main_menu(self):
        self.clear_layout()

        title = QLabel("English Learning App")
        title.setFont(QFont("Arial", 18, QFont.Bold))
        self.layout.addWidget(title)

        subtitle = QLabel("Select a lesson:")
        subtitle.setFont(QFont("Arial", 14))
        self.layout.addWidget(subtitle)

        for i, lesson in enumerate(self.lessons):
            btn = QPushButton(lesson.getTitle())
            btn.setFont(QFont("Arial", 12))
            btn.clicked.connect(lambda _, idx=i: self.start_lesson(idx))
            self.layout.addWidget(btn)

    # ---------------------- QUIZ ----------------------
    def start_lesson(self, idx):
        self.current_lesson = self.lessons[idx]
        self.words = self.current_lesson.getWords()
        self.index = 0
        self.correct = 0
        self.show_question()

    def show_question(self):
        self.clear_layout()

        # Hết câu hỏi
        if self.index >= len(self.words):
            percent = int(self.correct / len(self.words) * 100)
            QMessageBox.information(
                self, "Result",
                f"You got {self.correct}/{len(self.words)} words correct ({percent}%)"
            )
            self.show_main_menu()
            return

        # Hiện câu hỏi
        w = self.words[self.index]
        q_label = QLabel(f"What is the meaning of '{w.getText()}'?")
        q_label.setFont(QFont("Arial", 14))
        self.layout.addWidget(q_label)

        self.answer_entry = QLineEdit()
        self.answer_entry.setFont(QFont("Arial", 12))
        self.layout.addWidget(self.answer_entry)

        submit_btn = QPushButton("Submit")
        submit_btn.setFont(QFont("Arial", 12))
        submit_btn.clicked.connect(lambda: self.check_answer(w))
        self.layout.addWidget(submit_btn)

    def check_answer(self, w):
        ans = self.answer_entry.text().strip().lower()
        correct = w.getMeaning().strip().lower()

        if ans == correct:
            QMessageBox.information(self, "Correct!", "✅ Correct!")
            self.correct += 1
        else:
            QMessageBox.warning(self, "Wrong", f"❌ Correct answer: {w.getMeaning()}")

        self.index += 1
        self.show_question()


if __name__ == "__main__":
    app = QApplication(sys.argv)
    gui = EnglishAppGUI()
    gui.show()
    sys.exit(app.exec_())
