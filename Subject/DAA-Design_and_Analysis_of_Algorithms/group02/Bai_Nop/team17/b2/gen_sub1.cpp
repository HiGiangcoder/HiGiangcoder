#include "testlib.h"
#include <iostream>
#include <vector>

using namespace std;

#define MAX_A (int)1e9

// Trường hợp thông thường: đồ thị nhỏ ngẫu nhiên
void genNormalCase() {
    int n = rnd.next(5, 10);
    int m = rnd.next(5, 20);
    cout << n << " " << m << endl;
    for (int i = 0; i < m; ++i) {
        int val = rnd.next(0, 4);
        int u = rnd.next(1, n), v = rnd.next(1, n); 
        if(val != 2) while(u == v) v = rnd.next(1, n);
        cout << u << " " << v << " " << rnd.next(1, MAX_A) << endl;
    }
}

// Trường hợp đặc biệt: Đa đồ thị (nhiều cạnh nối 2 đỉnh), đồ thị không liên thông
void genSpecialCase() {
    int n = 10;
    int m = 20;
    vector<bool> flag(n + 1, false);
    flag[1] = 1; 
    cout << n << " " << m << endl;
    int t = rnd.next(1, 5);
    // Test đa đồ thị
    for (int i = 0; i < t; ++i) {
        int x = 1, y = rnd.next(2, n - 1);
        int val = rnd.next(0, 1); 

        if(val) swap(x, y);

        cout << x << " " << y << " " << rnd.next(1, MAX_A) << endl;
        flag[y] = 1;
    }
    for (int i = 0; i < 20 - t; ++i) {
        int u = rnd.next(2, n); while(flag[u]) u = rnd.next(2, n);
        int v = rnd.next(2, n); while(flag[v] || u == v) v = rnd.next(2, n);

        cout << u << " " << v << " " << rnd.next(1, MAX_A) << endl;
    }
}

// Trường hợp biên: n nhỏ nhất, m=0
void genEdgeCase() {
    int n = 2;
    int m = rnd.next(0, 1); // Hoặc không có cạnh nào, hoặc có 1 cạnh
    cout << n << " " << m << endl;
    for (int i = 0; i < m; ++i) {
        cout << 1 << " " << 2 << " " << rnd.next(1, MAX_A) << endl;
    }
}

// Trường hợp cực đại: n, m lớn nhất trong subtask
void genStressCase() {
    int n = 10;
    int m = 20;
    cout << n << " " << m << endl;
    
    // Phần 1: Tạo đường đi chính từ 1 đến n (đảm bảo liên thông)
    vector<int> path;
    for(int i = 1; i <= n; i++) path.push_back(i);
    // Xáo trộn các đỉnh giữa (trừ 1 và n)
    for(int i = 2; i <= n; i++) {
        int j = rnd.next(1, i - 1);
        swap(path[i - 1], path[j - 1]);
    }
    
    // Thêm các cạnh của đường đi chính
    for(int i = 0; i < n-1; i++) {
        cout << path[i] << " " << path[i+1] << " " << rnd.next(1, MAX_A) << endl;
        m--;
    }
    
    // Phần 2: Thêm cạnh đa đồ thị (nhiều cạnh giữa cùng 2 đỉnh)
    int multi_edges = rnd.next(3, 8);
    for(int i = 0; i < multi_edges && m > 0; i++) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n);
        if(u != v) {
            int repeats = rnd.next(2, min(4, m));
            for(int j = 0; j < repeats && m > 0; j++) {
                cout << u << " " << v << " " << rnd.next(1, MAX_A) << endl;
                m--;
            }
        }
    }
    
    // Phần 3: Thêm cạnh ngẫu nhiên còn lại
    while(m > 0) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n);
        if(u != v) {
            cout << u << " " << v << " " << rnd.next(1, MAX_A) << endl;
            m--;
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int type = atoi(argv[1]);
    if (type == 1) genNormalCase();
    else if (type == 2) genSpecialCase();
    else if (type == 3) genEdgeCase();
    else genStressCase();

    return 0;
}