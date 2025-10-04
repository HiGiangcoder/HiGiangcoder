# Bài tập sinh test

## Nội dung bài tập về nhà.
Nội dung bài tập về nhà được mô tả tại phần cuối trong [slide (bấm vào đây để mở slide)](DAA.pdf) hoặc được cung cấp ngay dưới đây:


### Bài 1: Tổng dãy số
Cho mảng n số nguyên, tính tổng tất cả phần tử. 

- Input: $n$ và dãy $a_1, a_2, \dots, a_n$. 
- Output: tổng $n$ phần tử.

Giới hạn $1 ≤ n ≤ 100 000, −10^5 ≤ a_i ≤ 10^5$. 

- Subtask 1: $n \le 1000$
- Subtask 2: $n \le 100 000$

**Input ví dụ 1**

```
5
1 2 3 4 5
```

**Output**

```
15
```

**Input ví dụ 2**

```
3
-10 20 -5
```

**Output**

```
5
```

### Bài 2: Đồ thị

Đồ thị có hướng $n$ đỉnh $m$ cạnh trọng số dương, tìm độ dài đường đi ngắn nhất từ $1$ đến $n$. 

- Input: $n m$ và $m$ dòng $u_i v_i w_i$. 
- Output: độ dài hoặc −1. 

Giới hạn: $2 ≤ n ≤ 2000, m ≤ 5000, 1 ≤ w_i ≤ 10^9$

- Subtask 1: $n≤200$, $m≤1000$; 
- Subtask 2: Không còn giới hạn gì thêm.


**Input ví dụ 1**

```
4 4
1 2 1
2 3 2
3 4 3
1 4 10
```

**Output**

```
6
```

*(Đường đi ngắn nhất từ 1 → 2 → 3 → 4, tổng trọng số = 1+2+3=6)*

**Input ví dụ 2**

```
3 1
2 3 5
```

**Output**

```
-1
```

*(Không có đường đi từ 1 đến 3)*

---

### Bài 3: Đường đi Hamilton:
Đồ thị vô hướng $n$ đỉnh $m$ cạnh, in một đường đi Hamilton (qua mỗi đỉnh đúng 1 lần) hoặc −1. 

- Input: $n$ $m$ và $m$ cạnh $u_i v_i$ (Đảm bảo rằng không có 2 cạnh nào trùng nhau). 
- Output: dãy $n$ đỉnh hoặc −1. 

Giới hạn $1 ≤ n ≤ 12, m ≤ n(n−1)/2$


**Input ví dụ 1**

```
4 5
1 2
1 3
2 3
2 4
3 4
```

**Output**

```
1 2 3 4
```

*(Một đường đi Hamilton: đi qua tất cả đỉnh đúng 1 lần)*

**Input ví dụ 2**

```
3 1
1 2
```

**Output**

```
-1
```

*(Không tồn tại đường đi Hamilton)*


## Cách nộp
Yêu cầu bài nộp phải dựa trên template đã được cung cấp ở phần [ví dụ](#-ví-dụ).

Bài nộp dựa trên yêu cầu viết `solution.cpp`, 1 hoặc nhiều file `gen.cpp`, `checker.cpp`, `validator.cpp`, đồng thời phải tinh chỉnh lại `gen.sh` (`check.sh` có thể không cần chỉnh sửa vì không cần thiết).

Bài nộp phải bao gồm các file dựa trên template **và không bao gồm bộ test** sao cho khi chạy `bash gen.sh <STT của nhóm bạn>` sẽ tạo ra một folder chứa các test.

Số lượng test sẽ tùy do bạn quyết định nhưng sẽ có **tối đa là 100 test**.

## Cách chấm điểm
Điểm sẽ dựa trên độ tốt của test mà bạn sinh ra, nếu test của bạn sinh ra bị thiếu trường hợp bình thường, trường hợp đặc biệt, trường hợp biên, trường hợp cực đại, bạn sẽ bị trừ điểm.

Vì mình sẽ sử dụng cách chấm điểm bằng cách sử dụng một code nào đó bị sai tương ứng với các trường hợp đã nếu trên. Nếu bộ test mà bạn tạo ra bắt được bug trong code đó, bạn sẽ được tính điểm của trường hợp đó. Do đó, hãy viết checker một cách cẩn thận.

**Cách tính điểm**

Gọi:
- $n = \{0, 1\}$. Nếu có trường hợp bình thường $n = 1$ và ngược lại.
- $s = \{0, 1\}$. Nếu có trường hợp cực đại $s = 1$ và ngược lại.
- $p$ là tổng số lượng trường hợp đặc biệt và trường hợp biên thực tế của bài toán, $q$ là tổng số lượng trường hợp đặc biệt và trường hợp biên của bộ test bạn đã cung cấp.  

Điểm của bạn sẽ được tính dựa trên công thức:
$$score = f(n, s, p, q) = 5 \times n + 2 \times s + 3 \times \frac{q+1}{p+1}$$

Trong trường hợp bài có nhiều subtask, gọi $k$ là số lượng subtask, điểm của bạn sẽ được tính dựa trên công thức:
$$score = \frac1k \sum_{i=1}^{k} f(n_i, s_i, p_i, q_i)$$

*Chúc các bạn làm bài tốt!*

## Ví dụ:
Dưới đây là ví dụ bài nộp cho bài toán được mô tả dưới đây

[Mẫu bài nộp](template/readme.md)

### **Bài toán ví dụ:** **Truy vấn giá trị lớn nhất trên đoạn**
#### Mô tả

Cho một mảng gồm $n$ phần tử nguyên $a_1, a_2, \ldots, a_n$.

Bạn cần xử lý $q$ truy vấn.
Mỗi truy vấn gồm hai số nguyên ( l, r ) ((1 \le l \le r \le n)).
Với mỗi truy vấn, hãy in ra **giá trị lớn nhất của mảng ( a )** trong đoạn từ chỉ số ( l ) đến ( r ), tức là:

$$\text{max}(a_l, a_{l+1}, \ldots, a_r)$$

---

#### Input

* Dòng đầu tiên chứa hai số nguyên $n$ và $q$:
  số phần tử của mảng và số lượng truy vấn.
* Dòng thứ hai chứa $n$ số nguyên $a_1, a_2, \ldots, a_n$: các phần tử của mảng.
* Mỗi trong $q$ dòng tiếp theo chứa hai số nguyên $l$ và $r$: biểu thị một truy vấn.

#### Output

* Với mỗi truy vấn, in ra **một số nguyên duy nhất trên một dòng**, là giá trị lớn nhất trong đoạn $[l, r]$.

## Ràng buộc

Ràng buộc               
$1 \le n, q \le 100{,}000$ 
$-10^9 \le a_i \le 10^9$   
$1 \le l \le r \le n$   


## Subtasks

| Subtask | Giới hạn             | Điểm |
| ------- | -------------------- | ---- |
| 1       | $n, q \le 1{,}000$   | 30   |
| 2       | $n, q \le 100{,}000$ | 70   |

---

## Ví dụ

### **Input**

```
5 3
2 1 5 3 4
1 3
2 5
3 3
```

### **Output**

```
5
5
5
```

---

## Giải thích

* Truy vấn 1: đoạn [1, 3] → max(2, 1, 5) = 5
* Truy vấn 2: đoạn [2, 5] → max(1, 5, 3, 4) = 5
* Truy vấn 3: đoạn [3, 3] → max(5) = 5
