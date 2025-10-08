'''
Cài  đặt  lớp  số phức để  biểu  diễn  khái  niệm  số  phức  (một 
số phức bao gồm hai thành phần: phần ảo, phần thực).
Cho phép thực hiên các thao tác sau:
- Tạo lập số phức khi biết phần thực và ảo
- Thay đổi phần thực, phần ảo
- Lấy giá trị phần thực, phần ảo
- Nhập số phức
- Xuất số phức
- Công hai số phức.
❖Viết chương trình minh họa
    các chức năng của
    lớp số phức
'''

class SoPhuc:
    def __init__(self, phan_thuc=0, phan_ao=0):
        self.phan_thuc = phan_thuc
        self.phan_ao = phan_ao

    def thay_doi(self, phan_thuc=None, phan_ao=None):
        if phan_thuc is not None:
            self.phan_thuc = phan_thuc
        if phan_ao is not None:
            self.phan_ao = phan_ao

    def lay_gia_tri(self):
        return self.phan_thuc, self.phan_ao

    def nhap(self):
        self.phan_thuc = float(input("Nhập phần thực: "))
        self.phan_ao = float(input("Nhập phần ảo: "))

    def xuat(self):
        print(f"Số phức: {self.phan_thuc} + {self.phan_ao}i")

    def cong(self, other):
        return SoPhuc(self.phan_thuc + other.phan_thuc, self.phan_ao + other.phan_ao)

if __name__ == "__main__":
    print("Nhập số phức thứ nhất:")
    sp1 = SoPhuc()
    sp1.nhap()
    
    print("Nhập số phức thứ hai:")
    sp2 = SoPhuc()
    sp2.nhap()
    
    sp1.xuat()
    sp2.xuat()
    
    sp3 = sp1.cong(sp2)
    print("Tổng hai số phức là:")
    sp3.xuat()