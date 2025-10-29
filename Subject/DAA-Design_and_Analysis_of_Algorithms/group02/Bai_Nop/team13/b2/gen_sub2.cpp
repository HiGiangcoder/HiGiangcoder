#include "testlib.h"
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

const int MAXN_SUB2 = 1000;
const int MAXM_SUB2 = 10000; // Giảm xuống để tránh timeout
const long long MAX_WEIGHT = 1000000000LL;

// Tạo đồ thị ngẫu nhiên cỡ trung bình 
void genNormalCase() {
    int n = rnd.next(100, MAXN_SUB2);
    int max_possible = min(MAXM_SUB2, n * (n - 1));
    int m = rnd.next(n - 1, max_possible);
    
    cout << n << " " << m << endl;
    
    vector<pair<int, int> > all_edges;
    
    // Tạo đường đi 1->2->...->n
    for (int i = 1; i < n; i++) {
        all_edges.push_back(make_pair(i, i + 1));
    }
    
    // Tạo thêm cạnh ngẫu nhiên
    for (int u = 1; u <= n && (int)all_edges.size() < max_possible; u++) {
        for (int v = 1; v <= n && (int)all_edges.size() < max_possible; v++) {
            if (u != v) {
                all_edges.push_back(make_pair(u, v));
            }
        }
    }
    
    // Xóa trùng lặp (nếu có)
    sort(all_edges.begin(), all_edges.end());
    all_edges.erase(unique(all_edges.begin(), all_edges.end()), all_edges.end());
    
    // Xáo trộn và lấy m cạnh
    shuffle(all_edges.begin(), all_edges.end());
    
    for (int i = 0; i < m; i++) {
        long long w = rnd.next(1LL, MAX_WEIGHT);
        cout << all_edges[i].first << " " << all_edges[i].second << " " << w << endl;
    }
}

// Tạo test với nhiều đường đi ngắn khác nhau
void genSpecialCase() {
    int n = 100; // Giảm n để đảm bảo performance
    int m = min(2000, n * (n - 1) / 2);
    
    cout << n << " " << m << endl;
    
    vector<pair<int, int> > edges;
    
    // Tạo đường đi chính 1->2->3->...->n với trọng số nhỏ
    for (int i = 1; i < n; i++) {
        edges.push_back(make_pair(i, i + 1));
    }
    
    // Thêm các đường đi tắt từ 1 đến các đỉnh gần n
    for (int i = 0; i < m - (n - 1); i++) {
        int u = rnd.next(1, n / 3);
        int v = rnd.next(2 * n / 3, n);
        if (u < v) {
            edges.push_back(make_pair(u, v));
        }
    }
    
    // Nếu chưa đủ m, thêm cạnh ngẫu nhiên
    while ((int)edges.size() < m) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n);
        if (u != v) {
            edges.push_back(make_pair(u, v));
        }
    }
    
    // Chỉ lấy m cạnh đầu
    edges.resize(m);
    
    for (int i = 0; i < m; i++) {
        long long w;
        if (edges[i].first + 1 == edges[i].second) {
            w = rnd.next(1LL, 10LL); // Đường chính - nhỏ
        } else if (edges[i].first == 1 && edges[i].second == n) {
            w = rnd.next(50LL, 100LL); // Đường tắt trực tiếp
        } else {
            w = rnd.next(20LL, MAX_WEIGHT); // Đường khác
        }
        cout << edges[i].first << " " << edges[i].second << " " << w << endl;
    }
}

// Tạo test biên - đồ thị dạng chuỗi với một số cạnh tắt 
void genEdgeCase() {
    int n = MAXN_SUB2;
    int m = min(MAXM_SUB2, 2 * n); // Giới hạn m
    
    cout << n << " " << m << endl;
    
    // Tạo đường đi chính 1->2->...->n
    for (int i = 1; i < n; i++) {
        long long w = rnd.next(1LL, 10LL);
        cout << i << " " << i + 1 << " " << w << endl;
        m--;
    }
    
    // Thêm một số cạnh tắt ngẫu nhiên
    for (int i = 0; i < m; i++) {
        int u = rnd.next(1, n / 2);
        int v = rnd.next(u + 2, n);
        long long w = rnd.next(1LL, MAX_WEIGHT);
        cout << u << " " << v << " " << w << endl;
    }
}

// Tạo test stress - đồ thị lớn đơn giản 
void genStressCase() {
    int n = 1000; // Giảm n để đảm bảo performance
    int m = min(MAXM_SUB2, 5 * n);
    
    cout << n << " " << m << endl;
    
    vector<pair<int, int> > edges;
    
    // Tạo đường đi từ 1 đến n
    for (int i = 1; i < n; i++) {
        edges.push_back(make_pair(i, i + 1));
    }
    
    // Thêm cạnh ngẫu nhiên
    while ((int)edges.size() < m) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n);
        if (u != v) {
            edges.push_back(make_pair(u, v));
        }
    }
    
    // Chỉ lấy m cạnh đầu
    edges.resize(m);
    
    for (int i = 0; i < m; i++) {
        long long w = rnd.next(1LL, MAX_WEIGHT);
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