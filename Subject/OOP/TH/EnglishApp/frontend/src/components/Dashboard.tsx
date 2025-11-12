import React, { useState, useEffect } from 'react';
import { Link } from 'react-router-dom';
import type { Lesson } from '../types';
import { lessonsApi } from '../api';

export const Dashboard: React.FC = () => {
  const [lessons, setLessons] = useState<Lesson[]>([]);
  const [loading, setLoading] = useState(true);

  useEffect(() => {
    loadLessons();
  }, []);

  const loadLessons = async () => {
    try {
      const lessonsData = await lessonsApi.getAll();
      setLessons(lessonsData);
    } catch (error) {
      console.error('Failed to load lessons:', error);
    } finally {
      setLoading(false);
    }
  };

  if (loading) {
    return <div className="loading">Loading lessons...</div>;
  }

  return (
    <div className="dashboard">
      <h2>Available Lessons</h2>
      
      <div className="lessons-grid">
        {lessons.map(lesson => (
          <div key={lesson.id} className="lesson-card">
            <h3>{lesson.title}</h3>
            <p className="lesson-type">{lesson.type}</p>
            {lesson.description && (
              <p className="lesson-description">{lesson.description}</p>
            )}
            {lesson.author_name && (
              <p className="lesson-author">By: {lesson.author_name}</p>
            )}
            
            <div className="lesson-actions">
              <Link to={`/quiz/${lesson.id}`} className="btn btn-primary">
                Start Lesson
              </Link>
            </div>
          </div>
        ))}
      </div>

      {lessons.length === 0 && (
        <div className="no-lessons">
          <p>No lessons available. Create some lessons to get started!</p>
          <Link to="/lessons" className="btn btn-secondary">
            Manage Lessons
          </Link>
        </div>
      )}
    </div>
  );
};