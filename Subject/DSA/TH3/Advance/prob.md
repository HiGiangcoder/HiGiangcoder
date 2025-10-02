## Bài 1: Kiểm kê hàng hóa
**Mô tả**:  
Cửa hàng X bán nhiều loại hàng, mỗi loại có mã riêng. Trong quá trình bán hàng, nhân viên chỉ ghi lại mã hàng mà không ghi số lượng. Hãy xác định số lượng bán ra của từng mã hàng.

**Đầu vào**:  
- Dòng đầu tiên chứa số nguyên `N` (1 ≤ N ≤ 5 × 10⁴), là số lượng mã hàng được ghi lại.  
- `N` dòng tiếp theo, mỗi dòng chứa một mã hàng (tối đa 100 ký tự).

**Đầu ra**:  
- Với mỗi mã hàng, in ra mã hàng và số lượng bán được.  
- Sắp xếp kết quả theo số lượng giảm dần. Nếu số lượng bằng nhau, sắp xếp theo mã hàng tăng dần.

**Ví dụ**:  
Đầu vào:  
```
10  
123  
123444  
123444  
12  
1  
8  
1  
455  
455  
9  
```
Đầu ra:  
```
1 2  
455 2  
123444 2  
8 1  
9 1  
12 1  
123 1  
```

---

## Bài 2: Truy vấn tìm kiếm nhị phân
**Mô tả**:  
Cho một mảng số nguyên `A` và `Q` truy vấn. Với mỗi truy vấn:  
- Nếu `type = 1`, tìm vị trí đầu tiên xuất hiện của `y` trong `A`.  
- Nếu `type = 2`, tìm vị trí cuối cùng xuất hiện của `y` trong `A`.  
Nếu không tìm thấy, trả về `-1`.

**Đầu vào**:  
- Dòng đầu tiên chứa hai số nguyên `N` và `Q` (1 ≤ N ≤ 10⁵, 1 ≤ Q ≤ 5 × 10⁵).  
- Dòng thứ hai chứa `N` số nguyên `A[i]` (-10⁹ ≤ A[i] ≤ 10⁹).  
- `Q` dòng tiếp theo, mỗi dòng chứa một truy vấn dạng `type x y`.

**Đầu ra**:  
- Với mỗi truy vấn, in ra kết quả trên một dòng.

**Ví dụ**:  
Đầu vào:  
```
13 6  
9 10 12 7 -1 1 1 0 1 7 9 9 1  
type 1 3  
type 2 2  
type 1 1  
type 2 1  
type 1 9  
type 2 7  
```
Đầu ra:  
```
-1  
-1  
6  
13  
1  
10  
```

---

## Bài 3: Phát hiện virus trong tệp
**Mô tả**:  
Cho một tệp hình chữ nhật kích thước `N × M` chứa các ký tự thường. Xác định xem mỗi mẫu virus có xuất hiện trong tệp hay không (theo chiều ngang hoặc dọc).

**Đầu vào**:  
- Dòng đầu tiên chứa ba số nguyên `N`, `M`, và `Q` (1 ≤ N × M ≤ 10⁵, 1 ≤ Q ≤ 10⁴).  
- `N` dòng tiếp theo, mỗi dòng chứa `M` ký tự.  
- `Q` dòng tiếp theo, mỗi dòng chứa một mẫu virus (độ dài từ 2 đến 10).

**Đầu ra**:  
- Một dòng duy nhất gồm `Q` ký tự, ký tự thứ `i` là `1` nếu mẫu virus thứ `i` xuất hiện, ngược lại là `0`.

**Ví dụ**:  
Đầu vào:  
```
4 5 4  
attnt  
oboot  
campc  
ontes  
tt  
attn  
xyc  
aoco  
```
Đầu ra:  
```
1101  
```

---

## Bài 4: Sinh viên cuối hàng
**Mô tả**:  
Ban đầu, các sinh viên xếp hàng theo thứ tự mã số sinh viên từ `1` đến `n`. Khi một sinh viên được gọi, họ sẽ lên đầu hàng. Hãy xác định sinh viên cuối hàng sau mỗi lần gọi.

**Đầu vào**:  
- Dòng đầu tiên chứa hai số nguyên `n` và `m` (1 ≤ n, m ≤ 10⁵).  
- Dòng thứ hai chứa `m` số nguyên, là mã số sinh viên được gọi.

**Đầu ra**:  
- `m` số nguyên, là mã số sinh viên cuối hàng sau mỗi lần gọi.

**Ví dụ**:  
Đầu vào:  
```
5 2  
5 4  
```
Đầu ra:  
```
4 3  
```

---

## Bài 5: Thứ tự cuối cùng của sinh viên
**Mô tả**:  
Ban đầu, các sinh viên xếp hàng theo thứ tự mã số sinh viên từ `1` đến `n`. Khi một sinh viên được gọi, họ sẽ lên đầu hàng. Hãy xác định thứ tự cuối cùng của các sinh viên sau tất cả các lần gọi.

**Đầu vào**:  
- Dòng đầu tiên chứa hai số nguyên `n` và `m` (1 ≤ n, m ≤ 10⁵).  
- Dòng thứ hai chứa `m` số nguyên, là mã số sinh viên được gọi.

**Đầu ra**:  
- Một dòng duy nhất chứa thứ tự cuối cùng của các sinh viên.

**Ví dụ**:  
Đầu vào:  
```
5 2  
5 4  
```
Đầu ra:  
```
4 5 1 2 3  
```
