#include "../testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // n phải nằm trong khoảng [1, 100000]
    int n = inf.readInt(1, 100000, "n");
    inf.readEoln(); // Kết thúc dòng

    // Đọc và kiểm tra mảng a
    // Mảng phải có đúng n phần tử, mỗi phần tử trong khoảng [-100000, 100000]
    vector<int> a = inf.readInts(n, -100000, 100000, "a_i");
    inf.readEoln(); // Kết thúc dòng

    // Đảm bảo không còn dữ liệu nào khác trong file
    inf.readEof();
}