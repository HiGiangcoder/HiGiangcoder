# 🧩 Hướng dẫn sử dụng Template làm bài tập về nhà

## 🧠 Giới thiệu

Template này cung cấp **bộ công cụ tự động hóa toàn diện** để làm bài tập về nhà hoặc kiểm thử thuật toán.  
Nó hỗ trợ:
- ✅ Sinh dữ liệu test tự động: *normal case, edge case, special case, stress case.*
- ✅ Kiểm tra hợp lệ input với `validator.cpp` (sử dụng `testlib.h`).
- ✅ So sánh output của bài làm với đáp án bằng `checker.cpp`.
- ✅ Chạy lời giải chuẩn trong `solution.cpp` (ví dụ: Sparse Table).
- ✅ Tự động compile, generate, validate và test trên **Windows / Linux / macOS**.

---

## 📁 Cấu trúc dự án

```

rmq_project/
├── brute.cpp           # Code brute-force để kiểm tra đối chiếu.
├── checker.cpp         # Custom checker (so sánh output).
├── gen_sub1.cpp        # Generator Subtask 1 (dữ liệu nhỏ).
├── gen_sub2.cpp        # Generator Subtask 2 (dữ liệu lớn).
├── solution.cpp        # Lời giải chính thức (ví dụ dùng Sparse Table).
├── validator.cpp       # Kiểm tra input (testlib.h).
│
├── testlib.h           # Thư viện testlib tiêu chuẩn.
│
├── gen.sh              # Sinh test (Linux Bash version).
├── check.sh            # Kiểm tra kết quả (Linux Bash version).
│
├── gen.ps1             # Phiên bản PowerShell cho Windows.
├── check.ps1           # Phiên bản PowerShell cho Windows.
│
├── gen.py              # (NEW) Phiên bản Python đa nền tảng của gen.sh.
├── check.py            # (NEW) Phiên bản Python đa nền tảng của check.sh.
│
├── README.md           # Hướng dẫn sử dụng.
│
├── tests/              # Chứa input + output gốc.
│   ├── test01/
│   │   ├── input.in
│   │   └── output.out
│   ├── test02/
│   │   ├── input.in
│   │   └── output.out
│   └── ...
│
└── outputs/            # Chứa output sinh ra từ bài làm của bạn.

````

---

## ⚙️ 1. Dành cho **Linux / macOS**

### 🔹 Sinh test

Sinh toàn bộ test bằng cách chạy:
```bash
bash gen.sh 42
````

Hoặc bằng Python (chạy được trên mọi nền tảng):

```bash
python3 gen.py 42
```

Nếu không truyền seed, mặc định là `1000`.
Ví dụ output:

```
[Info] Base seed = 42
[Compile] Building generators and solution...
[Generate] Subtask 1
[Gen] gen_sub1 type=1 seed=43 -> test01
[Gen] gen_sub1 type=2 seed=44 -> test02
...
```

---

### 🔹 Kiểm tra kết quả

Kiểm tra chương trình bằng:

```bash
bash check.sh solution.cpp
```

hoặc phiên bản Python:

```bash
python3 check.py solution.cpp
```

Script sẽ:

* Tự động compile `solution.cpp` và `checker.cpp`.
* Chạy chương trình với từng test.
* So sánh output bằng **checker**.
* Báo kết quả chi tiết từng test:

```
--- test01 ---
OK   | time=0.00s | mem=1.73MB

--- test02 ---
WA   | time=0.01s | mem=6.12MB

Summary: passed=48 failed=2 total=50
Outputs saved to ./outputs/
```

---

## 🪟 2. Dành cho **Windows (PowerShell)**

### Cho phép chạy script PowerShell:

```powershell
Set-ExecutionPolicy -Scope Process Bypass
```

### Sinh test:

```powershell
./gen.ps1 1234
```

hoặc:

```powershell
python gen.py 1234
```

### Kiểm tra kết quả:

```powershell
./check.ps1 solution.cpp
```

hoặc:

```powershell
python check.py solution.cpp
```

---

## 🧩 3. So sánh giữa các script

| Tên file    | Ngôn ngữ   | Nền tảng hỗ trợ   | Mô tả chức năng chính                        |
| ----------- | ---------- | ----------------- | -------------------------------------------- |
| `gen.sh`    | Bash       | Linux/macOS       | Sinh test nhanh bằng shell script            |
| `check.sh`  | Bash       | Linux/macOS       | Kiểm tra output bằng checker                 |
| `gen.ps1`   | PowerShell | Windows           | Sinh test trên Windows                       |
| `check.ps1` | PowerShell | Windows           | Kiểm tra bằng checker trên Windows           |
| `gen.py`    | Python     | Win/Linux/macOS ✅ | Sinh test đa nền tảng                        |
| `check.py`  | Python     | Win/Linux/macOS ✅ | Kiểm tra bằng checker, đo thời gian & bộ nhớ |

---

## 🚀 4. Tính năng nổi bật của `check.py`

* Phát hiện compiler tự động (`g++`, `clang++`, `cl.exe`).
* Chạy được trên **Windows, Linux, macOS**.
* Compile `solution.cpp` và `checker.cpp`.
* Đo thời gian và bộ nhớ (nếu OS hỗ trợ).
* So sánh bằng **checker** chứ không dùng `diff`.
* In kết quả chi tiết:

```
--- test05 ---
OK   | time=0.01s | mem=5.86MB
```

---

## 💡 Mẹo & Gợi ý

* Thử thuật toán khác chỉ cần đổi file truyền vào:

```bash
python3 check.py brute.cpp
```

* Copy template sang repo riêng hoặc GitHub Classroom.
* `check.py` thích hợp cho CI/CD kiểm thử tự động.

---

## ✅ Tổng kết

| Hệ điều hành | File dùng để sinh test | File dùng để kiểm tra    |
| ------------ | ---------------------- | ------------------------ |
| Linux/macOS  | `gen.sh` / `gen.py`    | `check.sh` / `check.py`  |
| Windows      | `gen.ps1` / `gen.py`   | `check.ps1` / `check.py` |

Tất cả đều tương thích chéo nền tảng.
Cần **Python 3.8+** hoặc compiler C++17 (`g++`, `clang++`, hoặc MSVC).
