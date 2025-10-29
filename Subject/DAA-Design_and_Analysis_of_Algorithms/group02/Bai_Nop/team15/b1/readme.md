# Hướng dẫn sử dụng Template làm bài tập về nhà

## Giới thiệu

Template này cung cấp một bộ công cụ toàn diện để hỗ trợ làm bài tập về nhà. Bạn sẽ sử dụng nó để:
- Sinh dữ liệu test tự động với nhiều dạng: normal case, edge case, special case và stress case (thông qua các file gen_sub1.cpp và gen_sub2.cpp).
- Kiểm tra tính hợp lệ của input với validator.cpp (dựa trên testlib.h).
- So sánh output của bài làm với đáp án mẫu bằng checker.cpp.
- Sinh lời giải mẫu chuẩn sử dụng thuật toán Sparse Table trong solution.cpp.
- Tự động hóa quy trình từ compile, generate, validate đến test với các script test.sh, gen.sh và check.sh.

## Cấu trúc dự án

```
rmq_project/
├── brute.cpp           # Code brute-force dùng để đối chiếu (so sánh kết quả).
├── checker.cpp         # So sánh output của bài làm với đáp án mẫu (custom checker).
├── gen_sub1.cpp        # Generator cho Subtask 1 (dữ liệu nhỏ: normal, edge, special, stress).
├── gen_sub2.cpp        # Generator cho Subtask 2 (dữ liệu lớn: normal, edge, special, stress).
├── solution.cpp        # Lời giải chính thức (ví dụ dùng Sparse Table).
├── validator.cpp       # Kiểm tra hợp lệ input (dựa trên testlib.h).
│
├── testlib.h           # Thư viện hỗ trợ sinh test, validator, checker (theo chuẩn testlib).
│
├── test.sh             # Script Linux tổng hợp: compile, generate, validate, run test.
├── gen.sh              # Sinh toàn bộ bộ test (Linux Bash version).
├── check.sh            # Kiểm tra kết quả chạy (Linux Bash version).
│
├── gen.ps1             # (NEW) Phiên bản PowerShell của gen.sh — chạy trên Windows.
├── check.ps1           # (NEW) Phiên bản PowerShell của check.sh — chạy trên Windows.
│
├── README.md           # Hướng dẫn sử dụng template (Linux + Windows).
│
├── tests/              # Thư mục chứa test inputs (input.in).
│   ├── test01/
│   │   ├── input.in
│   │   └── output.out
│   ├── test02/
│   │   ├── input.in
│   │   └── output.out
│   └── ...
│
└── outputs/            # Chứa các file output của solution.cpp khi chạy thử.

```

## Hướng dẫn sử dụng

### 1. Đối với linux

Chạy script `check.sh` để tự động:
- Biên dịch các file `.cpp`.
- chạy file `checker.cpp` để kiểm tra output của bài nộp với đáp án

```bash
bash check.sh brute.cpp
```

Kết quả sẽ hiển thị trạng thái của từng test, ví dụ:

```
--- test19 ---
OK   | time=0.00s | mem=1.59MB

--- test20 ---
OK   | time=0.00s | mem=1.59MB

--- test21 ---
TLE  | time=0.00s | mem=0.00MB

--- test22 ---
TLE  | time=0.00s | mem=0.00MB

--- test23 ---
TLE  | time=0.00s | mem=0.00MB

--- test24 ---
```

Sử dụng file `gen.sh` để tạo bộ test bao gồm 4 loại case:
- Normal case: dữ liệu ngẫu nhiên thông thường.
- Special case: dữ liệu có tính chất đặc biệt (ví dụ: toàn số giống nhau).
- Edge case: các truy vấn và dữ liệu biên (ví dụ: truy vấn bao phủ cả mảng).
- Stress case: dữ liệu kích thước lớn nhằm kiểm tra hiệu năng.

Ví dụ:
```bash
./gen.sh 42
```
Nếu không cung cấp base_seed, mặc định là 1000.
Output ví dụ:

```
[Info] Base seed = 42
[Compile] Building generators and solution...
[Compile] Done.
[Generate] Subtask 1
[Gen] gen_sub1 type=1 seed=43 -> test01
[Gen] gen_sub1 type=1 seed=44 -> test02
[Gen] gen_sub1 type=1 seed=45 -> test03
[Gen] gen_sub1 type=1 seed=46 -> test04
[Gen] gen_sub1 type=1 seed=47 -> test05
```

### 2. Đối với Windows

Hướng dẫn chạy trên Windows

Mở PowerShell trong thư mục có check.ps1, gen.ps1, code .cpp.

Cho phép chạy script (nếu chưa bật):
```
Set-ExecutionPolicy -Scope Process Bypass
```

Sinh test:
```
./gen.ps1 1234
```

Kiểm tra chương trình:
```
./check.ps1 solution.cpp
```

hoặc:
```
./check.ps1 solution.exe
```