#pragma once
#include <string>
#include <vector>
#include <sqlite3.h>

class Database {
private:
    sqlite3* db;              // member, không phải global
    std::string filename;

public:
    Database();                            // default ctor
    explicit Database(const std::string& file); // ctor mở DB (tùy chọn)
    ~Database();                           // dtor đóng DB

    bool connect(const std::string& path); // mở (hoặc đổi) DB
    bool execute(const std::string& sql);  // INSERT/UPDATE/DELETE
    std::vector<std::vector<std::string>> query(const std::string& sql); // SELECT
    void close();                          // đóng kết nối
};
