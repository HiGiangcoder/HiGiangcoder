/*
Mục tiêu: Quản lý kết nối SQLite duy nhất trong toàn chương trình
OOP áp dụng: 
- Encapsulation: giấu biến db và filename bên trong lớp Database
- Singleton Pattern: đảm bảo chỉ có một thể hiện của Database trong toàn chương trình
- RAII: quản lý tài nguyên kết nối CSDL thông qua các phương thức connect và close
*/
#pragma once
#include <string>
#include <vector>
#include <sqlite3.h>

class Database {
private:
    sqlite3* db;
    std::string filename;
    Database(const std::string& file);
public:
    
    bool connect(const std::string& path);
    std::vector<std::vector<std::string>> query(const std::string& sql);
    void close();
};

/*
connect: Ket noi den CSDL SQLite
*/
bool Database::connect(const std::string& path) {
    if (sqlite3_open(path.c_str(), &db) != SQLITE_OK) {
        return false;
    }
    return true;
}

/*
query: Thuc hien cau lenh SQL va tra ve 1 bang ket qua
- sql: cau lenh SQL can thuc hien
- tra ve: bang ket qua duoi dang vector<vector<string>>
*/
std::vector<std::vector<std::string>> Database::query(const std::string& sql) {
    std::vector<std::vector<std::string>> results;
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return results;
    }

    int cols = sqlite3_column_count(stmt);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::vector<std::string> row;
        for (int i = 0; i < cols; i++) {
            const char* text = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));
            row.push_back(text ? text : "");
        }
        results.push_back(row);
    }
    sqlite3_finalize(stmt);
    return results;
}

/*
close: Dong ket noi den CSDL
*/
void Database::close() {
    sqlite3_close(db);
}