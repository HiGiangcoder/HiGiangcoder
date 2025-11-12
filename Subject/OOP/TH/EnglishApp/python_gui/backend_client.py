"""
Client để giao tiếp với C++ backend
Nếu C++ backend không khả dụng, sẽ sử dụng Python fallback
"""

import os
import sys

class BackendClient:
    def __init__(self):
        self.backend_available = False
        self.backend = None
        self.setup_backend()
    
    def setup_backend(self):
        """Thiết lập kết nối với C++ backend"""
        try:
            # Thử import C++ backend
            from englishapp import EnglishApp, VocabularyLesson, Word
            self.backend = EnglishApp()
            self.backend_available = True
            print("✓ C++ Backend loaded successfully")
        except ImportError as e:
            print(f"✗ C++ Backend not available: {e}")
            print("✓ Using Python fallback backend")
            self.backend = PythonBackend()
    
    def get_lessons(self):
        """Lấy danh sách lessons từ backend"""
        if self.backend_available:
            try:
                return self.backend.getLessons()
            except Exception as e:
                print(f"Error getting lessons from C++ backend: {e}")
                return []
        else:
            return self.backend.get_lessons()
    
    def start_lesson(self, lesson):
        """Bắt đầu một lesson"""
        if self.backend_available:
            lesson.start()
        else:
            self.backend.start_lesson(lesson)
    
    def is_cpp_backend(self):
        """Kiểm tra xem có đang dùng C++ backend không"""
        return self.backend_available


class PythonBackend:
    """Python fallback backend khi C++ không khả dụng"""
    
    def __init__(self):
        self.lessons = []
        self.setup_demo_lessons()
    
    def setup_demo_lessons(self):
        """Thiết lập lessons demo"""
        # Tạo lessons demo đơn giản
        demo_lessons = [
            {"id": 1, "title": "Animals Vocabulary", "type": "vocabulary", "words": [
                {"text": "cat", "meaning": "con mèo", "example": "The cat is sleeping"},
                {"text": "dog", "meaning": "con chó", "example": "The dog is barking"}
            ]},
            {"id": 2, "title": "Food Vocabulary", "type": "vocabulary", "words": [
                {"text": "apple", "meaning": "quả táo", "example": "I eat an apple"},
                {"text": "rice", "meaning": "cơm", "example": "We eat rice"}
            ]},
            {"id": 3, "title": "Basic Grammar", "type": "grammar", "words": [
                {"text": "present simple", "meaning": "thì hiện tại đơn", "example": "I work every day"}
            ]}
        ]
        
        for lesson_data in demo_lessons:
            lesson = PythonLesson(lesson_data)
            self.lessons.append(lesson)
    
    def get_lessons(self):
        return self.lessons
    
    def start_lesson(self, lesson):
        lesson.start()


class PythonLesson:
    """Python implementation của Lesson"""
    
    def __init__(self, data):
        self.id = data["id"]
        self.title = data["title"]
        self.type = data["type"]
        self.words = [PythonWord(word) for word in data["words"]]
    
    def getTitle(self):
        return self.title
    
    def getType(self):
        return self.type
    
    def getId(self):
        return self.id
    
    def getWords(self):
        return self.words
    
    def start(self):
        print(f"Starting lesson: {self.title}")
        # Logic học lesson có thể thêm ở đây


class PythonWord:
    """Python implementation của Word"""
    
    def __init__(self, data):
        self.text = data["text"]
        self.meaning = data["meaning"]
        self.example = data.get("example", "")
    
    def getText(self):
        return self.text
    
    def getMeaning(self):
        return self.meaning
    
    def getExample(self):
        return self.example