#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000;

void genNormalCase() {
    int n = rnd.next(10, MAXN); // số phần tử (ví dụ lấy 10..100 cho dễ test)
    cout << n << "\n";
    for (int i = 0; i < n; i++) {
        cout << rnd.next(-100, 100) << " \n"[i == n - 1];
    }
}

void genSpecialCase() {
    
    int type = rnd.next(1, 4); // chọn ngẫu nhiên 1 trong 4 case
    int n = rnd.next(5, 10);   // số phần tử nhỏ để dễ kiểm tra

    if (type == 1) {
        // Case 1: tất cả phần tử = 0
        cout << n << "\n";
        for (int i = 0; i < n; i++) cout << 0 << " \n"[i == n - 1];
    } 
    else if (type == 2) {
        // Case 2: tất cả phần tử = MAX
        cout << n << "\n";
        for (int i = 0; i < n; i++) cout << 100000 << " \n"[i == n - 1];
    } 
    else if (type == 3) {
        // Case 3: tất cả phần tử = MIN
        cout << n << "\n";
        for (int i = 0; i < n; i++) cout << -100000 << " \n"[i == n - 1];
    } 
    else if (type == 4) {
        // Case 4: n = 1, phần tử duy nhất rất lớn
        cout << 1 << "\n";
        cout << 99999 << "\n";
    }
}

void genEdgeCase() {
    int type = rnd.next(1, 4); // chọn ngẫu nhiên edge case
    if (type == 1) {
        // Case 1: n = 1, phần tử nhỏ nhất
        cout << 1 << "\n";
        cout << -100000 << "\n";
    } 
    else if (type == 2) {
        // Case 2: n = 1, phần tử lớn nhất
        cout << 1 << "\n";
        cout << 100000 << "\n";
    } 
    else if (type == 3) {
        // Case 3: n = MAXN, toàn bộ = 100000
        cout << MAXN << "\n";
        for (int i = 0; i < MAXN; i++)
            cout << 100000 << " \n"[i == MAXN - 1];
    } 
    else {
        // Case 4: n = MAXN, xen kẽ -100000 và 100000
        cout << MAXN << "\n";
        for (int i = 0; i < MAXN; i++) {
            int val = (i % 2 == 0 ? 100000 : -100000);
            cout << val << " \n"[i == MAXN - 1];
        }
    }
}

void genStressCase() {
    int type = rnd.next(1, 4);
    int n = MAXN; // kích thước lớn nhất
    cout << n << "\n";

    if (type == 1) {
        // Case 1: tất cả = 100000
        for (int i = 0; i < n; i++)
            cout << 100000 << " \n"[i == n - 1];
    } 
    else if (type == 2) {
        // Case 2: tất cả = -100000
        for (int i = 0; i < n; i++)
            cout << -100000 << " \n"[i == n - 1];
    } 
    else if (type == 3) {
        // Case 3: xen kẽ 100000 và -100000
        for (int i = 0; i < n; i++)
            cout << (i % 2 ? -100000 : 100000) << " \n"[i == n - 1];
    } 
    else {
        // Case 4: ngẫu nhiên [-100000, 100000]
        for (int i = 0; i < n; i++)
            cout << rnd.next(-100000, 100000) << " \n"[i == n - 1];
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int seed = atoi(argv[2]);
    rnd.setSeed(seed);

    int type = (argc > 1) ? atoi(argv[1]) : 1;
    if (type == 1) genNormalCase();
    else if (type == 2) genSpecialCase();
    else if (type == 3) genEdgeCase();
    else genStressCase();
    return 0;
}
