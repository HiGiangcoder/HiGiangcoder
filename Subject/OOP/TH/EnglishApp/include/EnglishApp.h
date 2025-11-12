#pragma once
#include "DatabaseDAO.h"
#include "User.h"
#include "LessonFactory.h"
#include "Logger.h"

/*
**Chức năng:**

- **Trái tim của ứng dụng** — nơi điều phối toàn bộ.

**Nhiệm vụ khi code:**

- Quản lý Database, DAO, Logger, User, danh sách Lessons.
- Giao diện CLI chính (`runCLI()`), hiển thị menu, gọi `Lesson.start()`.
- Load bài học qua `LessonFactory`.

**Cấu trúc logic:**

1. Load dữ liệu từ `DatabaseDAO`.
2. Hiển thị menu chính.
3. Gọi `Lesson.start()`.
4. Ghi tiến độ vào DB.
*/

class EnglishApp {
private:
    Database db;
    DatabaseDAO dao;
    User user;
public:
    EnglishApp();
    std::vector<Lesson*> getLessons();
    void run();
    User& getUser();
};