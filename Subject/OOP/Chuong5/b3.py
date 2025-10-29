class DaThuc:
    def __init__(self, bac=0):
        # bậc n -> có (n+1) hệ số
        self.bac = bac
        self.heso = [0.0 for _ in range(bac + 1)]


    def Input(self):
        while True:
            try:
                self.bac = int(input("Nhap bac cua da thuc (>=0): "))
                assert self.bac >= 0
                print(f"Nhap {self.bac + 1} he so (tu bac cao den bac 0):")
                self.heso = [float(x) for x in input().split()]
                assert len(self.heso) == self.bac + 1
                break
            except ValueError:
                print("Error: Khac kieu du lieu (yeu cau so thuc).")
            except AssertionError:
                print("Error: Nhap sai so luong he so hoac bac am!")

    def Output(self):
        print(self)

    def __str__(self):
   
        s = ""
        n = self.bac
        for i, a in enumerate(self.heso):
            if abs(a) < 1e-12:
                continue  # bỏ hệ số = 0
            mu = n - i
            # biểu diễn từng hạng tử
            if mu == 0:
                term = f"{a:+g}"
            elif mu == 1:
                term = f"{a:+g}x"
            else:
                term = f"{a:+g}x^{mu}"
            s += term
        if not s:
            s = "0"
        if s[0] == '+':  # bỏ dấu + đầu tiên cho đẹp
            s = s[1:]
        return f"P(x) = {s}"

    def TinhGiaTri(self, x):
        kq = 0.0
        n = self.bac
        for i, a in enumerate(self.heso):
            kq += a * (x ** (n - i))
        return kq

    def __add__(self, other):
        # căn chỉnh bậc 2 đa thức
        n1, n2 = self.bac, other.bac
        if n1 > n2:
            diff = n1 - n2
            h2 = [0.0] * diff + other.heso
            h1 = self.heso[:]
            bac_moi = n1
        else:
            diff = n2 - n1
            h1 = [0.0] * diff + self.heso
            h2 = other.heso[:]
            bac_moi = n2

        tong = [h1[i] + h2[i] for i in range(len(h1))]
        return DaThuc.FromList(tong, bac_moi)

    def __sub__(self, other):
        n1, n2 = self.bac, other.bac
        if n1 > n2:
            diff = n1 - n2
            h2 = [0.0] * diff + other.heso
            h1 = self.heso[:]
            bac_moi = n1
        else:
            diff = n2 - n1
            h1 = [0.0] * diff + self.heso
            h2 = other.heso[:]
            bac_moi = n2

        hieu = [h1[i] - h2[i] for i in range(len(h1))]
        return DaThuc.FromList(hieu, bac_moi)

    # 
    @classmethod
    def FromList(cls, heso_list, bac):
        # loại bỏ hệ số 0 ở đầu nếu có
        while len(heso_list) > 1 and abs(heso_list[0]) < 1e-12:
            heso_list.pop(0)
            bac -= 1
        dt = cls(bac)
        dt.heso = heso_list
        return dt

# test
if __name__ == "__main__":
    print("=== Chuong trinh xu ly da thuc ===")

    print("Nhap da thuc thu 1:")
    P1 = DaThuc()
    P1.Input()

    print("\nNhap da thuc thu 2:")
    P2 = DaThuc()
    P2.Input()

    print("\nDa thuc P1:")
    P1.Output()
    print("Da thuc P2:")
    P2.Output()

    tong = P1 + P2
    hieu = P1 - P2

    print(f"\nP1 + P2 = {tong}")
    print(f"P1 - P2 = {hieu}")

    x = float(input("\nNhap gia tri x can tinh: "))
    print(f"P1({x}) = {P1.TinhGiaTri(x):.3f}")
    print(f"P2({x}) = {P2.TinhGiaTri(x):.3f}")
