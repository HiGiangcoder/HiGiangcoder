#pragma once
#include "Lesson.h"
#include "Word.h"
#include <vector>

/*
VocabularyLesson: Lop con cua Lesson, quan ly bai hoc tu vung
- id: ma bai hoc
- title: tieu de bai hoc
- words: danh sach cac tu vung trong bai hoc

Kế thừa từ Lesson
Quản lý danh sách Word
Xử lý logic học từ vựng
*/

class VocabularyLesson : public Lesson {
private:
    std::vector<Word> words;
public:
    VocabularyLesson(int id, const std::string& title, std::vector<Word> w);
    void start() override;
    void showResult() override;

    const std::vector<Word>& getWords() const;
};
