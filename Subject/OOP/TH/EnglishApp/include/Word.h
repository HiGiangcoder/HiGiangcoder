#pragma once
#include <string>
using namespace std;

/*
Chức năng: Đại diện cho một từ vựng.
*/
class Word {
private:
    int id;
    string text;
    string meaning;
    string example;
public:
    Word(const string& t, const string& m);
    void display() const;
    string getText() const;
    const std::string& getMeaning() const;
};
