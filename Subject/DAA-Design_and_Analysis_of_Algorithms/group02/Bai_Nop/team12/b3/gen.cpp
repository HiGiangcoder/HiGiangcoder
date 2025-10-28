#include "../testlib.h"
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 12;

// Hàm tiện ích để in đồ thị, các cạnh được xáo trộn
void print_graph(int n, const set<pair<int, int>>& edge_set) {
    vector<pair<int, int>> edges(edge_set.begin(), edge_set.end());
    shuffle(edges.begin(), edges.end());
    cout << n << " " << edges.size() << "\n";
    for (const auto& edge : edges) {
        cout << edge.first << " " << edge.second << "\n";
    }
}

// Case 1: Đồ thị ngẫu nhiên, đảm bảo có đường đi
void genNormalCase() {
    int n = rnd.next(8, MAXN);
    set<pair<int, int>> edges;

    // 1. Tạo một đường đi Hamilton từ một hoán vị ngẫu nhiên
    vector<int> p(n);
    iota(p.begin(), p.end(), 1);
    shuffle(p.begin(), p.end());
    for (int i = 0; i < n - 1; ++i) {
        edges.insert({min(p[i], p[i+1]), max(p[i], p[i+1])});
    }

    // 2. Thêm các cạnh ngẫu nhiên
    int m_target = rnd.next(n - 1, n * (n - 1) / 2);
    while (edges.size() < m_target) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n);
        if (u == v) continue;
        edges.insert({min(u, v), max(u, v)});
    }
    print_graph(n, edges);
}

// Case 2: Đồ thị là một đường đi (Path Graph)
void genSpecialCase1() {
    int n = MAXN;
    set<pair<int, int>> edges;
    vector<int> p(n);
    iota(p.begin(), p.end(), 1);
    shuffle(p.begin(), p.end());
    for (int i = 0; i < n - 1; ++i) {
        edges.insert({min(p[i], p[i+1]), max(p[i], p[i+1])});
    }
    print_graph(n, edges);
}

// Case 3: Đồ thị là một chu trình (Cycle Graph)
void genSpecialCase2() {
    int n = MAXN;
    set<pair<int, int>> edges;
    vector<int> p(n);
    iota(p.begin(), p.end(), 1);
    shuffle(p.begin(), p.end());
    for (int i = 0; i < n - 1; ++i) {
        edges.insert({min(p[i], p[i+1]), max(p[i], p[i+1])});
    }
    edges.insert({min(p[n-1], p[0]), max(p[n-1], p[0])});
    print_graph(n, edges);
}

// Case 4: Đồ thị đầy đủ (Complete Graph)
void genSpecialCase3() {
    int n = MAXN;
    set<pair<int, int>> edges;
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            edges.insert({i, j});
        }
    }
    print_graph(n, edges);
}

// Case 5: Không có đường đi - Đồ thị không liên thông
void genSpecialCase4() {
    int n = MAXN;
    set<pair<int, int>> edges;
    int m_target = rnd.next(n, n * (n - 2) / 2);
    // Chỉ thêm cạnh giữa các đỉnh 1..n-1, đỉnh n bị cô lập
    while(edges.size() < m_target) {
        int u = rnd.next(1, n - 1);
        int v = rnd.next(1, n - 1);
        if (u == v) continue;
        edges.insert({min(u, v), max(u, v)});
    }
    print_graph(n, edges);
}

// Case 6: Không có đường đi - Đồ thị hình quả tạ (Dumbbell)
void genSpecialCase5() {
    int n = 12; // Chẵn
    set<pair<int, int>> edges;
    int k = n / 2;
    // Cụm 1: đồ thị đầy đủ
    for(int i = 1; i <= k; ++i)
        for(int j = i + 1; j <= k; ++j)
            edges.insert({i, j});
    // Cụm 2: đồ thị đầy đủ
    for(int i = k + 1; i <= n; ++i)
        for(int j = i + 1; j <= n; ++j)
            edges.insert({i, j});
    // Thêm 1 cạnh cầu nối
    edges.insert({rnd.next(1, k), rnd.next(k + 1, n)});
    print_graph(n, edges);
}

// Case 7: Không có đường đi - Đồ thị hình sao (Star Graph)
void genEdgeCase() {
    int n = rnd.next(5, MAXN);
    set<pair<int, int>> edges;
    int center = rnd.next(1, n);
    for (int i = 1; i <= n; ++i) {
        if (i == center) continue;
        edges.insert({min(i, center), max(i, center)});
    }
    print_graph(n, edges);
}

// Case 8: Stress test, N max, đồ thị gần đầy đủ
void genStressCase() {
    int n = MAXN;
    set<pair<int, int>> edges;

    // 1. Tạo một đường đi Hamilton để đảm bảo có kết quả
    vector<int> p(n);
    iota(p.begin(), p.end(), 1);
    shuffle(p.begin(), p.end());
    for (int i = 0; i < n - 1; ++i) {
        edges.insert({min(p[i], p[i+1]), max(p[i], p[i+1])});
    }

    // 2. Thêm cạnh đến khi gần đầy đủ
    int max_m = n * (n - 1) / 2;
    int m_target = rnd.next(max_m - 5, max_m); // Gần đầy đủ
    while (edges.size() < m_target) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n);
        if (u == v) continue;
        edges.insert({min(u, v), max(u, v)});
    }
    print_graph(n, edges);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int type = atoi(argv[1]);
    int seed = atoi(argv[2]);
    rnd.setSeed(seed);

    if (type == 1) genNormalCase();
    else if (type == 2) genSpecialCase1(); // Path Graph
    else if (type == 3) genSpecialCase2(); // Cycle Graph
    else if (type == 4) genSpecialCase3(); // Complete Graph
    else if (type == 5) genSpecialCase4(); // No Path - Disconnected
    else if (type == 6) genSpecialCase5(); // No Path - Dumbbell
    else if (type == 7) genEdgeCase();     // No Path - Star Graph
    else genStressCase();

    return 0;
}