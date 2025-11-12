#include "GrammarLesson.h"
#include <iostream>

GrammarLesson::GrammarLesson(int id, const std::string& title, std::vector<std::string> r)
    : Lesson(id, title, "Grammar Lesson"), rules(std::move(r)), points(0) {}

void GrammarLesson::start() {
    std::cout << "\n[Lesson] Grammar: " << title << "\n";
    // ... (hiển thị quy tắc và câu ví dụ)
}

void GrammarLesson::showResult() {
    std::cout << "[Result] Grammar lesson complete.\n";
}

const std::vector<string>& GrammarLesson::getRules() const {
    return rules; 
}

int GrammarLesson::getGrammarPoints() {
    return points;
}