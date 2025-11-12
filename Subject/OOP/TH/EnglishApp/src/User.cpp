#include "User.h"
#include <iostream>


User::User(const string& user, const string& pass) 
    : username(user), password(pass) {
    this->lessonCount = 0;
}

// Xác nhận mật khẩu
bool User::authenticate(const string& pass) const {
    return password == pass;
}

// Tăng số lần hoàn thành bài học đó lên 1
void User::completeLesson(const string& lesson) {
    this->progress[lesson]++;
    this->lessonCount ++;
    std::cout << "[User] Completed: " << lesson << std::endl;
}

// Lấy kết quả số lần hoàn thành bài học đó
int User::getProgress(const string& lesson) {
    return progress[lesson];
}

std::string User::getName() const {
    return this->username;
}

// Getter cho lessonCount
int User::getLessonCount() const {
    return this->lessonCount;
}