#pragma once
#include <string>
using namespace std;

class Word {
private:
    string text;
    string meaning;
public:
    Word(const string& t, const string& m);
    void display() const;
    string getText() const;
};

Word::Word(const string& t, const string& m) : text(t), meaning(m) {}

void Word::display() const {
    printf("Word: %s, Meaning: %s\n", text.c_str(), meaning.c_str());
}

string Word::getText() const {
    return text;
}