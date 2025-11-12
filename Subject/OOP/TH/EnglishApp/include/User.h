#pragma once
#include <string>
#include <map>
using namespace std;
/*
Chức năng: Lưu thông tin người học
*/

class User {
private:
    string username;
    string password;
    map<string, int> progress;
    int lessonCount;
public:
    explicit User(const string& user, const string& pass);
    bool authenticate(const string& pass) const;
    void completeLesson(const string& lesson);
    int getProgress(const string& lesson);
    string getName() const;
    int getLessonCount() const;
};
