# Bài tập sinh test

## Nội dung bài tập về nhà.
Nội dung bài tập về nhà được mô tả tại phần cuối trong [slide (bấm vào đây để mở slide)](DAA.pdf)

## Cách nộp
Gồm 5 file: `solution.cpp`, `validator.cpp`, `checker.cpp`, `generator.cpp`, `test.sh`.

## Ví dụ:
Dưới đây là ví dụ bài nộp cho bài toán được mô tả dưới đây

### Bài toán: **Truy vấn giá trị lớn nhất trên đoạn**
#### Mô tả

Cho một mảng gồm $n$ phần tử nguyên $a_1, a_2, \ldots, a_n$.

Bạn cần xử lý $q$ truy vấn.
Mỗi truy vấn gồm hai số nguyên ( l, r ) ((1 \le l \le r \le n)).
Với mỗi truy vấn, hãy in ra **giá trị lớn nhất của mảng ( a )** trong đoạn từ chỉ số ( l ) đến ( r ), tức là:

$$\text{max}(a_l, a_{l+1}, \ldots, a_r)$$

---

#### Input

* Dòng đầu tiên chứa hai số nguyên ( n ) và ( q ):
  số phần tử của mảng và số lượng truy vấn.
* Dòng thứ hai chứa ( n ) số nguyên ( a_1, a_2, \ldots, a_n ): các phần tử của mảng.
* Mỗi trong ( q ) dòng tiếp theo chứa hai số nguyên ( l ) và ( r ): biểu thị một truy vấn.

#### Output

* Với mỗi truy vấn, in ra **một số nguyên duy nhất trên một dòng**, là giá trị lớn nhất trong đoạn ([l, r]).

## Ràng buộc

Ràng buộc               
$1 \le n, q \le 100{,}000$ 
$-10^9 \le a_i \le 10^9$   
$1 \le l \le r \le n$   


## 🧮 Subtasks

| Subtask | Giới hạn             | Điểm |
| ------- | -------------------- | ---- |
| 1       | (n, q \le 1{,}000)   | 30   |
| 2       | (n, q \le 100{,}000) | 70   |

---

## 💡 Ví dụ

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

## 🧠 Giải thích

* Truy vấn 1: đoạn [1, 3] → max(2, 1, 5) = 5
* Truy vấn 2: đoạn [2, 5] → max(1, 5, 3, 4) = 5
* Truy vấn 3: đoạn [3, 3] → max(5) = 5
