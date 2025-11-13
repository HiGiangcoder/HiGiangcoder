import React, { useState, useEffect } from 'react';
import { BrowserRouter as Router, Routes, Route, Navigate } from 'react-router-dom';
import type { User } from './types';
import { Login } from './components/Login';
import { Dashboard } from './components/Dashboard';
import { LessonManager } from './components/LessonManager';
import { Quiz } from './components/Quiz';
import { Progress } from './components/Progress';
import './App.css';

const App: React.FC = () => {
  const [user, setUser] = useState<User | null>(null);
  const [loading, setLoading] = useState(true);

  useEffect(() => {
    // Check if user is logged in (from localStorage)
    const savedUser = localStorage.getItem('user');
    if (savedUser) {
      setUser(JSON.parse(savedUser));
    }
    setLoading(false);
  }, []);

  const handleLogin = (userData: User, token: string) => {
    setUser(userData);
    localStorage.setItem('user', JSON.stringify(userData));
    localStorage.setItem('token', token);
  };

  const handleLogout = () => {
    setUser(null);
    localStorage.removeItem('user');
    localStorage.removeItem('token');
  };

  if (loading) {
    return <div className="loading">Loading...</div>;
  }

  return (
    <Router>
      <div className="app">
        {user ? (
          <div className="app-container">
            <header className="app-header">
              <h1>English Learning App</h1>
              <div className="user-info">
                <span>Welcome, {user.username}!</span>
                <button onClick={handleLogout} className="logout-btn">
                  Logout
                </button>
              </div>
            </header>
            
            <nav className="app-nav">
              <a href="/dashboard">Dashboard</a>
              <a href="/lessons">Manage Lessons</a>
              <a href="/progress">My Progress</a>
            </nav>

            <main className="app-main">
              <Routes>
                <Route path="/" element={<Navigate to="/dashboard" />} />
                <Route path="/dashboard" element={<Dashboard />} />
                <Route path="/lessons" element={<LessonManager />} />
                <Route path="/quiz/:lessonId" element={<Quiz />} />
                <Route path="/progress" element={<Progress />} />
              </Routes>
            </main>
          </div>
        ) : (
          <Login onLogin={handleLogin} />
        )}
      </div>
    </Router>
  );
};

export default App;