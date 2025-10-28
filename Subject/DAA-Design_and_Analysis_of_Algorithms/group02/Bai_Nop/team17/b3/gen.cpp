#include "testlib.h"
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <set>

using namespace std;

// Sinh đồ thị ngẫu nhiên
void genNormalCase() {
    int n = rnd.next(8, 12);
    int m_max = n * (n - 1) / 2;
    int m = rnd.next(n - 1, m_max);
    cout << n << " " << m << endl;
    vector<pair<int, int>> all_edges;
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            all_edges.push_back({i, j});
        }
    }
    shuffle(all_edges.begin(), all_edges.end());
    for (int i = 0; i < m; ++i) {
        cout << all_edges[i].first << " " << all_edges[i].second << endl;
    }
}

// Sinh đồ thị chắc chắn có đường đi Hamilton (LOGIC ĐÃ SỬA LẠI)
void genSpecialCase() {
    int n = 12;
    vector<int> p(n);
    iota(p.begin(), p.end(), 1);
    shuffle(p.begin(), p.end());

    set<pair<int, int>> existing_edges;
    // Tạo đường đi Hamilton
    for (int i = 0; i < n - 1; ++i) {
        int u = p[i], v = p[i + 1];
        if (u > v) swap(u, v);
        existing_edges.insert({u, v});
    }

    int m_extra = rnd.next(0, 10);
    int m = existing_edges.size() + m_extra;
    cout << n << " " << m << endl;

    // In ra các cạnh của đường đi
    for (const auto& edge : existing_edges) {
        cout << edge.first << " " << edge.second << endl;
    }
    
    // Thêm chính xác m_extra cạnh mới
    while (existing_edges.size() < m) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n);
        if (u == v) continue;
        if (u > v) swap(u, v);
        if (existing_edges.find({u, v}) == existing_edges.end()) {
            existing_edges.insert({u, v});
            cout << u << " " << v << endl;
        }
    }
}

// Sinh đồ thị không có đường đi (ví dụ: đỉnh bị cô lập)
void genEdgeCase() {
    int n = rnd.next(5, 12);
    int m_max = (n / 2) * (n / 2 - 1) / 2;
    int m = rnd.next(0, m_max);
    cout << n << " " << m << endl;
    
    set<pair<int, int>> edges;
    while(edges.size() < m) {
        int u = rnd.next(1, n / 2);
        int v = rnd.next(1, n / 2);
        if (u == v) continue;
        if (u > v) swap(u,v);
        edges.insert({u, v});
    }
    for(const auto& edge : edges) {
        cout << edge.first << " " << edge.second << endl;
    }
}


// Sinh đồ thị đầy đủ (luôn có đường đi)
void genStressCase() {
    int n = 12;
    int m = n * (n - 1) / 2;
    cout << n << " " << m << endl;
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            cout << i << " " << j << endl;
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