class Matrix:    
    def __init__(self, rows, cols, data=None):
        self.rows = rows
        self.cols = cols
        if data is None:
            self.data = [[0 for _ in range(cols)] for _ in range(rows)]
        else:
            self.data = data
        self.__fix()
    
    def __fix_add(self, other):
        if self.rows != other.rows or self.cols != other.cols:
            raise ValueError("Hai ma tran khong hop le de cong tru")
    
    def __fix_mul(self, other):
        if self.cols != other.rows:
            raise ValueError("Hai ma tran khong hop le de nhan")
    
    def __fix(self):
        if self.rows != self.data.__len__():
            raise ValueError("So hang khong hop le")
        for row in self.data:
            if self.cols != row.__len__():
                raise ValueError("So cot khong hop le")

    def __add__(self, other):
        self.__fix_add(other)
        res = Matrix(self.rows, self.cols, self.data)
        for i in range(self.rows):
            for j in range(self.cols):
                res.data[i][j] = self.data[i][j] + other.data[i][j]
        return res
    
    def __sub__(self, other):
        self.__fix_add(other)
        res = Matrix(self.rows, self.cols, self.data)
        for i in range(self.rows):
            for j in range(self.cols):
                res.data[i][j] = self.data[i][j] - other.data[i][j]
        return res
    
    def __mul__(self, other):
        self.__fix_mul(other)
        res = Matrix(self.rows, other.cols)
        for i in range(self.rows):
            for j in range(other.cols):
                for k in range(self.cols):
                    res.data[i][j] += self.data[i][k] * other.data[k][j]
        return res

    def __str__(self):
        res = ""
        for row in self.data:
            for x in row:
                res += str(x) + " "
            res += '\n'
        return res

if __name__ == "__main__":
    print("Nhap ma tran 1:")
    row1 = int(input("Nhap so hang: "))
    col1 = int(input("Nhap so cot: "))
    data1 = []
    for i in range(row1):
        row = [int(x) for x in input(f"Nhap hang {i+1} (cach nhau boi khoang trang): ").split()]
        data1.append(row)
    m1 = Matrix(row1, col1, data1)
    
    print("Nhap ma tran 2:")
    row2 = int(input("Nhap so hang: "))
    col2 = int(input("Nhap so cot: "))
    data2 = []
    for i in range(row2):
        row = [int(x) for x in input(f"Nhap hang {i+1} (cach nhau boi khoang trang): ").split()]
        data2.append(row)
    m2 = Matrix(row2, col2, data2)
    
    print("Tong hai ma tran:", m1 + m2, sep='\n')
    print("Hieu hai ma tran:", m1 - m2, sep='\n')
    print("Tich hai ma tran:", m1 * m2, sep='\n')