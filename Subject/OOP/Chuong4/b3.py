class DonThuc:
    def __init__(self, a=0, b=0):
        self.a = a # he so
        self.b = b # so mu

    def input_donthuc(self):
        self.a = float(input("Nhập hệ số a: "))
        self.b = int(input("Nhập số mũ b: "))

    def __str__(self):
        if self.b == 0:
            return f"{self.a}"
        elif self.b == 1:
            return f"{self.a}x"
        else:
            return f"{self.a}x^{self.b}"

    def evaluate(self, x):
        return self.a * (x ** self.b)

    def derivative(self):
        if self.b == 0:
            return DonThuc(0, 0)  
        return DonThuc(self.a * self.b, self.b - 1)

    def __add__(self, other):
        if self.b != other.b:
            raise ValueError("Không thể cộng hai đơn thức khác bậc")
        return DonThuc(self.a + other.a, self.b)
