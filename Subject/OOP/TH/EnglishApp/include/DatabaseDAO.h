#pragma once
#include "Database.h"
#include "Word.h"
#include "Lesson.h"
#include "User.h"

class DatabaseDAO {
private:
    Database* db;
public:
    explicit DatabaseDAO(Database* db);
    std::vector<Word> loadWords();
    std::vector<Lesson*> loadLessons();
    void saveUserProcess(const User& user);
};

