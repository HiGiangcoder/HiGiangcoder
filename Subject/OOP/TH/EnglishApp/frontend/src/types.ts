export interface User {
    id: number;
    username: string;
    email?: string;
}

export interface Lesson {
    id: number;
    title: string;
    type: string;
    description?: string;
    created_by?: number;
    author_name?: string;
    created_at: string;
}

export interface Word {
    id: number;
    lesson_id: number;
    word: string;
    meaning: string;
    example?: string;
}

export interface Progress {
    id: number;
    user_id: number;
    lesson_id: number;
    score: number;
    completed_at: string;
    lesson_title: string;
}

export interface LoginRequest {
    username: string;
    password: string;
}

export interface RegisterRequest {
    username: string;
    password: string;
    email?: string;
}