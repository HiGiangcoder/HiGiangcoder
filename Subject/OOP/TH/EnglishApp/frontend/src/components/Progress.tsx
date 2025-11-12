import React, { useState, useEffect } from 'react';
import type { Progress as ProgressType } from '../types';
import { progressApi } from '../api';

export const Progress: React.FC = () => {
    const [progress, setProgress] = useState<ProgressType[]>([]);
    const [loading, setLoading] = useState(true);

    useEffect(() => {
        loadProgress();
    }, []);

    const loadProgress = async () => {
    try {
        const progressData = await progressApi.getUserProgress();
        setProgress(progressData);
    } catch (error) {
        console.error('Failed to load progress:', error);
    } finally {
        setLoading(false);
    }
};

if (loading) {
    return <div className="loading">Loading progress...</div>;
}

return (
    <div className="progress-page">
    <h2>My Learning Progress</h2>

    {progress.length === 0 ? (
        <div className="no-progress">
        <p>You haven't completed any lessons yet.</p>
        <p>Start learning to see your progress here!</p>
        </div>
    ) : (
        <div className="progress-list">
        <table className="progress-table">
            <thead>
            <tr>
                <th>Lesson</th>
                <th>Score</th>
                <th>Completed At</th>
            </tr>
            </thead>
            <tbody>
            {progress.map((item) => (
                <tr key={item.id}>
                <td>{item.lesson_title}</td>
                <td>
                    <div className="score-bar">
                    <div 
                        className="score-fill"
                        style={{ width: `${item.score}%` }}
                    ></div>
                    <span className="score-text">{item.score}%</span>
                    </div>
                </td>
                <td>{new Date(item.completed_at).toLocaleDateString()}</td>
                </tr>
            ))}
            </tbody>
        </table>
        </div>
    )}
    </div>
);
};