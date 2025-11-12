#include "LessonFactory.h"
#include <iostream>

Lesson* LessonFactory::createLesson(const std::string& type, int id, const std::string& title) {
    if (type == "vocabulary") {
        std::vector<Word> dummy = { Word("apple", "quả táo"), Word("book", "quyển sách") };
        return new VocabularyLesson(id, title, dummy);
    } else if (type == "grammar") {
        std::vector<std::string> rules = { "Use 'a' before consonant sounds", "Use 'an' before vowel sounds" };
        return new GrammarLesson(id, title, rules);
    }
    std::cerr << "[Factory] Unknown lesson type: " << type << std::endl;
    return nullptr;
}
