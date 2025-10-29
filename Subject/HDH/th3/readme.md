# 🧩 **Câu 1. Mối quan hệ cha–con giữa các tiến trình**

---

### **a. Vẽ cây quan hệ parent–child**

Bảng tiến trình:

| UID | PID | PPID | COMMAND      |
| --- | --- | ---- | ------------ |
| 88  | 86  | 1    | WindowServer |
| 501 | 281 | 86   | iTunes       |
| 501 | 282 | 86   | Terminal     |
| 0   | 287 | 282  | login        |
| 501 | 293 | 287  | -bash        |
| 501 | 461 | 293  | firefox-bin  |
| 501 | 531 | 86   | Safari       |
| 501 | 726 | 86   | Mail         |
| 501 | 751 | 293  | Aquamacs     |

→ Ta xây dựng cây cha–con dựa theo cột **PPID** (Parent PID).

```
(1) launchd
 └── (86) WindowServer
      ├── (281) iTunes
      ├── (282) Terminal
      │    └── (287) login
      │         └── (293) -bash
      │              ├── (461) firefox-bin
      │              └── (751) Aquamacs
      ├── (531) Safari
      └── (726) Mail
```

👉 **Giải thích:**

* `WindowServer (86)` là con trực tiếp của `launchd (1)`.
* `Terminal (282)` cũng do `WindowServer` sinh ra, trong đó `login (287)` là con của `Terminal`, và `-bash (293)` là con của `login`.
* Từ `bash` lại sinh thêm `firefox-bin` và `Aquamacs`.

---

### **b. Cách dùng lệnh `ps` để tìm tiến trình cha (parent process)**

**Cú pháp:**

```bash
ps -o ppid= -p <PID>
```

* `-p <PID>`: chỉ định tiến trình cần tra.
* `-o ppid=`: chỉ hiển thị **Parent PID**.

👉 **Ví dụ:**

```bash
ps -o ppid= -p 293
```

➡ Kết quả: `287`
→ nghĩa là tiến trình có PID 293 (bash) có cha là PID 287 (login).

---

### **c. Dùng `pstree`**

**Cài đặt (nếu chưa có):**

```bash
sudo apt install pstree
```

**Cách dùng:**

```bash
pstree -p
```

→ Hiển thị **toàn bộ cây tiến trình** kèm PID.

Hoặc để xem **cụ thể tiến trình cha của một PID:**

```bash
pstree -p <PID>
```

Ví dụ:

```bash
pstree -p 293
```

➡ Kết quả hiển thị chuỗi cha–con dẫn đến tiến trình đó, ví dụ:

```
systemd(1)─WindowServer(86)─Terminal(282)─login(287)─bash(293)
```

---

