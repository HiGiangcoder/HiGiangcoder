#pragma once
#include <string>
#include <vector>
#include <Word.h>

using namespace std;

/*
Chức năng: 
    Lớp trừu tượng (abstract base class) Đại diện cho mọi loại lesson
    Cung cấp Interface chung: start(), showResult()
*/
class Lesson {
protected:
    int id;
    string title;
    string lesson_type;
public:
    Lesson(int id, const string& title, string lesson_type);
    virtual void start() = 0; // Phuong thuc truu tuong: Hàm thuần ảo
    virtual void showResult() = 0;
    virtual ~Lesson() = default;
    const std::string& getTitle() const { return title; }
    int getId();
    std::string getType();
};
