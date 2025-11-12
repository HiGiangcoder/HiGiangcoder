#include "DatabaseDAO.h"
#include "LessonFactory.h"
#include <iostream>

DatabaseDAO::DatabaseDAO(Database* db) : db(db) {}

std::vector<Word> DatabaseDAO::loadWords() {
    std::vector<Word> words;
    auto rows = db->query("SELECT word, meaning FROM words;");
    for (auto& row : rows) {
        if (row.size() >= 2) {
            words.emplace_back(row[0], row[1]);
        }
    }
    std::cout << "[DatabaseDAO] Loaded " << words.size() << " words" << std::endl;
    return words;
}

std::vector<Lesson*> DatabaseDAO::loadLessons() {
    std::vector<Lesson*> lessons;
    auto rows = db->query("SELECT id, title, type FROM lessons;");
    std::cout << "[DatabaseDAO] Found " << rows.size() << " lessons in database" << std::endl;
    
    for (auto& row : rows) {
        if (row.size() >= 3) {
            int id = std::stoi(row[0]);
            std::string title = row[1];
            std::string type = row[2];
            
            // Load words for this specific lesson
            auto words_rows = db->query("SELECT word, meaning FROM words WHERE lesson_id = " + row[0] + ";");
            std::vector<Word> lesson_words;
            for (auto& word_row : words_rows) {
                if (word_row.size() >= 2) {
                    lesson_words.emplace_back(word_row[0], word_row[1]);
                }
            }
            
            std::cout << "[DatabaseDAO] Lesson " << id << ": " << title << " (" << type << ") with " << lesson_words.size() << " words" << std::endl;
            
            if (type == "vocabulary") {
                lessons.push_back(new VocabularyLesson(id, title, lesson_words));
            } else if (type == "grammar") {
                std::vector<std::string> rules = {"Rule 1", "Rule 2"}; // Placeholder
                lessons.push_back(new GrammarLesson(id, title, rules));
            } else {
                std::cerr << "[DatabaseDAO] Unknown lesson type: " << type << std::endl;
            }
        }
    }
    return lessons;
}

void DatabaseDAO::saveUserProcess(const User& user) {
    std::cout << "[DatabaseDAO] Saving user progress..." << std::endl;
}