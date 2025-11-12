#include "Lesson.h"

Lesson::Lesson(int id, const std::string& title, string lesson_type)
    : id(id), title(title), lesson_type(lesson_type) {}

int Lesson::getId() {
    return this->id;
}

std::string Lesson::getType() {
    return this->lesson_type;
}
