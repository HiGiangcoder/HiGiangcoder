import random

class Matrix:
    def __init__(self, rows=0, cols=0):
        self.rows = rows
        self.cols = cols
        self.data = [[0 for _ in range(cols)] for _ in range(rows)]

    def Size(self):
        return (self.rows, self.cols)

    def Input(self, m, n):
        """Nhập ma trận m dòng n cột"""
        self.rows = m
        self.cols = n
        self.data = []
        print(f"Nhập ma trận {m}x{n}:")
        for i in range(m):
            while True:
                try:
                    row = [int(x) for x in input(f"  Dòng {i+1}: ").split()]
                    assert len(row) == n
                    self.data.append(row)
                    break
                except ValueError:
                    print("  Error: Khác kiểu dữ liệu (phải nhập số nguyên).")
                except AssertionError:
                    print(f"  Error: Cần nhập đúng {n} phần tử cho dòng này.")

    def MakeRandom(self, m, n, low=0, high=10):
        """Tạo ma trận ngẫu nhiên m x n"""
        self.rows = m
        self.cols = n
        self.data = [[random.randint(low, high) for _ in range(n)] for _ in range(m)]

    def Output(self):
        print(f"Ma trận {self.rows}x{self.cols}:")
        for row in self.data:
            print(" ".join(map(str, row)))

    def __str__(self):
        s = [f"Ma trận {self.rows}x{self.cols}:"]
        for row in self.data:
            s.append(" ".join(map(str, row)))
        return "\n".join(s)

    def __add__(self, other):
        """Toán tử cộng hai ma trận"""
        if self.rows != other.rows or self.cols != other.cols:
            raise ValueError("Hai ma trận phải cùng kích thước để cộng.")
        result = Matrix(self.rows, self.cols)
        for i in range(self.rows):
            for j in range(self.cols):
                result.data[i][j] = self.data[i][j] + other.data[i][j]
        return result

    def __sub__(self, other):
        """Toán tử trừ hai ma trận"""
        if self.rows != other.rows or self.cols != other.cols:
            raise ValueError("Hai ma trận phải cùng kích thước để trừ.")
        result = Matrix(self.rows, self.cols)
        for i in range(self.rows):
            for j in range(self.cols):
                result.data[i][j] = self.data[i][j] - other.data[i][j]
        return result

    def __mul__(self, other):
        """Toán tử nhân hai ma trận"""
        if self.cols != other.rows:
            raise ValueError("Số cột ma trận A phải bằng số dòng ma trận B để nhân.")
        result = Matrix(self.rows, other.cols)
        for i in range(self.rows):
            for j in range(other.cols):
                for k in range(self.cols):
                    result.data[i][j] += self.data[i][k] * other.data[k][j]
        return result


if __name__ == "__main__":
    print("=== Ma trận A ===")
    A = Matrix()
    A.MakeRandom(2, 3)
    A.Output()

    print("\n=== Ma trận B ===")
    B = Matrix()
    B.MakeRandom(2, 3)
    B.Output()

    print("\n=== A + B ===")
    C = A + B
    C.Output()

    print("\n=== A - B ===")
    D = A - B
    D.Output()

    print("\n=== Nhân 2 ma trận có kích thước hợp lệ ===")
    E = Matrix()
    E.MakeRandom(3, 2)
    E.Output()

    print("\nA * E =")
    F = A * E
    F.Output()
