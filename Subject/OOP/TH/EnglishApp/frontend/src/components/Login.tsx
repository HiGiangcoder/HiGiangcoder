import React, { useState } from 'react';
import type { User, LoginRequest, RegisterRequest } from '../types';
import { authApi } from '../api';

interface LoginProps {
    onLogin: (user: User, token: string) => void;
}

export const Login: React.FC<LoginProps> = ({ onLogin }) => {
    const [isLogin, setIsLogin] = useState(true);
    const [formData, setFormData] = useState<LoginRequest & RegisterRequest>({
        username: '',
        password: '',
        email: '',
    });
    const [error, setError] = useState('');
    const [loading, setLoading] = useState(false);

    const handleSubmit = async (e: React.FormEvent) => {
        e.preventDefault();
        setLoading(true);
        setError('');

        try {
            if (isLogin) {
                const { user, token } = await authApi.login(formData);
                onLogin(user, token);
        } else {
            await authApi.register(formData);
            // Auto login after registration
            const { user, token } = await authApi.login(formData);
            onLogin(user, token);
        } 
    } catch (err: any) {
        setError(err.response?.data?.detail || 'An error occurred');
    } finally {
        setLoading(false);
    }
};

const handleChange = (e: React.ChangeEvent<HTMLInputElement>) => {
    setFormData(prev => ({
        ...prev,
        [e.target.name]: e.target.value,
    }));
};

return (
    <div className="login-container">
    <div className="login-card">
        <h2>{isLogin ? 'Login' : 'Register'}</h2>
        
        {error && <div className="error-message">{error}</div>}
        
        <form onSubmit={handleSubmit}>
          <div className="form-group">
            <label htmlFor="username">Username</label>
            <input
              type="text"
              id="username"
              name="username"
              value={formData.username}
              onChange={handleChange}
              required
            />
          </div>

          {!isLogin && (
            <div className="form-group">
              <label htmlFor="email">Email (optional)</label>
              <input
                type="email"
                id="email"
                name="email"
                value={formData.email}
                onChange={handleChange}
              />
            </div>
          )}

          <div className="form-group">
            <label htmlFor="password">Password</label>
            <input
              type="password"
              id="password"
              name="password"
              value={formData.password}
              onChange={handleChange}
              required
            />
          </div>

          <button type="submit" disabled={loading} className="submit-btn">
            {loading ? 'Loading...' : (isLogin ? 'Login' : 'Register')}
          </button>
        </form>

        <p>
          {isLogin ? "Don't have an account? " : "Already have an account? "}
          <button
            type="button"
            className="link-btn"
            onClick={() => setIsLogin(!isLogin)}
          >
            {isLogin ? 'Register' : 'Login'}
          </button>
        </p>
      </div>
    </div>
  );
};