#include "../testlib.h"
#include <bits/stdc++.h>
using namespace std;

// Giới hạn cho Subtask 1
const int MAXN_SUB1 = 10;
const int MAXM_SUB1 = 20;
const int MAXW = 1e9; // Trọng số tối đa giữ nguyên cho mọi subtask

// Hàm tiện ích để in đồ thị và xáo trộn các cạnh
void print_graph(int n, int m, vector<tuple<int, int, int>>& edges) {
    cout << n << " " << m << "\n";
    shuffle(edges.begin(), edges.end());
    for (const auto& edge : edges) {
        cout << get<0>(edge) << " " << get<1>(edge) << " " << get<2>(edge) << "\n";
    }
}

// Case 1: Sinh test ngẫu nhiên thông thường, đảm bảo có đường đi 1->n
void genNormalCase() {
    int n = rnd.next(7, MAXN_SUB1);
    int m = rnd.next(n, MAXM_SUB1);
    
    vector<tuple<int, int, int>> edges;
    set<pair<int, int>> existing_edges;

    // Đảm bảo có đường đi từ 1 đến n
    vector<int> p(n);
    iota(p.begin(), p.end(), 1);
    shuffle(p.begin() + 1, p.end() - 1); // Xáo trộn các đỉnh ở giữa
    for (size_t i = 0; i < p.size() - 1; ++i) {
        int u = p[i], v = p[i+1];
        if (u > v) swap(u, v);
        if (existing_edges.find({u, v}) == existing_edges.end()) {
            edges.emplace_back(u, v, rnd.next(1, 1000));
            existing_edges.insert({u, v});
        }
    }

    // Thêm các cạnh ngẫu nhiên cho đến khi đủ m cạnh
    while (edges.size() < m) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n);
        if (u == v) continue;
        if (u > v) swap(u, v);
        if (existing_edges.find({u, v}) == existing_edges.end()) {
            edges.emplace_back(u, v, rnd.next(1, 1000));
            existing_edges.insert({u, v});
        }
    }

    print_graph(n, edges.size(), edges);
}

// Case 2: Đồ thị dạng đường thẳng (Line Graph)
void genSpecialCase1() {
    int n = MAXN_SUB1;
    int m = n - 1;
    vector<tuple<int, int, int>> edges;
    for (int i = 1; i < n; ++i) {
        edges.emplace_back(i, i + 1, rnd.next(1, 100));
    }
    print_graph(n, m, edges);
}

// Case 3: Đồ thị không liên thông, không có đường đi từ 1 đến n
void genSpecialCase2() {
    int n = MAXN_SUB1;
    int m = rnd.next(n-2, MAXM_SUB1);
    vector<tuple<int, int, int>> edges;
    set<pair<int, int>> existing_edges;

    while (edges.size() < m) {
        // Chỉ tạo cạnh giữa các đỉnh từ 1 đến n-1
        int u = rnd.next(1, n - 1);
        int v = rnd.next(1, n - 1);
        if (u == v) continue;
        if (u > v) swap(u, v);
        if (existing_edges.find({u, v}) == existing_edges.end()) {
            edges.emplace_back(u, v, rnd.next(1, 1000));
            existing_edges.insert({u, v});
        }
    }
    print_graph(n, edges.size(), edges);
}

// Case 4: Bẫy Dijkstra - đường đi vòng ngắn hơn đường đi thẳng
void genSpecialCase3() {
    int n = MAXN_SUB1;
    vector<tuple<int, int, int>> edges;
    
    int mid_node = rnd.next(2, n - 1);
    int w1 = rnd.next(10, 50);
    int w2 = rnd.next(10, 50);
    int w_direct = w1 + w2 + rnd.next(10, 50); // Đảm bảo đường thẳng dài hơn

    edges.emplace_back(1, mid_node, w1);
    edges.emplace_back(mid_node, n, w2);
    edges.emplace_back(1, n, w_direct);
    
    print_graph(n, edges.size(), edges);
}

// Case 5: Edge case, đường đi ít cạnh vs nhiều cạnh
void genEdgeCase() {
    int n = MAXN_SUB1;
    int m = n;
    vector<tuple<int, int, int>> edges;
    
    // Đường đi nhiều cạnh, tổng trọng số nhỏ
    int total_weight = 0;
    for (int i = 1; i < n; ++i) {
        int w = rnd.next(1, 5);
        edges.emplace_back(i, i + 1, w);
        total_weight += w;
    }
    // Cạnh trực tiếp, trọng số lớn
    edges.emplace_back(1, n, total_weight + rnd.next(1, 10));

    print_graph(n, m, edges);
}

// Case 6: Stress test, n và m max, trọng số lớn
void genStressCase() {
    int n = MAXN_SUB1;
    int m = MAXM_SUB1;
    
    vector<tuple<int, int, int>> edges;
    set<pair<int, int>> existing_edges;

    // Tạo một cây khung ngẫu nhiên để đảm bảo đồ thị liên thông
    vector<int> p(n);
    iota(p.begin(), p.end(), 1);
    shuffle(p.begin(), p.end());
    for(int i = 1; i < n; ++i) {
        int u = p[i];
        int v = p[rnd.next(0, i - 1)];
        if (u > v) swap(u,v);
        edges.emplace_back(u, v, rnd.next(MAXW / 100, MAXW));
        existing_edges.insert({u, v});
    }

    // Thêm cạnh ngẫu nhiên
    while (edges.size() < m) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n);
        if (u == v) continue;
        if (u > v) swap(u, v);
        if (existing_edges.find({u, v}) == existing_edges.end()) {
            edges.emplace_back(u, v, rnd.next(1, MAXW));
            existing_edges.insert({u, v});
        }
    }
    
    print_graph(n, edges.size(), edges);
}


int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int type = atoi(argv[1]);
    int seed = atoi(argv[2]);
    rnd.setSeed(seed);

    if (type == 1) genNormalCase();
    else if (type == 2) genSpecialCase1(); // Line Graph
    else if (type == 3) genSpecialCase2(); // Disconnected
    else if (type == 4) genSpecialCase3(); // Dijkstra Trap
    else if (type == 5) genEdgeCase();
    else genStressCase();

    return 0;
}