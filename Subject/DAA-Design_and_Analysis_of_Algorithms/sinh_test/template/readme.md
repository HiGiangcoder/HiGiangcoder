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
├── brute.cpp        // Code giải tham khảo dạng brute (có thể dùng để đối chiếu).
├── checker.cpp      // So sánh output của bài làm với đáp án mẫu.
├── gen_sub1.cpp     // Sinh dữ liệu test cho Subtask 1 (n, q nhỏ) bao gồm: normal, special, edge, và stress cases.
├── gen_sub2.cpp     // Sinh dữ liệu test cho Subtask 2 (n, q lớn) bao gồm: normal, special, edge, và stress cases.
├── solution.cpp     // Lời giải mẫu sử dụng thuật toán Sparse Table (O(n log n) xây dựng, O(1) mỗi truy vấn).
├── validator.cpp    // Kiểm tra tính hợp lệ của input (định dạng và giá trị) dựa trên testlib.h.
├── test.sh          // Tự động hóa compile, sinh test, validate, và chạy test.
├── gen.sh           // Sinh bộ test, đảm bảo bao gồm các loại: normal case, edge case, special case, stress case.
├── check.sh         // Chạy kiểm tra và so sánh kết quả chạy của lời giải với đáp án mẫu.
├── testlib.h        // Thư viện hỗ trợ kiểm tra, sinh dữ liệu và các công cụ liên quan.
├── README.md        // Hướng dẫn sử dụng template và mô tả dự án.
├── tests/           // Chứa các file input (*.in) được sinh ra.
└── outputs/         // Chứa các file output (*.out) được tạo bởi solution.cpp.
```

## Hướng dẫn sử dụng

### 1. Toàn bộ pipeline

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

### 2. Sinh dữ liệu test riêng

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
