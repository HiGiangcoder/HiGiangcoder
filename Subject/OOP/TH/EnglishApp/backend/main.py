from fastapi import FastAPI, HTTPException, Depends
from fastapi.middleware.cors import CORSMiddleware
from pydantic import BaseModel
from typing import List, Optional
import sqlite3
import hashlib
from datetime import datetime

app = FastAPI(title="English Learning App API")

# CORS middleware để frontend có thể kết nối
app.add_middleware(
    CORSMiddleware,
    allow_origins=["http://localhost:3000", "http://localhost:5173"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

# Database setup
DATABASE_PATH = "../data/english.db"

def get_db():
    conn = sqlite3.connect(DATABASE_PATH)
    conn.row_factory = sqlite3.Row
    try:
        yield conn
    finally:
        conn.close()

# Pydantic models
class UserLogin(BaseModel):
    username: str
    password: str

class UserRegister(BaseModel):
    username: str
    password: str
    email: Optional[str] = None

class UserResponse(BaseModel):
    id: int
    username: str
    email: Optional[str]

class LessonBase(BaseModel):
    title: str
    type: str
    description: Optional[str] = None

class LessonCreate(LessonBase):
    pass

class LessonResponse(LessonBase):
    id: int
    created_by: Optional[int]
    author_name: Optional[str]
    created_at: str

class WordBase(BaseModel):
    word: str
    meaning: str
    example: Optional[str] = None

class WordCreate(WordBase):
    lesson_id: int

class WordResponse(WordBase):
    id: int
    lesson_id: int

class ProgressCreate(BaseModel):
    lesson_id: int
    score: int

class ProgressResponse(BaseModel):
    id: int
    user_id: int
    lesson_id: int
    score: int
    completed_at: str
    lesson_title: str

# Utility functions
def hash_password(password: str) -> str:
    return hashlib.sha256(password.encode()).hexdigest()

def get_current_user(conn: sqlite3.Connection, token: str) -> dict:
    # Simple token-based auth (in production, use JWT)
    try:
        user_id = int(token)
        cursor = conn.cursor()
        cursor.execute("SELECT id, username, email FROM users WHERE id = ?", (user_id,))
        user = cursor.fetchone()
        if user:
            return dict(user)
    except:
        pass
    raise HTTPException(status_code=401, detail="Invalid authentication")

# API Routes

@app.post("/register", response_model=dict)
def register(user: UserRegister, conn: sqlite3.Connection = Depends(get_db)):
    cursor = conn.cursor()
    
    # Check if username exists
    cursor.execute("SELECT id FROM users WHERE username = ?", (user.username,))
    if cursor.fetchone():
        raise HTTPException(status_code=400, detail="Username already exists")
    
    # Create user
    password_hash = hash_password(user.password)
    cursor.execute(
        "INSERT INTO users (username, password_hash, email) VALUES (?, ?, ?)",
        (user.username, password_hash, user.email)
    )
    user_id = cursor.lastrowid
    conn.commit()
    
    return {"message": "User registered successfully", "user_id": user_id}

@app.post("/login", response_model=dict)
def login(user: UserLogin, conn: sqlite3.Connection = Depends(get_db)):
    cursor = conn.cursor()
    
    password_hash = hash_password(user.password)
    cursor.execute(
        "SELECT id, username, email FROM users WHERE username = ? AND password_hash = ?",
        (user.username, password_hash)
    )
    user_data = cursor.fetchone()
    
    if user_data:
        return {
            "message": "Login successful",
            "user": dict(user_data),
            "token": str(user_data['id'])  # Simple token (user_id)
        }
    else:
        raise HTTPException(status_code=401, detail="Invalid username or password")

# Lessons endpoints
@app.get("/lessons", response_model=List[LessonResponse])
def get_lessons(conn: sqlite3.Connection = Depends(get_db)):
    cursor = conn.cursor()
    cursor.execute("""
        SELECT l.id, l.title, l.type, l.description, l.created_by, u.username as author_name, l.created_at
        FROM lessons l 
        LEFT JOIN users u ON l.created_by = u.id
        ORDER BY l.created_at DESC
    """)
    lessons = [dict(row) for row in cursor.fetchall()]
    return lessons

@app.get("/lessons/{lesson_id}", response_model=LessonResponse)
def get_lesson(lesson_id: int, conn: sqlite3.Connection = Depends(get_db)):
    cursor = conn.cursor()
    cursor.execute("""
        SELECT l.id, l.title, l.type, l.description, l.created_by, u.username as author_name, l.created_at
        FROM lessons l 
        LEFT JOIN users u ON l.created_by = u.id
        WHERE l.id = ?
    """, (lesson_id,))
    lesson = cursor.fetchone()
    if not lesson:
        raise HTTPException(status_code=404, detail="Lesson not found")
    return dict(lesson)

@app.post("/lessons", response_model=dict)
def create_lesson(
    lesson: LessonCreate,
    conn: sqlite3.Connection = Depends(get_db),
    token: str = Depends(lambda: None)  # Simple auth
):
    # In a real app, you'd get user from token
    user_id = 1  # Default user for demo
    
    cursor = conn.cursor()
    cursor.execute(
        "INSERT INTO lessons (title, type, description, created_by) VALUES (?, ?, ?, ?)",
        (lesson.title, lesson.type, lesson.description, user_id)
    )
    lesson_id = cursor.lastrowid
    conn.commit()
    
    return {"message": "Lesson created successfully", "lesson_id": lesson_id}

@app.get("/lessons/{lesson_id}/words", response_model=List[WordResponse])
def get_lesson_words(lesson_id: int, conn: sqlite3.Connection = Depends(get_db)):
    cursor = conn.cursor()
    cursor.execute("""
        SELECT id, lesson_id, word, meaning, example 
        FROM words 
        WHERE lesson_id = ?
        ORDER BY id
    """, (lesson_id,))
    words = [dict(row) for row in cursor.fetchall()]
    return words

@app.post("/words", response_model=dict)
def add_word(word: WordCreate, conn: sqlite3.Connection = Depends(get_db)):
    cursor = conn.cursor()
    cursor.execute(
        "INSERT INTO words (lesson_id, word, meaning, example) VALUES (?, ?, ?, ?)",
        (word.lesson_id, word.word, word.meaning, word.example)
    )
    conn.commit()
    return {"message": "Word added successfully"}

# Progress endpoints
@app.post("/progress", response_model=dict)
def save_progress(progress: ProgressCreate, conn: sqlite3.Connection = Depends(get_db)):
    user_id = 1  # Default user for demo
    
    cursor = conn.cursor()
    cursor.execute("""
        INSERT INTO user_progress (user_id, lesson_id, score) 
        VALUES (?, ?, ?)
    """, (user_id, progress.lesson_id, progress.score))
    conn.commit()
    return {"message": "Progress saved successfully"}

@app.get("/progress", response_model=List[ProgressResponse])
def get_user_progress(conn: sqlite3.Connection = Depends(get_db)):
    user_id = 1  # Default user for demo
    
    cursor = conn.cursor()
    cursor.execute("""
        SELECT up.id, up.user_id, up.lesson_id, up.score, up.completed_at, l.title as lesson_title
        FROM user_progress up
        JOIN lessons l ON up.lesson_id = l.id
        WHERE up.user_id = ?
        ORDER BY up.completed_at DESC
    """, (user_id,))
    progress = [dict(row) for row in cursor.fetchall()]
    return progress

if __name__ == "__main__":
    import uvicorn
    uvicorn.run(app, host="0.0.0.0", port=8000)