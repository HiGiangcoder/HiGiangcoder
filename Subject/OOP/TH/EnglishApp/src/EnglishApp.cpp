#include "EnglishApp.h"
#include <iostream>
#include <sys/stat.h> // Thêm cho mkdir

EnglishApp::EnglishApp() : dao(&db), user("Guest", "123456") {
    // Tạo thư mục data nếu chưa tồn tại
    struct stat info;
    if (stat("data", &info) != 0) {
        // Thư mục không tồn tại, tạo mới
        mkdir("data", 0755);
        std::cout << "[EnglishApp] Created data directory" << std::endl;
    }
    
    std::string db_path = "data/english.db";
    std::cout << "[EnglishApp] Connecting to database: " << db_path << std::endl;
    
    if (!db.connect(db_path)) {
        std::cerr << "[EnglishApp] Failed to connect to database: " << db_path << std::endl;
        // Thử tạo database nếu không tồn tại
        std::cout << "[EnglishApp] Database file might not exist. Please run init_database.py first." << std::endl;
    } else {
        std::cout << "[EnglishApp] Database connected successfully." << std::endl;
    }
}

void EnglishApp::run() {
    Logger::info("EnglishApp started.");
    
    auto lessons = dao.loadLessons();

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
                std::cout << i++ << ". " << l->getTitle() << "\n";

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