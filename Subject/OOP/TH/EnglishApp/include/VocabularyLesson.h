#pragma once
#include "Lesson.h"
#include "Word.h"
#include <vector>

class VocabularyLesson : public Lesson {
private:
    std::vector<Word> words;
public:
    VocabularyLesson(int id, const std::string& title, std::vector<Word> w);
    void start() override;
    void showResult() override;
};

/*
VocabularyLesson: Lop con cua Lesson, quan ly bai hoc tu vung
- id: ma bai hoc
- title: tieu de bai hoc
- words: danh sach cac tu vung trong bai hoc
*/
inline VocabularyLesson::VocabularyLesson(int id, const std::string& title, std::vector<Word> w) {
    this->id = id;
    this->title = title;
    this->words = w;
}

inline void VocabularyLesson::start() {
    printf("Starting Vocabulary Lesson: %s\n", title.c_str());
    for (const auto& word : words) {
        word.display();
    }
}

inline void VocabularyLesson::showResult() {
    printf("Vocabulary Lesson %s completed. Total words: %zu\n", title.c_str(), words.size());
}