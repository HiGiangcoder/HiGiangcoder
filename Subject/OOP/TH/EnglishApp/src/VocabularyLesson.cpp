#include "VocabularyLesson.h"
#include <iostream>

VocabularyLesson::VocabularyLesson(int id, const std::string& title, std::vector<Word> w) 
    : Lesson(id, title, "Vocabulary Lesson"), words(w) {}

inline void VocabularyLesson::showResult() {
    printf("Vocabulary Lesson %s completed. Total words: %zu\n", title.c_str(), words.size());
}

const std::vector<Word>& VocabularyLesson::getWords() const {
    return words; 
}

void VocabularyLesson::start() {
    std::cout << "\n[Lesson] Vocabulary: " << title << "\n";
    std::cout << "----------------------------------\n";

    int correct = 0;
    int total = words.size();

    for (auto& word : words) {
        std::cout << "→ What is the meaning of \"" << word.getText() << "\"? ";
        std::string answer;
        std::getline(std::cin, answer);

        // chuẩn hóa chuỗi (bỏ khoảng trắng thừa, chuyển về chữ thường)
        auto normalize = [](std::string s) {
            s.erase(0, s.find_first_not_of(" \t\n\r"));
            s.erase(s.find_last_not_of(" \t\n\r") + 1);
            for (auto& c : s) c = std::tolower(c);
            return s;
        };

        if (normalize(answer) == normalize(word.getMeaning())) {
            std::cout << "✅ Correct!\n";
            ++correct;
        } else {
            std::cout << "❌ Wrong! The correct meaning is: " << word.getMeaning() << "\n";
        }
        std::cout << "----------------------------------\n";
    }

    double score = (total > 0) ? (correct * 100.0 / total) : 0.0;
    std::cout << "[Result] You got " << correct << "/" << total 
              << " words correct (" << score << "%)\n";
}
