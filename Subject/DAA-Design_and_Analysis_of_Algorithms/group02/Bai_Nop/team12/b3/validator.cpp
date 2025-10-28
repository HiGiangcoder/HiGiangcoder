#include "../testlib.h"
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Đọc và kiểm tra n trên dòng đầu tiên
    int n = inf.readInt(1, 12, "n");
    inf.readSpace();

    // Tính số cạnh tối đa có thể có với n đỉnh
    long long max_m = (long long)n * (n - 1) / 2;

    // Đọc và kiểm tra m
    int m = inf.readInt(0, max_m, "m");
    inf.readEoln();

    // Dùng set để kiểm tra cạnh lặp một cách hiệu quả
    set<pair<int, int>> existing_edges;

    for (int i = 0; i < m; i++) {
        // Đọc 2 đỉnh u, v
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readEoln();

        // Kiểm tra không có khuyên (u != v)
        ensuref(u != v, "Self-loop detected on vertex %d", u);

        // Chuẩn hóa (u, v) để (u, v) và (v, u) là như nhau
        if (u > v) swap(u, v);
        
        // Kiểm tra cạnh lặp
        ensuref(existing_edges.find({u, v}) == existing_edges.end(), "Duplicate edge between %d and %d", u, v);
        existing_edges.insert({u, v});
    }

    // Đảm bảo file kết thúc tại đây, không có dữ liệu thừa
    inf.readEof();
}