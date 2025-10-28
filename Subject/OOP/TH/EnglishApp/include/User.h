#pragma once
#include <string>
#include <map>
using namespace std;

class User {
private:
    string username;
    string password;
    map<string, int> progress;
public:
    explicit User(const string& user, const string& pass);
    bool authenticate(const string& pass) const;
    void completeLesson(const string& lesson);
    int getProgress(const string& lesson);
}

User::User(const string& user, const string& pass) : username(user), password(pass) {}

bool User::authenticate(const string& pass) const {
    return password == pass;
}
void User::completeLesson(const string& lesson) {
    progress[lesson]++;
}

int User::getProgress(const string& lesson) {
    return progress[lesson];
}