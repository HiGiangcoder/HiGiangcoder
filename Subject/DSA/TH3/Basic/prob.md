### Bài 1: Kiểm tra tính hợp lệ của chuỗi Latex
Kiểm tra chuỗi Latex có hợp lệ không bằng cách đảm bảo các dấu ngoặc `{}`, `[]`, `()` được đóng mở đúng thứ tự.

**Đầu vào**:  
Chuỗi `s` (1 ≤ |s| ≤ 10⁵).

**Đầu ra**:  
`1` nếu chuỗi hợp lệ, ngược lại `0`.

**Ví dụ**:
| Đầu vào                        | Đầu ra |
|--------------------------------|--------|
| `p_{\frac{5}{2}}^{-\frac{1}{2}}` | `1`    |
| `\intd^4}p`                    | `0`    |

---

### Bài 2: Chèn vào danh sách liên kết đơn đã sắp xếp
Chèn giá trị `x` vào danh sách liên kết đơn đã sắp xếp sao cho danh sách vẫn giữ thứ tự tăng dần.

**Đầu vào**:  
- Số nguyên `N` (0 ≤ N ≤ 10⁵), số phần tử trong danh sách.  
- `N` số nguyên của danh sách liên kết.  
- Số nguyên `x`, giá trị cần chèn.

**Đầu ra**:  
Danh sách liên kết sau khi chèn, cách nhau bởi dấu cách.

**Ví dụ**:
| Đầu vào          | Đầu ra       |
|------------------|--------------|
| `5\n1\n3\n4\n6\n7\n5` | `1 3 4 5 6 7` |

---

### Bài 3: Nhập và tính giá trị đa thức
Nhập một đa thức, hiển thị dạng chuẩn và tính giá trị tại `x`.

**Đầu vào**:  
- Số nguyên `n` (0 ≤ n ≤ 100), số đơn thức.  
- `n` cặp số: hệ số (số thực) và số mũ (nguyên không âm).  
- Số thực `x`.

**Đầu ra**:  
- Đa thức dạng chuẩn.  
- Giá trị của đa thức tại `x`, làm tròn 2 chữ số thập phân.

**Ví dụ**:
| Đầu vào                          | Đầu ra                                                                 |
|----------------------------------|-----------------------------------------------------------------------|
| `7\n2 15\n-1 10\n0 8\n1 5\n6 2\n-8.5 1\n-10.52 0\n2` | `Da thuc vua nhap la: 2x^15-x^10+x^5+6x^2-8.5x-10.52\nVoi x=2, gia tri da thuc la: 64540.48` |

---

### Bài 4: Đảo ngược danh sách liên kết
Đảo ngược danh sách liên kết đơn và in kết quả.

**Đầu vào**:  
- Số nguyên `N`, số phần tử trong danh sách.  
- `N` số nguyên của danh sách liên kết.

**Đầu ra**:  
Danh sách liên kết sau khi đảo ngược, cách nhau bởi dấu cách.

**Ví dụ**:
| Đầu vào          | Đầu ra       |
|------------------|--------------|
| `4\n2\n4\n5\n7` | `7 5 4 2`   |

---

### Bài 5: Chuyển đổi thập phân sang nhị phân
Chuyển đổi số nguyên từ hệ thập phân sang hệ nhị phân.

**Đầu vào**:  
Số nguyên `x` (1 ≤ x ≤ 10⁵).

**Đầu ra**:  
Chuỗi nhị phân tương ứng.

**Ví dụ**:
| Đầu vào | Đầu ra  |
|---------|---------|
| `10`    | `1010`  |
| `1009`  | `1111110001` |

---

### Bài 6: Trộn hai danh sách liên kết đã sắp xếp
Trộn hai danh sách liên kết đơn đã sắp xếp thành một danh sách cũng được sắp xếp.

**Đầu vào**:  
- Số nguyên `T` (T < 10), số bộ test.  
- Mỗi bộ test gồm:  
  - Hai số nguyên `n` và `m`, kích thước của hai danh sách.  
  - `n` số nguyên của danh sách thứ nhất.  
  - `m` số nguyên của danh sách thứ hai.

**Đầu ra**:  
Danh sách liên kết sau khi trộn.

**Ví dụ**:
| Đầu vào                          | Đầu ra                     |
|----------------------------------|----------------------------|
| `1\n5 4\n1 2 5 7 10\n2 4 9 11` | `1 2 2 4 5 7 9 10 11`     |

---

### Bài 7: Duyệt cây theo thứ tự NLR (Đệ quy)
Duyệt cây nhị phân theo thứ tự NLR (Node-Left-Right) bằng đệ quy.

**Đầu vào**:  
- Số nguyên `N`, số nút trong cây.  
- `N` số nguyên là giá trị các nút.

**Đầu ra**:  
Kết quả duyệt cây theo thứ tự NLR.

**Ví dụ**:
| Đầu vào          | Đầu ra       |
|------------------|--------------|
| `6\n1 2 5 3 4 6` | `1 2 5 3 4 6` |

---

### Bài 8: Duyệt cây theo thứ tự NLR (Không đệ quy)
Duyệt cây nhị phân theo thứ tự NLR (Node-Left-Right) không dùng đệ quy.

**Đầu vào**:  
Giống bài 7.

**Đầu ra**:  
Giống bài 7.

---

### Bài 9: Tìm nút chung của hai danh sách liên kết
Tìm nút chung đầu tiên của hai danh sách liên kết đơn.

**Đầu vào**:  
- Hai danh sách liên kết.  
- Danh sách thứ ba chứa các nút chung.

**Đầu ra**:  
Giá trị của nút chung đầu tiên, hoặc `NA` nếu không có.

**Ví dụ**:
| Đầu vào                          | Đầu ra |
|----------------------------------|--------|
| `3\n1 2 3\n2\n4 5\n2\n6 7`       | `6`    |

---

### Bài 10: Nút tổ tiên thấp nhất trong cây BST
Tìm nút tổ tiên thấp nhất của hai nút trong cây nhị phân tìm kiếm (BST).

**Đầu vào**:  
- Số nguyên `N`, số nút trong cây.  
- `N` số nguyên là giá trị các nút.  
- Hai số nguyên `v1` và `v2`.

**Đầu ra**:  
Giá trị của nút tổ tiên thấp nhất.

**Ví dụ**:
| Đầu vào                          | Đầu ra |
|----------------------------------|--------|
| `6\n4 2 3 1 7 6\n1 7`            | `4`    |