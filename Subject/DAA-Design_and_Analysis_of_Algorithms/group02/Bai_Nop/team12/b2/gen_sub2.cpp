#include "../testlib.h"
#include <bits/stdc++.h>
using namespace std;

// Giới hạn cho Subtask 2
const int MAXN_SUB2 = 1000;
const int MAXM_FULL = 200000; // Giới hạn m của toàn bài
const long long MAXW = 1e9;

// Hàm tiện ích để in đồ thị và xáo trộn các cạnh
void print_graph(int n, int m, vector<tuple<int, int, long long>>& edges) {
    cout << n << " " << m << "\n";
    shuffle(edges.begin(), edges.end());
    for (const auto& edge : edges) {
        cout << get<0>(edge) << " " << get<1>(edge) << " " << get<2>(edge) << "\n";
    }
}

// Case 1: Test ngẫu nhiên, đồ thị tương đối thưa
void genNormalCase() {
    int n = rnd.next(800, MAXN_SUB2);
    int m = rnd.next(2 * n, 5 * n);
    
    vector<tuple<int, int, long long>> edges;
    set<pair<int, int>> existing_edges;

    // Tạo cây khung ngẫu nhiên để đảm bảo liên thông
    vector<int> p(n);
    iota(p.begin(), p.end(), 1);
    shuffle(p.begin(), p.end());
    for(int i = 1; i < n; ++i) {
        int u = p[i];
        int v = p[rnd.next(0, i - 1)];
        if (u > v) swap(u,v);
        edges.emplace_back(u, v, rnd.next(1LL, 100000LL));
        existing_edges.insert({u, v});
    }

    // Thêm cạnh ngẫu nhiên
    while (edges.size() < m) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n);
        if (u == v) continue;
        if (u > v) swap(u, v);
        if (existing_edges.find({u, v}) == existing_edges.end()) {
            edges.emplace_back(u, v, rnd.next(1LL, 100000LL));
            existing_edges.insert({u, v});
        }
    }
    print_graph(n, edges.size(), edges);
}

// Case 2: Đường đi dài với trọng số lớn (kiểm tra long long)
void genSpecialCase1() {
    int n = MAXN_SUB2;
    int m = n - 1;
    vector<tuple<int, int, long long>> edges;
    
    vector<int> p(n);
    iota(p.begin(), p.end(), 1);
    shuffle(p.begin() + 1, p.end() - 1);

    for (size_t i = 0; i < p.size() - 1; ++i) {
        edges.emplace_back(p[i], p[i+1], rnd.next(MAXW - 10000, MAXW));
    }
    print_graph(n, m, edges);
}

// Case 3: Đồ thị không liên thông
void genSpecialCase2() {
    int n = MAXN_SUB2;
    int m = rnd.next(n, 2 * n);
    vector<tuple<int, int, long long>> edges;
    set<pair<int, int>> existing_edges;

    while (edges.size() < m) {
        int u = rnd.next(1, n - 1);
        int v = rnd.next(1, n - 1);
        if (u == v) continue;
        if (u > v) swap(u, v);
        if (existing_edges.find({u, v}) == existing_edges.end()) {
            edges.emplace_back(u, v, rnd.next(1LL, 1000LL));
            existing_edges.insert({u, v});
        }
    }
    print_graph(n, edges.size(), edges);
}

// Case 4: Đồ thị dày đặc (kiểm tra hiệu năng)
void genSpecialCase3() {
    int n = rnd.next(400, 500); // Giảm N để M có thể rất lớn so với N^2
    
    // Tính số cạnh tối đa có thể có với n đỉnh
    long long max_possible_edges = (long long)n * (n - 1) / 2;
    // Lấy giá trị nhỏ hơn giữa giới hạn của đề bài và giới hạn thực tế
    int m = min((long long)MAXM_FULL, max_possible_edges);
    // --- KẾT THÚC SỬA LỖI ---

    vector<tuple<int, int, long long>> edges;
    set<pair<int, int>> existing_edges;
    
    // Tạo cây khung để đảm bảo đồ thị liên thông (nếu m >= n-1)
    if (m >= n - 1) {
        for(int i = 2; i <= n; ++i) {
            int u = i, v = rnd.next(1, i - 1);
            edges.emplace_back(u, v, rnd.next(1LL, MAXW));
            existing_edges.insert({min(u, v), max(u, v)});
        }
    }

    // Thêm các cạnh ngẫu nhiên cho đến khi đủ m cạnh
    while (edges.size() < m) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n);
        if (u == v) continue;
        if (u > v) swap(u, v);
        if (existing_edges.find({u, v}) == existing_edges.end()) {
            edges.emplace_back(u, v, rnd.next(1LL, MAXW));
            existing_edges.insert({u, v});
        }
    }
    print_graph(n, m, edges);
}

// Case 5: Bẫy BFS/Greedy
void genEdgeCase() {
    int n = MAXN_SUB2;
    int m = n;
    vector<tuple<int, int, long long>> edges;
    
    long long total_weight = 0;
    for (int i = 1; i < n; ++i) {
        long long w = rnd.next(1LL, 5LL);
        edges.emplace_back(i, i + 1, w);
        total_weight += w;
    }
    edges.emplace_back(1, n, total_weight + rnd.next(1LL, 100LL));

    print_graph(n, m, edges);
}

// Case 6: Stress test, n và m max
void genStressCase() {
    int n = MAXN_SUB2;
    int m = MAXM_FULL;
    vector<tuple<int, int, long long>> edges;
    set<pair<int, int>> existing_edges;

    // Tạo cây khung
    for(int i = 2; i <= n; ++i) {
        int u = i, v = rnd.next(1, i - 1);
        edges.emplace_back(u, v, rnd.next(1LL, MAXW));
        existing_edges.insert({min(u, v), max(u, v)});
    }

    while (edges.size() < m) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n);
        if (u == v) continue;
        if (u > v) swap(u, v);
        if (existing_edges.find({u, v}) == existing_edges.end()) {
            edges.emplace_back(u, v, rnd.next(1LL, MAXW));
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
    else if (type == 2) genSpecialCase1(); // Long Path (long long test)
    else if (type == 3) genSpecialCase2(); // Disconnected
    else if (type == 4) genSpecialCase3(); // Dense Graph (performance test)
    else if (type == 5) genEdgeCase();
    else genStressCase();

    return 0;
}