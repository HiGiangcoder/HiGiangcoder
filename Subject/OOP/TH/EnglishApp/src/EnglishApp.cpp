#include <string>
#include <iostream>

#ifdef _WIN32
#include <conio.h>
std::string inputPassword(const std::string& prompt) {
    std::cout << prompt;
    std::string password;
    char ch;
    while ((ch = _getch()) != '\r') {  // enter key
        if (ch == '\b' && !password.empty()) {
            password.pop_back();
            std::cout << "\b \b";
        } else if (ch != '\b') {
            password.push_back(ch);
            std::cout << '*';
        }
    }
    std::cout << std::endl;
    return password;
}
#else
#include <termios.h>
#include <unistd.h>

std::string inputPassword(const std::string& prompt) {
    std::cout << prompt;
    termios oldt{}, newt{};
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~ECHO; // Tắt hiển thị ký tự
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    std::string password;
    std::getline(std::cin, password);

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Bật lại echo
    std::cout << std::endl;
    return password;
}
#endif


#include "EnglishApp.h"
#include <iostream>

EnglishApp::EnglishApp() : dao(&db), user("Guest", "123456") {
    db.connect("data/english.db");
}

void EnglishApp::run() {
    Logger::info("EnglishApp started.");
    
    std::cout << "Enter username: ";
    std::string username;
    std::getline(std::cin, username);

    std::string password = inputPassword("Enter password: ");

    if (!user.authenticate(password)) {
        std::cout << "❌ Wrong password. Exiting...\n";
        return;
    }

    auto lessons = dao.loadLessons();

// void EnglishApp::run() {
//     Logger::info("EnglishApp started.");
//     auto lessons = dao.loadLessons();

    while (true) {
        std::cout << "\n--- English Learning CLI ---\n";
        std::cout << "1. View Lessons\n2. Exit\n> ";
        int choice;
        std::cin >> choice;
        std::cin.ignore();
        if (choice == 2) break;

        if (choice == 1) {
            int i = 1;
            for (auto* l : lessons)
                std::cout << i++ << ". " << "Lesson ID " << i-1 << "\n";

            std::cout << "Select lesson: ";
            int sel; std::cin >> sel; std::cin.ignore();
            if (sel > 0 && sel <= (int)lessons.size()) {
                lessons[sel - 1]->start();
                lessons[sel - 1]->showResult();
                user.completeLesson("Lesson_" + std::to_string(sel));
            }
        }
    }

    db.close();
    Logger::info("Application closed.");
}

std::vector<Lesson*> EnglishApp::getLessons() { 
    return this->dao.loadLessons(); 
}

User& EnglishApp::getUser() { 
    return this->user; 
}