#pragma once
#include "Lesson.h"
#include <vector>
using namespace std;

class GrammarLesson : public Lesson {
private:
    vector<string> rules;
public:
    GrammarLesson(int id, const string& title, vector<string> r);
    void start() override;
    void showResult() override;
};

GrammarLesson::GrammarLesson(int id, const string& title, vector<string> r) {
    this->id = id;
    this->title = title;
    this->rules = r;
}

void GrammarLesson::start() {
    printf("Starting Grammar Lesson: %s\n", title.c_str());
    for (const string& rule : rules) {
        printf("Rule: %s\n", rule.c_str());
    }
}

void GrammarLesson::showResult() {
    printf("Grammar Lesson %s completed. Total rules: %zu\n", title.c_str(), rules.size());
}