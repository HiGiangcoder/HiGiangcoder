import React, { useState, useEffect } from 'react';
import type { Lesson, Word } from '../types';
import { lessonsApi, wordsApi } from '../api';

export const LessonManager: React.FC = () => {
  const [lessons, setLessons] = useState<Lesson[]>([]);
  const [selectedLesson, setSelectedLesson] = useState<Lesson | null>(null);
  const [words, setWords] = useState<Word[]>([]);
  const [newLesson, setNewLesson] = useState({ title: '', type: 'vocabulary', description: '' });
  const [newWord, setNewWord] = useState({ word: '', meaning: '', example: '' });
  const [loading, setLoading] = useState(false);

  useEffect(() => {
    loadLessons();
  }, []);

  const loadLessons = async () => {
    try {
      const lessonsData = await lessonsApi.getAll();
      setLessons(lessonsData);
    } catch (error) {
      console.error('Failed to load lessons:', error);
    }
  };

  const loadWords = async (lessonId: number) => {
    try {
      const wordsData = await lessonsApi.getWords(lessonId);
      setWords(wordsData);
    } catch (error) {
      console.error('Failed to load words:', error);
    }
  };

  const handleCreateLesson = async (e: React.FormEvent) => {
    e.preventDefault();
    setLoading(true);
    try {
      await lessonsApi.create(newLesson);
      setNewLesson({ title: '', type: 'vocabulary', description: '' });
      loadLessons();
      alert('Lesson created successfully!');
    } catch (error) {
      console.error('Failed to create lesson:', error);
      alert('Failed to create lesson');
    } finally {
      setLoading(false);
    }
  };

  const handleAddWord = async (e: React.FormEvent) => {
    e.preventDefault();
    if (!selectedLesson) {
      alert('Please select a lesson first');
      return;
    }
    setLoading(true);
    try {
      await wordsApi.create({ ...newWord, lesson_id: selectedLesson.id });
      setNewWord({ word: '', meaning: '', example: '' });
      loadWords(selectedLesson.id);
      alert('Word added successfully!');
    } catch (error) {
      console.error('Failed to add word:', error);
      alert('Failed to add word');
    } finally {
      setLoading(false);
    }
  };

  const handleLessonSelect = (lesson: Lesson) => {
    setSelectedLesson(lesson);
    loadWords(lesson.id);
  };

  return (
    <div className="lesson-manager">
      <h2>Manage Lessons</h2>
      
      <div className="manager-content">
        {/* Create New Lesson */}
        <div className="create-lesson-section">
          <h3>Create New Lesson</h3>
          <form onSubmit={handleCreateLesson} className="lesson-form">
            <input
              type="text"
              placeholder="Lesson Title"
              value={newLesson.title}
              onChange={(e) => setNewLesson({ ...newLesson, title: e.target.value })}
              required
            />
            <select
              value={newLesson.type}
              onChange={(e) => setNewLesson({ ...newLesson, type: e.target.value })}
            >
              <option value="vocabulary">Vocabulary</option>
              <option value="grammar">Grammar</option>
              <option value="conversation">Conversation</option>
            </select>
            <textarea
              placeholder="Description (optional)"
              value={newLesson.description}
              onChange={(e) => setNewLesson({ ...newLesson, description: e.target.value })}
            />
            <button type="submit" disabled={loading}>
              {loading ? 'Creating...' : 'Create Lesson'}
            </button>
          </form>
        </div>

        {/* Lessons List */}
        <div className="lessons-section">
          <h3>Existing Lessons</h3>
          <div className="lessons-list">
            {lessons.map(lesson => (
              <div
                key={lesson.id}
                className={`lesson-item ${selectedLesson?.id === lesson.id ? 'selected' : ''}`}
                onClick={() => handleLessonSelect(lesson)}
              >
                <h4>{lesson.title}</h4>
                <p>Type: {lesson.type}</p>
                {lesson.description && <p>{lesson.description}</p>}
                {lesson.author_name && <p className="author">By: {lesson.author_name}</p>}
              </div>
            ))}
          </div>
        </div>

        {/* Words Management */}
        {selectedLesson && (
          <div className="words-section">
            <h3>Words in {selectedLesson.title}</h3>
            
            {/* Add New Word */}
            <form onSubmit={handleAddWord} className="word-form">
              <h4>Add New Word</h4>
              <input
                type="text"
                placeholder="Word"
                value={newWord.word}
                onChange={(e) => setNewWord({ ...newWord, word: e.target.value })}
                required
              />
              <input
                type="text"
                placeholder="Meaning"
                value={newWord.meaning}
                onChange={(e) => setNewWord({ ...newWord, meaning: e.target.value })}
                required
              />
              <input
                type="text"
                placeholder="Example (optional)"
                value={newWord.example}
                onChange={(e) => setNewWord({ ...newWord, example: e.target.value })}
              />
              <button type="submit" disabled={loading}>
                {loading ? 'Adding...' : 'Add Word'}
              </button>
            </form>

            {/* Words List */}
            <div className="words-list">
              <h4>Current Words</h4>
              {words.length === 0 ? (
                <p>No words in this lesson yet.</p>
              ) : (
                words.map(word => (
                  <div key={word.id} className="word-item">
                    <strong>{word.word}</strong> - {word.meaning}
                    {word.example && <div className="example">Example: {word.example}</div>}
                  </div>
                ))
              )}
            </div>
          </div>
        )}
      </div>
    </div>
  );
};