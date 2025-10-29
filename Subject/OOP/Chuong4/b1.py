import random

class cArray:
    def __init__(self):
        self.arr = []
    
    def Size(self):
        return len(self.arr)

    def Input(self, n):
        while True:
            try:
                print(f"Nhap {n} so nguyen:", end=' ')
                self.arr = [int(x) for x in input().split()]
                
                assert n == len(self.arr)
                break

            except ValueError:
                print("Error: Khac kieu du lieu.")

            except AssertionError:
                print(f"Error: Do dai khong khop! Day do dai {n} nhung ban nhap {len(self.arr)} So")
    
    def Output(self):
        print(f"Day {self.Size()} so nguyen la: {self.arr}")

    def __str__(self):
        return f"Day {self.Size()} so nguyen la: {self.arr}"

    def MakeRandomArr(self, n):
        self.arr = [random.randint(0, 100) for _ in range(n)]

    def Count(self, num):
        cnt = 0
        for x in self.arr:
            if num == x:
                cnt += 1
        return cnt

    def IsIncreasing(self):
        return all(self.arr[i - 1] <= self.arr[i] for i in range(1, self.Size()))

    def MinOdd(self):
        odd_numbers = [x for x in self.arr if x % 2 == 1]
        if not odd_numbers:
            return None # tap rong -> khong co gia tri le nao
        return min(odd_numbers)

    def SortAscending(self):
        self.arr.sort()

if __name__ == "__main__":
    a = cArray()

    a.MakeRandomArr(5)
    print(a)

    print(a.Count(3))

    a.SortAscending()
    print(a)