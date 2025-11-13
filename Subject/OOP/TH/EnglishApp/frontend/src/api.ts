import axios from 'axios';
import type { User, Lesson, Word, Progress, LoginRequest, RegisterRequest } from './types';

const API_BASE = 'http://localhost:8000';

const api = axios.create({
  baseURL: API_BASE,
  headers: {
    'Content-Type': 'application/json',
  },
});

// Auth API
export const authApi = {
  login: async (credentials: LoginRequest): Promise<{ user: User; token: string }> => {
    const response = await api.post('/login', credentials);
    return response.data;
  },

  register: async (userData: RegisterRequest): Promise<{ message: string; user_id: number }> => {
    const response = await api.post('/register', userData);
    return response.data;
  },
};

// Lessons API
export const lessonsApi = {
  getAll: async (): Promise<Lesson[]> => {
    const response = await api.get('/lessons');
    return response.data;
  },

  getById: async (id: number): Promise<Lesson> => {
    const response = await api.get(`/lessons/${id}`);
    return response.data;
  },

  create: async (lesson: Omit<Lesson, 'id' | 'created_at'>): Promise<{ lesson_id: number }> => {
    const response = await api.post('/lessons', lesson);
    return response.data;
  },

  getWords: async (lessonId: number): Promise<Word[]> => {
    const response = await api.get(`/lessons/${lessonId}/words`);
    return response.data;
  },
};

// Words API
export const wordsApi = {
  create: async (word: Omit<Word, 'id'>): Promise<{ message: string }> => {
    const response = await api.post('/words', word);
    return response.data;
  },
};

// Progress API
export const progressApi = {
  save: async (lessonId: number, score: number): Promise<{ message: string }> => {
    const response = await api.post('/progress', { lesson_id: lessonId, score });
    return response.data;
  },

  getUserProgress: async (): Promise<Progress[]> => {
    const response = await api.get('/progress');
    return response.data;
  },
};

export default api;