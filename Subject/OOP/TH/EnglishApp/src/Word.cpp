#include "Word.h"
#include <iostream>

Word::Word(const std::string& t, const std::string& m) : text(t), meaning(m) {}

void Word::display() const {
    std::cout << text << " - " << meaning << std::endl;
}

std::string Word::getText() const {
    return text;
}

const std::string& Word::getMeaning() const { 
    return meaning; 
}