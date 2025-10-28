#include "../testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Đọc và kiểm tra n, m trên dòng đầu tiên
    int n = inf.readInt(2, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 200000, "m");
    inf.readEoln();

    // Dùng set để kiểm tra cạnh lặp
    set<pair<int, int>> existing_edges;

    for (int i = 0; i < m; i++) {
        // Đọc 3 số trên một dòng
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readSpace();
        long long w = inf.readLong(1LL, 1000000000LL, "w");
        inf.readEoln();

        // Kiểm tra không có khuyên (self-loop)
        ensuref(u != v, "Self-loop detected on vertex %d", u);

        // Chuẩn hóa (u, v) để kiểm tra cạnh lặp cho đồ thị vô hướng
        if (u > v) swap(u, v);
        
        // Kiểm tra cạnh lặp
        ensuref(existing_edges.find({u, v}) == existing_edges.end(), "Multiple edges between %d and %d", u, v);
        existing_edges.insert({u, v});
    }

    // Đảm bảo file kết thúc tại đây
    inf.readEof();
}