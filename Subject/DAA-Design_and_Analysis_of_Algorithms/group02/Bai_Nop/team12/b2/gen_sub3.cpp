#include "../testlib.h"
#include <bits/stdc++.h>
using namespace std;

// Giới hạn cho Subtask 3 (toàn bộ bài toán)
const int MAXN_SUB3 = 100000;
const int MAXM_SUB3 = 200000;
const long long MAXW = 1e9;

// Hàm tiện ích để in đồ thị và xáo trộn các cạnh
void print_graph(int n, int m, vector<tuple<int, int, long long>>& edges) {
    cout << n << " " << m << "\n";
    shuffle(edges.begin(), edges.end());
    for (const auto& edge : edges) {
        cout << get<0>(edge) << " " << get<1>(edge) << " " << get<2>(edge) << "\n";
    }
}

// Case 1: Test ngẫu nhiên, n và m lớn
void genNormalCase() {
    int n = rnd.next(90000, MAXN_SUB3);
    int m = rnd.next(n + 1, MAXM_SUB3);
    
    vector<tuple<int, int, long long>> edges;
    set<pair<int, int>> existing_edges;

    // Tạo cây khung ngẫu nhiên để đảm bảo liên thông
    for(int i = 2; i <= n; ++i) {
        int u = i, v = rnd.next(1, i - 1);
        edges.emplace_back(u, v, rnd.next(1LL, MAXW));
        existing_edges.insert({min(u, v), max(u, v)});
    }

    // Thêm cạnh ngẫu nhiên
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

// Case 2: Đường đi rất dài với trọng số rất lớn (max test cho long long)
void genSpecialCase1() {
    int n = MAXN_SUB3;
    int m = n - 1;
    vector<tuple<int, int, long long>> edges;
    
    vector<int> p(n);
    iota(p.begin(), p.end(), 1);
    shuffle(p.begin() + 1, p.end() - 1); // Giữ 1 và n ở đầu cuối, xáo trộn giữa

    // Tìm vị trí của 1 và n để hoán đổi về đúng vị trí
    int pos1 = -1, posn = -1;
    for(int i=0; i<n; ++i) {
        if (p[i] == 1) pos1 = i;
        if (p[i] == n) posn = i;
    }
    swap(p[pos1], p[0]);
    swap(p[posn], p[n-1]);
    
    for (int i = 0; i < n - 1; ++i) {
        edges.emplace_back(p[i], p[i+1], rnd.next(MAXW - 100000, MAXW));
    }
    print_graph(n, m, edges);
}

// Case 3: Đồ thị không liên thông, n và m max
void genSpecialCase2() {
    int n = MAXN_SUB3;
    int m = MAXM_SUB3;
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

// Case 4: Đồ thị là một cây ngẫu nhiên (test đồ thị cực thưa)
void genSpecialCase3() {
    int n = MAXN_SUB3;
    int m = n - 1;
    vector<tuple<int, int, long long>> edges;
    for(int i = 2; i <= n; ++i) {
        edges.emplace_back(i, rnd.next(1, i - 1), rnd.next(1LL, MAXW));
    }
    print_graph(n, m, edges);
}

// Case 5: Bẫy BFS/Greedy với N max
void genEdgeCase() {
    int n = MAXN_SUB3;
    int m = n;
    vector<tuple<int, int, long long>> edges;
    
    long long total_weight = 0;
    for (int i = 1; i < n; ++i) {
        long long w = 1; // Trọng số nhỏ nhất
        edges.emplace_back(i, i + 1, w);
        total_weight += w;
    }
    // Cạnh trực tiếp có trọng số lớn hơn
    edges.emplace_back(1, n, total_weight + 1);

    print_graph(n, m, edges);
}

// Case 6: Stress test, n và m max, đồ thị ngẫu nhiên liên thông
void genStressCase() {
    int n = MAXN_SUB3;
    int m = MAXM_SUB3;
    vector<tuple<int, int, long long>> edges;
    set<pair<int, int>> existing_edges;

    // Tạo cây khung
    for(int i = 2; i <= n; ++i) {
        int u = i, v = rnd.next(1, i - 1);
        edges.emplace_back(u, v, rnd.next(1LL, MAXW));
        existing_edges.insert({min(u, v), max(u, v)});
    }

    // Thêm cạnh ngẫu nhiên
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
    else if (type == 2) genSpecialCase1(); // Long Chain (long long test)
    else if (type == 3) genSpecialCase2(); // Disconnected
    else if (type == 4) genSpecialCase3(); // Random Tree (sparse test)
    else if (type == 5) genEdgeCase();
    else genStressCase();

    return 0;
}