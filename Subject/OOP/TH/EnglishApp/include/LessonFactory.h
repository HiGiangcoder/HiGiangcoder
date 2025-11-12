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
