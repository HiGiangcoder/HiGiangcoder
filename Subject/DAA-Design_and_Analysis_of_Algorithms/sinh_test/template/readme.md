Dưới đây là **file `README.md`** mô tả đầy đủ cấu trúc và nội dung của **bộ sinh test** cho bài toán *“Truy vấn giá trị lớn nhất trên đoạn” (Range Maximum Query)*.
File này có thể đặt cùng thư mục với `solution.cpp`, `generator.cpp`, `validator.cpp`, `checker.cpp`, `test.sh`.

---

# 🧾 README — Bộ sinh test cho bài toán “Truy vấn giá trị lớn nhất trên đoạn”

## 🧩 Tổng quan

Bộ công cụ này dùng để:

* Sinh dữ liệu test (`generator.cpp`)
* Kiểm tra hợp lệ input (`validator.cpp`)
* Kiểm tra đúng sai output (`checker.cpp`)
* Sinh lời giải mẫu (`solution.cpp`)
* Tự động sinh, kiểm thử, và xác thực toàn bộ pipeline (`test.sh`)

---

## 📁 Cấu trúc thư mục

```
rmq_project/
├── checker.cpp
├── generator.cpp
├── solution.cpp
├── validator.cpp
├── test.sh
├── README.md
├── tests/        # nơi chứa các file input (*.in)
└── outputs/      # nơi chứa các file output (*.out)
```

---

## ⚙️ Cách chạy

### 1️⃣ Biên dịch và sinh toàn bộ test

```bash
bash test.sh
```

Tập lệnh này sẽ:

* Biên dịch tất cả file `.cpp`
* Sinh các file test cho từng subtask
* Chạy validator kiểm tra input hợp lệ
* Chạy solution để tạo output mẫu
* Dùng checker để xác thực output

Kết quả sẽ in ra dòng:

```
Test 1_1 OK
Test 1_2 OK
Test 1_3 OK
Test 2_1 OK
Test 2_2 OK
Test 2_3 OK
```

---

## 🧮 Mô tả từng thành phần

### 🧠 1. `generator.cpp`

Sinh dữ liệu ngẫu nhiên cho từng **subtask**.
Nhận tham số dòng lệnh (1 hoặc 2) để xác định mức độ test:

| Subtask | Quy mô          | Mô tả đặc trưng                                  |
| ------- | --------------- | ------------------------------------------------ |
| **1**   | `n, q ≤ 1000`   | Dữ liệu nhỏ, dùng để test tính đúng đắn cơ bản   |
| **2**   | `n, q ≤ 100000` | Dữ liệu lớn, dùng để test hiệu năng và độ tối ưu |

**Nguyên tắc sinh dữ liệu:**

* Mảng `a` gồm các phần tử ngẫu nhiên trong khoảng `[-1e9, 1e9]`.
* Các truy vấn `(l, r)` được sinh ngẫu nhiên, đảm bảo `l ≤ r`.
* Sử dụng `testlib.h` để sinh dữ liệu với seed ngẫu nhiên, đảm bảo đa dạng test.

Ví dụ lệnh sinh test:

```bash
./generator 1 > tests/1_1.in
```

---

### ✅ 2. `validator.cpp`

Dùng `testlib.h` để **kiểm tra tính hợp lệ của input**:

* `1 ≤ n, q ≤ 100000`
* `-10^9 ≤ a_i ≤ 10^9`
* `1 ≤ l ≤ r ≤ n`
* Định dạng đúng: không dư/kém dòng, không sai cách xuống dòng.

Nếu input sai, chương trình in ra lỗi cụ thể.

Ví dụ:

```bash
./validator < tests/1_1.in
```

---

### 🔍 3. `checker.cpp`

So sánh **output của thí sinh** với **đáp án đúng** (file `.out` mẫu).
Nếu sai, in ra truy vấn sai, giá trị mong đợi và giá trị thực tế.

* Trả về `_ok` nếu toàn bộ đúng
* Trả về `_wa` nếu có truy vấn sai
* Trả về `_pe` nếu định dạng sai (extra tokens)

Ví dụ:

```bash
./checker tests/1_1.in outputs/1_1.out outputs/1_1.out
```

---

### 💡 4. `solution.cpp`

Lời giải chính thức dùng để tạo output chuẩn (đáp án mẫu).
Sử dụng **Sparse Table** để xử lý truy vấn (O(1)) mỗi lần.
Thời gian xây dựng: (O(n \log n)).

---

### 🔧 5. `test.sh`

Tự động hóa toàn bộ quá trình:

1. Biên dịch các chương trình.
2. Sinh dữ liệu cho từng subtask.
3. Chạy validator kiểm tra input.
4. Chạy solution tạo output.
5. Dùng checker để kiểm tra kết quả.

Kết quả cuối cùng sẽ thông báo `OK` hoặc lỗi.

---

## 🧠 Hướng mở rộng

Bạn có thể chỉnh `generator.cpp` để sinh thêm các kiểu test đặc biệt:

| Loại test             | Mô tả                                           |
| --------------------- | ----------------------------------------------- |
| **Sorted Increasing** | Mảng `a` tăng dần                               |
| **Sorted Decreasing** | Mảng `a` giảm dần                               |
| **All Equal**         | Mảng toàn số giống nhau                         |
| **Stress**            | `n, q` đạt cực đại, truy vấn bao phủ toàn mảng  |
| **Random Edge**       | Truy vấn sát biên, ví dụ `(1, n)` hoặc `(n, n)` |

Chỉ cần thay đổi seed hoặc quy tắc sinh là có thể mở rộng bộ test phong phú.

---

## 🧾 Ghi chú

* Mọi chương trình cần **`testlib.h`** (đặt cùng thư mục hoặc include path).
* Có thể dùng thêm `--seed` khi chạy generator để đảm bảo tái lập kết quả.
* Mọi output sinh ra đều lưu trong `outputs/`.

---

Bạn có muốn mình bổ sung phần **mẫu lệnh chạy test từng bước thủ công** (giúp sinh viên thao tác trên terminal mà không cần script `test.sh`) không?
Nếu có, mình sẽ thêm phần đó vào cuối README, hướng dẫn chi tiết từng dòng lệnh `g++`, `./generator`, `./solution`, `./checker` theo thứ tự chuẩn của Codeforces/Polygon.
