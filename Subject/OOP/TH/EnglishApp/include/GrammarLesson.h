#pragma once
#include "Lesson.h"
#include <vector>
using namespace std;

/*
Chức năng: Lưu các bài học ngữ pháp
*/
class GrammarLesson : public Lesson {
private:
    vector<string> rules;
    int points;
public:
    GrammarLesson(int id, const string& title, vector<string> r);
    void start() override;
    void showResult() override;
    const std::vector<string>& getRules() const;
    int getGrammarPoints();
};
