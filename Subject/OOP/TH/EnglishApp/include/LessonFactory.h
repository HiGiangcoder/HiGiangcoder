#pragma once
#include "Lesson.h"
#include "VocabularyLesson.h"
#include "GrammarLesson.h"
#include <string>
#include <vector>

using namespace std;

class LessonFactory {
public:
    static Lesson* createLesson(const string& type, int id, const string& title);
};

Lesson* LessonFactory::createLesson(const string& type, int id, const string& title) {
    if (type == "vocabulary") {
        // For simplicity, creating a VocabularyLesson with empty words
        return new VocabularyLesson(id, title, vector<Word>{});
    } else if (type == "grammar") {
        // For simplicity, creating a GrammarLesson with empty rules
        return new GrammarLesson(id, title, vector<string>{});
    }
    return nullptr;
}