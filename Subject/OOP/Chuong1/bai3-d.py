# Viết chương trình nhập vào một ngày. Tìm ngày kế tiếp và xuất kết quả.

class Lich:
    def __init__(self, ngay, thang, nam):
        self.ngay = ngay
        self.thang = thang
        self.nam = nam
        self.__fix()
        
    def __fix(self):
        if self.nam < 0:
            raise ValueError("Nam phai lon hon hoac bang 0")
        if self.thang < 1 or self.thang > 12:
            raise ValueError("Thang phai trong khoang tu 1 den 12")
        if self.ngay < 1 or self.ngay > self.__days_in_month():
            raise ValueError(f"Ngay phai trong khoang tu 1 den {self.__days_in_month()}")
        
    def __days_in_month(self):
        if self.thang in [1, 3, 5, 7, 8, 10, 12]:
            return 31
        elif self.thang in [4, 6, 9, 11]:
            return 30
        elif self.thang == 2:
            if (self.nam % 4 == 0 and self.nam % 100 != 0) or (self.nam % 400 == 0):
                return 29
            else:
                return 28
            
    def next_day(self):
        ngay = self.ngay + 1            
        thang = self.thang
        nam = self.nam
        if ngay > self.__days_in_month():
            ngay = 1
            thang += 1
            if thang > 12:
                thang = 1
                nam += 1
        return Lich(ngay, thang, nam)
    def __str__(self):
        return f"{self.ngay:02d}/{self.thang:02d}/{self.nam}"   


if __name__ == "__main__":
    ngay = int(input("Nhap ngay: "))
    thang = int(input("Nhap thang: "))
    nam = int(input("Nhap nam: "))
    date = Lich(ngay, thang, nam)
    print(f"Ngay vua nhap: {date}")
    print(f"Ngay ke tiep: {date.next_day()}")   