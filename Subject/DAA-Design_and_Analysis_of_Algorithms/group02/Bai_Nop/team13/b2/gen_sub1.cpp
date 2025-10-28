#include "testlib.h"
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

const int MAXN_SUB1 = 10;
const int MAXM_SUB1 = 20;
const long long MAX_WEIGHT = 1000000000LL;

// Tạo đồ thị ngẫu nhiên nhỏ
void genNormalCase() {
    int n = rnd.next(2, MAXN_SUB1);
    int m = rnd.next(1, min(MAXM_SUB1, n * (n - 1)));
    
    cout << n << " " << m << endl;
    
    vector<pair<int, int> > all_edges;
    
    // Tạo tất cả cạnh có thể
    for (int u = 1; u <= n; u++) {
        for (int v = 1; v <= n; v++) {
            if (u != v) {
                all_edges.push_back(make_pair(u, v));
            }
        }
    }
    
    // Xáo trộn và lấy m cạnh đầu tiên
    shuffle(all_edges.begin(), all_edges.end());
    
    for (int i = 0; i < m; i++) {
        long long w = rnd.next(1LL, 10LL);
        cout << all_edges[i].first << " " << all_edges[i].second << " " << w << endl;
    }
}

// Tạo test đặc biệt với trọng số cố định 
void genSpecialCase() {
    int n = rnd.next(5, MAXN_SUB1);
    int m = rnd.next(n - 1, min(MAXM_SUB1, n * (n - 1)));
    
    cout << n << " " << m << endl;
    
    vector<pair<int, int> > edges;
    
    // Tạo đường đi 1->2->3->...->n
    for (int i = 1; i < n; i++) {
        edges.push_back(make_pair(i, i + 1));
    }
    
    // Tạo thêm cạnh ngẫu nhiên
    vector<pair<int, int> > all_edges;
    for (int u = 1; u <= n; u++) {
        for (int v = 1; v <= n; v++) {
            if (u != v) {
                all_edges.push_back(make_pair(u, v));
            }
        }
    }
    
    shuffle(all_edges.begin(), all_edges.end());
    
    // Thêm cho đủ m cạnh (không trùng)
    for (int i = 0; i < (int)all_edges.size() && (int)edges.size() < m; i++) {
        bool exists = false;
        for (int j = 0; j < (int)edges.size(); j++) {
            if (edges[j] == all_edges[i]) {
                exists = true;
                break;
            }
        }
        if (!exists) {
            edges.push_back(all_edges[i]);
        }
    }
    
    // Trọng số cố định
    long long fixed_weight = 42;
    for (int i = 0; i < m; i++) {
        cout << edges[i].first << " " << edges[i].second << " " << fixed_weight << endl;
    }
}

// Tạo test biên - đồ thị gần như đầy đủ 
void genEdgeCase() {
    int n = MAXN_SUB1;
    int max_possible_edges = n * (n - 1);
    int m = min(MAXM_SUB1, max_possible_edges);
    
    cout << n << " " << m << endl;
    
    vector<pair<int, int> > all_edges;
    
    // Tạo tất cả cạnh có thể
    for (int u = 1; u <= n; u++) {
        for (int v = 1; v <= n; v++) {
            if (u != v) {
                all_edges.push_back(make_pair(u, v));
            }
        }
    }
    
    // Lấy ngẫu nhiên m cạnh
    shuffle(all_edges.begin(), all_edges.end());
    
    for (int i = 0; i < m; i++) {
        long long w = (i % 2 == 0) ? 1LL : MAX_WEIGHT;
        cout << all_edges[i].first << " " << all_edges[i].second << " " << w << endl;
    }
}

// Tạo test stress - không có đường đi từ 1 đến n 
void genStressCase() {
    int n = MAXN_SUB1;
    int m = MAXM_SUB1;
    
    cout << n << " " << m << endl;
    
    vector<pair<int, int> > edges;
    
    // Tạo 2 thành phần liên thông: {1} và {2,3,...,n}
    // Chỉ tạo cạnh trong thành phần {2,3,...,n}
    for (int u = 2; u <= n; u++) {
        for (int v = u + 1; v <= n; v++) {
            if (rnd.next(0, 1) == 0) {
                edges.push_back(make_pair(u, v));
            } else {
                edges.push_back(make_pair(v, u));
            }
        }
    }
    
    // Thêm cạnh ngẫu nhiên trong thành phần {2,...,n} cho đủ m
    while ((int)edges.size() < m) {
        int u = rnd.next(2, n);
        int v = rnd.next(2, n);
        if (u != v) {
            edges.push_back(make_pair(u, v));
        }
    }
    
    // Chỉ lấy m cạnh đầu tiên
    for (int i = 0; i < m; i++) {
        long long w = rnd.next(1LL, 100LL);
        cout << edges[i].first << " " << edges[i].second << " " << w << endl;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <type> <seed>" << endl;
        return 1;
    }
    
    int type = atoi(argv[1]);
    int seed = atoi(argv[2]);
    rnd.setSeed(seed);
    
    if (type == 1) genNormalCase();
    else if (type == 2) genSpecialCase();
    else if (type == 3) genEdgeCase();
    else genStressCase();
    
    return 0;
}