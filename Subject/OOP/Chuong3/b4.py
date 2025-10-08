'''
4. Cài đặt lớp cArray để biểu diễn mảng một chiều các 
số nguyên cho phép thực hiện các yêu cầu sau:
▪ Tạo lập mảng gồm n số nguyên ngẫu nhiên bằng 
constructor
▪ Xuất mảng ra màn hình
▪ Tìm số âm lớn nhất
▪ Đếm lần xuất hiện của một số nguyên x
▪ Kiểm tra mảng có giảm dần không
▪ Sắp xếp mảng tăng dần
'''

class cArray:
    def __init__(self, n=0, lower=0, upper=100):
        import random
        self.arr = [random.randint(lower, upper) for _ in range(n)]

    def xuat(self):
        print("Dãy số nguyên:", ' '.join(map(str, self.arr)))

    def tim_so_am_lon_nhat(self):
        so_am = [num for num in self.arr if num < 0]
        return max(so_am) if so_am else None

    def dem_x(self, x):
        return self.arr.count(x)

    def kiem_tra_giam_dan(self):
        return all(self.arr[i] >= self.arr[i + 1] for i in range(len(self.arr) - 1))

    def sap_xep_tang_dan(self):
        self.arr.sort()