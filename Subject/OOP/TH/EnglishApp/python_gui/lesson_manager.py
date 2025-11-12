import sys
from PyQt5.QtWidgets import (
    QDialog, QVBoxLayout, QHBoxLayout, QFormLayout, QTableWidget,
    QTableWidgetItem, QPushButton, QLabel, QLineEdit, QTextEdit,
    QComboBox, QMessageBox, QTabWidget, QHeaderView, QSplitter,
    QGroupBox, QInputDialog
)
from PyQt5.QtGui import QFont
from PyQt5.QtCore import Qt

class LessonManagerDialog(QDialog):
    def __init__(self, user_manager, parent=None):
        super().__init__(parent)
        self.user_manager = user_manager
        self.current_lesson_id = None
        self.setWindowTitle("Lesson Management")
        self.resize(900, 700)
        self.setup_ui()
        self.load_lessons()

    def setup_ui(self):
        layout = QVBoxLayout()
        self.setLayout(layout)

        # Title
        title = QLabel("Lesson Management")
        title.setFont(QFont("Arial", 16, QFont.Bold))
        layout.addWidget(title)

        # Create lesson button
        create_btn = QPushButton("Create New Lesson")
        create_btn.clicked.connect(self.show_create_lesson_dialog)
        layout.addWidget(create_btn)

        # Splitter for lessons list and details
        splitter = QSplitter(Qt.Horizontal)
        layout.addWidget(splitter)

        # Left side: Lessons list
        left_widget = QTabWidget()
        left_layout = QVBoxLayout()
        left_widget.setLayout(left_layout)

        lessons_label = QLabel("Lessons")
        lessons_label.setFont(QFont("Arial", 12, QFont.Bold))
        left_layout.addWidget(lessons_label)

        self.lessons_table = QTableWidget()
        self.lessons_table.setColumnCount(4)
        self.lessons_table.setHorizontalHeaderLabels(["ID", "Title", "Type", "Author"])
        self.lessons_table.horizontalHeader().setSectionResizeMode(1, QHeaderView.Stretch)
        self.lessons_table.setSelectionBehavior(QTableWidget.SelectRows)
        self.lessons_table.cellClicked.connect(self.on_lesson_selected)
        left_layout.addWidget(self.lessons_table)

        splitter.addWidget(left_widget)

        # Right side: Lesson details and words
        right_widget = QTabWidget()
        right_layout = QVBoxLayout()
        right_widget.setLayout(right_layout)

        # Lesson details group
        details_group = QGroupBox("Lesson Details")
        details_layout = QFormLayout()
        details_group.setLayout(details_layout)

        self.lesson_title = QLineEdit()
        self.lesson_type = QComboBox()
        self.lesson_type.addItems(["vocabulary", "grammar", "conversation"])
        self.lesson_description = QTextEdit()
        self.lesson_description.setMaximumHeight(80)

        details_layout.addRow("Title:", self.lesson_title)
        details_layout.addRow("Type:", self.lesson_type)
        details_layout.addRow("Description:", self.lesson_description)

        # Lesson buttons
        lesson_buttons_layout = QHBoxLayout()
        self.update_lesson_btn = QPushButton("Update Lesson")
        self.update_lesson_btn.clicked.connect(self.update_lesson)
        self.delete_lesson_btn = QPushButton("Delete Lesson")
        self.delete_lesson_btn.clicked.connect(self.delete_lesson)
        
        lesson_buttons_layout.addWidget(self.update_lesson_btn)
        lesson_buttons_layout.addWidget(self.delete_lesson_btn)
        details_layout.addRow(lesson_buttons_layout)

        right_layout.addWidget(details_group)

        # Words management group
        words_group = QGroupBox("Words Management")
        words_layout = QVBoxLayout()
        words_group.setLayout(words_layout)

        # Add word section
        add_word_layout = QFormLayout()
        self.new_word = QLineEdit()
        self.new_meaning = QLineEdit()
        self.new_example = QTextEdit()
        self.new_example.setMaximumHeight(60)

        add_word_layout.addRow("Word:", self.new_word)
        add_word_layout.addRow("Meaning:", self.new_meaning)
        add_word_layout.addRow("Example:", self.new_example)

        add_word_btn = QPushButton("Add Word")
        add_word_btn.clicked.connect(self.add_word)
        add_word_layout.addRow(add_word_btn)

        words_layout.addLayout(add_word_layout)

        # Words table
        self.words_table = QTableWidget()
        self.words_table.setColumnCount(4)
        self.words_table.setHorizontalHeaderLabels(["ID", "Word", "Meaning", "Example"])
        self.words_table.horizontalHeader().setSectionResizeMode(3, QHeaderView.Stretch)
        self.words_table.setSelectionBehavior(QTableWidget.SelectRows)
        words_layout.addWidget(self.words_table)

        # Word buttons
        word_buttons_layout = QHBoxLayout()
        edit_word_btn = QPushButton("Edit Selected Word")
        edit_word_btn.clicked.connect(self.edit_word)
        delete_word_btn = QPushButton("Delete Selected Word")
        delete_word_btn.clicked.connect(self.delete_word)
        
        word_buttons_layout.addWidget(edit_word_btn)
        word_buttons_layout.addWidget(delete_word_btn)
        words_layout.addLayout(word_buttons_layout)

        right_layout.addWidget(words_group)
        splitter.addWidget(right_widget)

        # Set splitter proportions
        splitter.setSizes([300, 600])

        # Initially disable editing
        self.set_editing_enabled(False)

    def set_editing_enabled(self, enabled):
        """Enable or disable editing controls"""
        self.lesson_title.setEnabled(enabled)
        self.lesson_type.setEnabled(enabled)
        self.lesson_description.setEnabled(enabled)
        self.update_lesson_btn.setEnabled(enabled)
        self.delete_lesson_btn.setEnabled(enabled)
        self.new_word.setEnabled(enabled)
        self.new_meaning.setEnabled(enabled)
        self.new_example.setEnabled(enabled)

    def load_lessons(self):
        """Load all lessons into the table"""
        lessons = self.user_manager.get_all_lessons()
        self.lessons_table.setRowCount(len(lessons))
        
        for row, lesson in enumerate(lessons):
            lesson_id, title, lesson_type, description, author, created_at = lesson
            
            self.lessons_table.setItem(row, 0, QTableWidgetItem(str(lesson_id)))
            self.lessons_table.setItem(row, 1, QTableWidgetItem(title))
            self.lessons_table.setItem(row, 2, QTableWidgetItem(lesson_type))
            self.lessons_table.setItem(row, 3, QTableWidgetItem(author or "Unknown"))

    def on_lesson_selected(self, row, column):
        """When a lesson is selected in the table"""
        lesson_id = int(self.lessons_table.item(row, 0).text())
        self.current_lesson_id = lesson_id
        
        # Load lesson details
        lessons = self.user_manager.get_all_lessons()
        for lesson in lessons:
            if lesson[0] == lesson_id:
                _, title, lesson_type, description, author, _ = lesson
                self.lesson_title.setText(title)
                self.lesson_type.setCurrentText(lesson_type)
                self.lesson_description.setText(description)
                break
        
        # Load words for this lesson
        self.load_words(lesson_id)
        
        # Enable editing
        self.set_editing_enabled(True)

    def load_words(self, lesson_id):
        """Load words for the selected lesson"""
        words = self.user_manager.get_lesson_words(lesson_id)
        self.words_table.setRowCount(len(words))
        
        for row, word in enumerate(words):
            word_id, word_text, meaning, example = word
            
            self.words_table.setItem(row, 0, QTableWidgetItem(str(word_id)))
            self.words_table.setItem(row, 1, QTableWidgetItem(word_text))
            self.words_table.setItem(row, 2, QTableWidgetItem(meaning))
            self.words_table.setItem(row, 3, QTableWidgetItem(example or ""))

    def show_create_lesson_dialog(self):
        """Show dialog to create a new lesson"""
        title, ok = QInputDialog.getText(self, "Create New Lesson", "Enter lesson title:")
        if ok and title:
            lesson_type, ok = QInputDialog.getItem(self, "Lesson Type", "Select lesson type:", 
                                                 ["vocabulary", "grammar", "conversation"], 0, False)
            if ok:
                description, ok = QInputDialog.getText(self, "Lesson Description", "Enter description (optional):")
                if ok is not None:
                    success, result = self.user_manager.create_lesson(title, lesson_type, description)
                    if success:
                        QMessageBox.information(self, "Success", "Lesson created successfully!")
                        self.load_lessons()
                    else:
                        QMessageBox.warning(self, "Error", result)

    def update_lesson(self):
        """Update the currently selected lesson"""
        if not self.current_lesson_id:
            return
            
        title = self.lesson_title.text().strip()
        lesson_type = self.lesson_type.currentText()
        description = self.lesson_description.toPlainText().strip()
        
        if not title:
            QMessageBox.warning(self, "Error", "Title is required")
            return
            
        success, result = self.user_manager.update_lesson(self.current_lesson_id, title, lesson_type, description)
        if success:
            QMessageBox.information(self, "Success", "Lesson updated successfully!")
            self.load_lessons()
        else:
            QMessageBox.warning(self, "Error", result)

    def delete_lesson(self):
        """Delete the currently selected lesson"""
        if not self.current_lesson_id:
            return
            
        reply = QMessageBox.question(self, "Confirm Delete", 
                                   "Are you sure you want to delete this lesson? This will also delete all words in this lesson.",
                                   QMessageBox.Yes | QMessageBox.No)
        if reply == QMessageBox.Yes:
            success, result = self.user_manager.delete_lesson(self.current_lesson_id)
            if success:
                QMessageBox.information(self, "Success", "Lesson deleted successfully!")
                self.current_lesson_id = None
                self.lesson_title.clear()
                self.lesson_description.clear()
                self.words_table.setRowCount(0)
                self.set_editing_enabled(False)
                self.load_lessons()
            else:
                QMessageBox.warning(self, "Error", result)

    def add_word(self):
        """Add a new word to the current lesson"""
        if not self.current_lesson_id:
            QMessageBox.warning(self, "Error", "Please select a lesson first")
            return
            
        word = self.new_word.text().strip()
        meaning = self.new_meaning.text().strip()
        example = self.new_example.toPlainText().strip()
        
        if not word or not meaning:
            QMessageBox.warning(self, "Error", "Word and meaning are required")
            return
            
        success, result = self.user_manager.add_word_to_lesson(self.current_lesson_id, word, meaning, example)
        if success:
            QMessageBox.information(self, "Success", "Word added successfully!")
            self.new_word.clear()
            self.new_meaning.clear()
            self.new_example.clear()
            self.load_words(self.current_lesson_id)
        else:
            QMessageBox.warning(self, "Error", result)

    def edit_word(self):
        """Edit the selected word"""
        current_row = self.words_table.currentRow()
        if current_row < 0:
            QMessageBox.warning(self, "Error", "Please select a word to edit")
            return
            
        word_id = int(self.words_table.item(current_row, 0).text())
        current_word = self.words_table.item(current_row, 1).text()
        current_meaning = self.words_table.item(current_row, 2).text()
        current_example = self.words_table.item(current_row, 3).text()
        
        # Get new values
        word, ok = QInputDialog.getText(self, "Edit Word", "Word:", text=current_word)
        if not ok or not word:
            return
            
        meaning, ok = QInputDialog.getText(self, "Edit Meaning", "Meaning:", text=current_meaning)
        if not ok or not meaning:
            return
            
        example, ok = QInputDialog.getText(self, "Edit Example", "Example (optional):", text=current_example)
        if not ok:
            return
            
        success, result = self.user_manager.update_word(word_id, word, meaning, example)
        if success:
            QMessageBox.information(self, "Success", "Word updated successfully!")
            self.load_words(self.current_lesson_id)
        else:
            QMessageBox.warning(self, "Error", result)

    def delete_word(self):
        """Delete the selected word"""
        current_row = self.words_table.currentRow()
        if current_row < 0:
            QMessageBox.warning(self, "Error", "Please select a word to delete")
            return
            
        word_id = int(self.words_table.item(current_row, 0).text())
        word_text = self.words_table.item(current_row, 1).text()
        
        reply = QMessageBox.question(self, "Confirm Delete", 
                                   f"Are you sure you want to delete the word '{word_text}'?",
                                   QMessageBox.Yes | QMessageBox.No)
        if reply == QMessageBox.Yes:
            success, result = self.user_manager.delete_word(word_id)
            if success:
                QMessageBox.information(self, "Success", "Word deleted successfully!")
                self.load_words(self.current_lesson_id)
            else:
                QMessageBox.warning(self, "Error", result)