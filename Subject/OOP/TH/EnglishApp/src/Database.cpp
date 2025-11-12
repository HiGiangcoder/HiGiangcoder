#include "Database.h"
#include <iostream>

// Default constructor: chưa mở DB
Database::Database() : db(nullptr), filename() {}

// Constructor với đường dẫn: cố gắng mở ngay
Database::Database(const std::string& file) : db(nullptr), filename(file) {
    if (!connect(file)) {
        std::cerr << "[Database] Warning: failed to open DB in ctor: " << file << std::endl;
    }
}

// Destructor: đóng nếu đang mở
Database::~Database() {
    close();
}

// Mở kết nối (hoặc chuyển sang DB mới)
bool Database::connect(const std::string& path) {
    // Nếu đang mở DB khác, đóng trước
    if (db) {
        sqlite3_close(db);
        db = nullptr;
    }

    int rc = sqlite3_open(path.c_str(), &db);
    if (rc != SQLITE_OK) {
        std::cerr << "[Database] Cannot open DB: " << sqlite3_errmsg(db) << std::endl;
        if (db) { sqlite3_close(db); db = nullptr; }
        return false;
    }
    filename = path;
    std::cout << "[Database] Connected to " << path << std::endl;
    return true;
}

// Thực thi câu lệnh không trả kết quả
bool Database::execute(const std::string& sql) {
    if (!db) {
        std::cerr << "[Database] execute: DB not opened\n";
        return false;
    }
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "[Database] SQL error: " << (errMsg ? errMsg : "") << std::endl;
        if (errMsg) sqlite3_free(errMsg);
        return false;
    }
    return true;
}

// Truy vấn và trả về bảng kết quả
std::vector<std::vector<std::string>> Database::query(const std::string& sql) {
    std::vector<std::vector<std::string>> results;
    if (!db) {
        std::cerr << "[Database] query: DB not opened\n";
        return results;
    }

    sqlite3_stmt* stmt = nullptr;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "[Database] prepare failed: " << sqlite3_errmsg(db) << std::endl;
        return results;
    }

    int cols = sqlite3_column_count(stmt);
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        std::vector<std::string> row;
        for (int i = 0; i < cols; ++i) {
            const unsigned char* text = sqlite3_column_text(stmt, i);
            row.emplace_back(text ? reinterpret_cast<const char*>(text) : "");
        }
        results.push_back(std::move(row));
    }

    if (rc != SQLITE_DONE) {
        std::cerr << "[Database] step error: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
    return results;
}

// Đóng kết nối
void Database::close() {
    if (db) {
        sqlite3_close(db);
        db = nullptr;
        std::cout << "[Database] Connection closed." << std::endl;
    }
}
