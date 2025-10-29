# test_factorial_whitebox.py
import unittest
from factorial import factorial

class TestFactorialWhiteBox(unittest.TestCase):
    def test_negative_input(self):   # kiểm tra nhánh n < 0
        with self.assertRaises(ValueError):
            factorial(-5)

    def test_zero_input(self):       # kiểm tra nhánh n == 0
        self.assertEqual(factorial(0), 1)

    def test_positive_input(self):   # kiểm tra nhánh n > 0 + vòng lặp
        self.assertEqual(factorial(5), 120)   # vòng lặp chạy nhiều lần
        self.assertEqual(factorial(1), 1)     # vòng lặp chạy đúng 1 lần

if __name__ == "__main__":
    unittest.main()