# 🧩 **Câu 2. Phân tích chương trình fork**

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int num_coconuts = 17;
    pid = fork();
    if (pid == 0) {
        num_coconuts = 42;
        exit(0);
    } else {
        wait(NULL); // chờ tiến trình con kết thúc
    }
    printf("I see %d coconuts!\n", num_coconuts);
    exit(0);
}
```

---

### ✅ **Kết quả in ra:**

```
I see 17 coconuts!
```

---

### 🧠 **Giải thích:**

1. **`fork()`** tạo ra **một tiến trình con**, là **bản sao của tiến trình cha**.

   * Tức là **biến `num_coconuts` được sao chép riêng** cho tiến trình con.
2. Trong **tiến trình con** (`pid == 0`):

   * Gán `num_coconuts = 42;`
   * Sau đó `exit(0)` → kết thúc.
3. Trong **tiến trình cha**:

   * `wait(NULL)` đợi tiến trình con kết thúc.
   * Biến `num_coconuts` **vẫn giữ giá trị 17**, vì vùng nhớ **không chia sẻ** giữa 2 tiến trình.
4. → Khi in ra, kết quả là **17**.

---

# 🧩 **Câu 3. POSIX Thread Attributes (`pthread_attr_*`)**

---

## **1️⃣ Các hàm thay đổi thuộc tính của pthread**

| Hàm                                                    | Mô tả                                                |
| ------------------------------------------------------ | ---------------------------------------------------- |
| `pthread_attr_init(pthread_attr_t *attr)`              | Khởi tạo cấu trúc thuộc tính                         |
| `pthread_attr_destroy(pthread_attr_t *attr)`           | Giải phóng thuộc tính                                |
| `pthread_attr_setdetachstate()` / `getdetachstate()`   | Đặt hoặc lấy trạng thái tách rời (joinable/detached) |
| `pthread_attr_setstacksize()` / `getstacksize()`       | Đặt/lấy kích thước stack cho thread                  |
| `pthread_attr_setstackaddr()` / `getstackaddr()`       | Đặt/lấy địa chỉ stack (ít dùng)                      |
| `pthread_attr_setschedpolicy()` / `getschedpolicy()`   | Đặt/lấy chính sách lập lịch (SCHED_OTHER, FIFO, RR)  |
| `pthread_attr_setschedparam()` / `getschedparam()`     | Đặt/lấy tham số lập lịch (priority, v.v.)            |
| `pthread_attr_setinheritsched()` / `getinheritsched()` | Quy định thread có kế thừa policy của cha không      |
| `pthread_attr_setscope()` / `getscope()`               | Phạm vi cạnh tranh CPU (system / process)            |

---

## **2️⃣ Ví dụ minh họa: detached thread**

```c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void* worker(void* arg) {
    printf("Thread running...\n");
    sleep(2);
    printf("Thread finished.\n");
    return NULL;
}

int main() {
    pthread_t tid;
    pthread_attr_t attr;

    pthread_attr_init(&attr); // khởi tạo
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    pthread_create(&tid, &attr, worker, NULL);
    pthread_attr_destroy(&attr);

    printf("Main thread done.\n");
    pthread_exit(NULL); // không cần join vì thread detached
}
```

### ✅ Giải thích:

* Thread được tạo ở trạng thái **detached**, tức là tự hủy khi kết thúc.
* Không cần gọi `pthread_join`.
* Thường dùng cho các tác vụ nền (background).

---

# 🧩 **Câu 4. Xử lý tín hiệu (Signal handling)**

---

### **Yêu cầu:**

1. In: `"Welcome to IT007, I am <your_ID>!"`
2. Mở file `abcd.txt` bằng **vim**.
3. Khi nhấn `Ctrl + C`, **thoát vim** và in `"You are pressed CTRL+C! Goodbye!"`

---

### **Code minh họa:**

```c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig) {
    printf("\nYou are pressed CTRL+C! Goodbye!\n");
    exit(0);
}

int main() {
    printf("Welcome to IT007, I am 22520001!\n");

    // Bắt tín hiệu Ctrl+C (SIGINT)
    signal(SIGINT, handler);

    // Mở vim
    execlp("vim", "vim", "abcd.txt", NULL);

    // Nếu execlp lỗi
    perror("execlp failed");
    return 1;
}
```

### ✅ **Giải thích:**

* `signal(SIGINT, handler);` → Khi người dùng nhấn Ctrl+C, hệ thống gửi tín hiệu SIGINT đến process.
* `handler()` sẽ được gọi → in thông báo và thoát.
* `execlp("vim", ...)` → thay thế tiến trình hiện tại bằng chương trình `vim`.
* Khi người dùng nhấn Ctrl+C trong vim → tín hiệu vẫn truyền tới chương trình và được bắt.

---

## 🎯 Tổng kết nhanh

| Câu | Chủ đề             | Kiến thức chính                                 |
| --- | ------------------ | ----------------------------------------------- |
| 1   | Quan hệ tiến trình | PPID, ps, pstree                                |
| 2   | fork()             | Copy vùng nhớ riêng biệt giữa process cha – con |
| 3   | pthread_attr_*     | Cấu hình thuộc tính của thread                  |
| 4   | Signal + exec      | Bắt tín hiệu SIGINT và thay thế tiến trình      |

