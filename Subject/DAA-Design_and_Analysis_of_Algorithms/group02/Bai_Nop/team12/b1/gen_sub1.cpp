#include "../testlib.h"
#include <bits/stdc++.h>
using namespace std;

// Giới hạn cho Subtask 1
const int MAXN_SUB1 = 1000;
const int MAX_A = 100000;

// Case 1: Sinh test ngẫu nhiên thông thường
void genNormalCase() {
    int n = rnd.next(MAXN_SUB1 / 10, MAXN_SUB1);
    cout << n << "\n";
    for (int i = 0; i < n; i++) {
        cout << rnd.next(-MAX_A, MAX_A) << " \n"[i == n - 1];
    }
}

// Case 2: Tất cả các phần tử bằng 0
void genSpecialCase1() {
    int n = rnd.next(MAXN_SUB1 / 2, MAXN_SUB1);
    cout << n << "\n";
    for (int i = 0; i < n; i++) {
        cout << 0 << " \n"[i == n - 1];
    }
}

// Case 3: Tất cả các phần tử là cùng một số dương
void genSpecialCase2() {
    int n = rnd.next(MAXN_SUB1 / 2, MAXN_SUB1);
    cout << n << "\n";
    int val = rnd.next(1, MAX_A);
    for (int i = 0; i < n; i++) {
        cout << val << " \n"[i == n - 1];
    }
}

// Case 4: Tất cả các phần tử là cùng một số âm
void genSpecialCase3() {
    int n = rnd.next(MAXN_SUB1 / 2, MAXN_SUB1);
    cout << n << "\n";
    int val = rnd.next(-MAX_A, -1);
    for (int i = 0; i < n; i++) {
        cout << val << " \n"[i == n - 1];
    }
}

// Case 5: n = 1
void genSpecialCase4() {
    int n = 1;
    cout << n << "\n";
    cout << rnd.next(-MAX_A, MAX_A) << "\n";
}


// Case 6: Trường hợp biên, n lớn nhất và giá trị a[i] lớn nhất/nhỏ nhất
void genEdgeCase() {
    int n = MAXN_SUB1;
    cout << n << "\n";
    int type = rnd.next(0, 1); // 0 for max value, 1 for min value
    if (type == 0) {
        for (int i = 0; i < n; i++) {
            cout << MAX_A << " \n"[i == n - 1];
        }
    } else {
        for (int i = 0; i < n; i++) {
            cout << -MAX_A << " \n"[i == n - 1];
        }
    }
}

// Case 7: Test hiệu năng, n lớn nhất và giá trị a[i] ngẫu nhiên
void genStressCase() {
    int n = MAXN_SUB1;
    cout << n << "\n";
    for (int i = 0; i < n; i++) {
        cout << rnd.next(-MAX_A, MAX_A) << " \n"[i == n - 1];
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int type = atoi(argv[1]);
    int seed = atoi(argv[2]);
    rnd.setSeed(seed);

    if (type == 1) genNormalCase();
    else if (type == 2) genSpecialCase1(); // All zeros
    else if (type == 3) genSpecialCase2(); // All same positive
    else if (type == 4) genSpecialCase3(); // All same negative
    else if (type == 5) genSpecialCase4(); // n = 1
    else if (type == 6) genEdgeCase();
    else genStressCase();

    return 0;
}