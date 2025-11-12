#include "DatabaseDAO.h"
#include "LessonFactory.h"
#include <iostream>

DatabaseDAO::DatabaseDAO(Database* db) : db(db) {}

std::vector<Word> DatabaseDAO::loadWords() {
    std::vector<Word> words;
    auto rows = db->query("SELECT text, meaning FROM words;");
    for (auto& row : rows) {
        words.emplace_back(row[0], row[1]);
    }
    return words;
}

std::vector<Lesson*> DatabaseDAO::loadLessons() {
    std::vector<Lesson*> lessons;
    auto rows = db->query("SELECT id, title, type FROM lessons;");
    for (auto& row : rows) {
        int id = std::stoi(row[0]);
        std::string title = row[1];
        std::string type = row[2];
        lessons.push_back(LessonFactory::createLesson(type, id, title));
    }
    return lessons;
}

void DatabaseDAO::saveUserProcess(const User& user) {
    // Tùy chọn: update bảng "progress" trong DB
    std::cout << "[DatabaseDAO] Saving user progress..." << std::endl;
}
