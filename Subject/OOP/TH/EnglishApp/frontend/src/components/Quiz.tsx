import React, { useState, useEffect } from 'react';
import { useParams, useNavigate } from 'react-router-dom';
import type { Word, Lesson } from '../types';
import { lessonsApi, progressApi } from '../api';

export const Quiz: React.FC = () => {
  const { lessonId } = useParams<{ lessonId: string }>();
  const navigate = useNavigate();
  
  const [lesson, setLesson] = useState<Lesson | null>(null);
  const [words, setWords] = useState<Word[]>([]);
  const [currentIndex, setCurrentIndex] = useState(0);
  const [score, setScore] = useState(0);
  const [userAnswer, setUserAnswer] = useState('');
  const [showResult, setShowResult] = useState(false);
  const [loading, setLoading] = useState(true);

  useEffect(() => {
    if (lessonId) {
      loadLessonData(parseInt(lessonId));
    }
  }, [lessonId]);

  const loadLessonData = async (id: number) => {
    try {
      const [lessonData, wordsData] = await Promise.all([
        lessonsApi.getById(id),
        lessonsApi.getWords(id),
      ]);
      setLesson(lessonData);
      setWords(wordsData);
    } catch (error) {
      console.error('Failed to load lesson data:', error);
    } finally {
      setLoading(false);
    }
  };

  const handleSubmit = () => {
    const currentWord = words[currentIndex];
    if (userAnswer.trim().toLowerCase() === currentWord.meaning.toLowerCase()) {
      setScore(score + 1);
    }

    if (currentIndex < words.length - 1) {
      setCurrentIndex(currentIndex + 1);
      setUserAnswer('');
    } else {
      setShowResult(true);
      // Save progress
      const finalScore = Math.round((score / words.length) * 100);
      progressApi.save(parseInt(lessonId!), finalScore);
    }
  };

  const handleRestart = () => {
    setCurrentIndex(0);
    setScore(0);
    setUserAnswer('');
    setShowResult(false);
  };

  if (loading) {
    return <div className="loading">Loading quiz...</div>;
  }

  if (!lesson) {
    return <div className="error">Lesson not found</div>;
  }

  if (showResult) {
    const percentage = Math.round((score / words.length) * 100);
    
    return (
      <div className="quiz-result">
        <h2>Quiz Completed!</h2>
        <div className="score-card">
          <h3>Your Score</h3>
          <div className="score-percentage">{percentage}%</div>
          <p>{score} out of {words.length} correct</p>
        </div>
        
        <div className="result-actions">
          <button onClick={handleRestart} className="btn btn-primary">
            Try Again
          </button>
          <button onClick={() => navigate('/dashboard')} className="btn btn-secondary">
            Back to Lessons
          </button>
        </div>
      </div>
    );
  }

  const currentWord = words[currentIndex];

  return (
    <div className="quiz">
      <div className="quiz-header">
        <h2>{lesson.title}</h2>
        <div className="quiz-progress">
          Question {currentIndex + 1} of {words.length}
        </div>
      </div>

      <div className="quiz-question">
        <h3>What is the meaning of "{currentWord.word}"?</h3>
        
        {currentWord.example && (
          <p className="word-example">Example: {currentWord.example}</p>
        )}

        <div className="answer-input">
          <input
            type="text"
            value={userAnswer}
            onChange={(e) => setUserAnswer(e.target.value)}
            placeholder="Enter the meaning..."
            onKeyPress={(e) => e.key === 'Enter' && handleSubmit()}
          />
          <button onClick={handleSubmit} className="btn btn-primary">
            Submit
          </button>
        </div>
      </div>
    </div>
  );
};