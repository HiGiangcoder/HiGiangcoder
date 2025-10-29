#include "testlib.h"
#include <iostream>

#define MAX_A (int)1e9 + 7
using namespace std;

#define endl "\n"
// Trường hợp thông thường: đồ thị cỡ vừa đầy đủ
void genNormalCase() {
   int n = 1000;
    int m = 200000;
    cout << n << " " << m << "\n";
    
    // Backbone với trọng số cực lớn
    for (int i = 1; i < n; ++i) {
        cout << i << " " << i + 1 << " " << rnd.next(900000000, 1000000000) << "\n";
    }
    
    // Shortcut với trọng số siêu nhỏ - tạo nhiều decrease-key
    int remaining = m - (n - 1);
    for (int i = 0; i < remaining; ++i) {
        int u = rnd.next(1, 100);
        int v = rnd.next(200, n);
        int w = rnd.next(1, 1000);  // Trọng số rất nhỏ so với backbone
        cout << u << " " << v << " " << w << "\n";
    } 
}

// Trường hợp đặc biệt: Kiểm tra full đồ thị mới tìm được mix (Kill time)
void genSpecialCase() {
  int n = 1000;
    int m = 200000;
    cout << n << " " << m << "\n";
    
    set<pair<int, int>> edges;
    
    // Đảm bảo đồ thị liên thông với trọng số lớn
    for (int i = 1; i < n; ++i) {
        edges.insert({i, i + 1});
        cout << i << " " << i + 1 << " " << rnd.next(500000000, 1000000000) << "\n";
    }
    
    // Thêm cạnh ngẫu nhiên với trọng số đa dạng
    while (edges.size() < m) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n);
        if (u != v && !edges.count({min(u,v), max(u,v)})) {
            edges.insert({min(u,v), max(u,v)});
            // Trọng số từ rất nhỏ đến rất lớn
            int w = rnd.next(1, 1000000000);
            cout << u << " " << v << " " << w << "\n";
        }
    } 
}

// Trường hợp biên: Đồ thị chỉ có đúng 1 đường đi 1->n
void genEdgeCase() {
    int n = 1000;
    int m = 200000;

    cout << n << " " << m << endl;
    for(int i = 2; i <= n; ++i){
        --m;
        cout << i - 1 << " " << i << " " << 1 << endl;
    } 
    
    for (int u = 1; u <= n - 2 && m > 0; ++u) {
        int limit = min(n, u + rnd.next(10, 50)); 
        for (int v = u + 1; v <= limit && m > 0; ++v, --m) {
            int w = 2 + (v - u) % 3; 
            cout << u << " " << v << " " << w << endl;
        }
    }
    
    while (m--) {
        int u = rnd.next(1, n - 1);
        int v = rnd.next(u + 1, n);
        int w = rnd.next(1, 5);
        cout << u << " " << v << " " << w << endl;
    }
}

// Trường hợp cực đại: n, m lớn nhất trong subtask

void genStressCase() {
    int n = 1000;
    int m = 200000;
    cout << n << " " << m << "\n";
    
    set<pair<int, int>> edges;
    
    // Tạo đồ thị gần đầy đủ (dense graph)
    // Mỗi đỉnh kết nối đến ~200 đỉnh khác
    for (int u = 1; u <= n && edges.size() < m; ++u) {
        // Kết nối đến các đỉnh gần (50 đỉnh mỗi bên)
        for (int v = max(1, u - 50); v <= min(n, u + 50) && edges.size() < m; ++v) {
            if (u != v && !edges.count({min(u, v), max(u, v)})) {
                cout << u << " " << v << " " << rnd.next(1, 1000) << "\n";
                edges.insert({min(u, v), max(u, v)});
            }
        }
        
        // Kết nối ngẫu nhiên đến các đỉnh xa
        for (int k = 0; k < 150 && edges.size() < m; ++k) {
            int v = rnd.next(1, n);
            if (u != v && abs(u - v) > 50 && !edges.count({min(u, v), max(u, v)})) {
                cout << u << " " << v << " " << rnd.next(1, 100) << "\n";
                edges.insert({min(u, v), max(u, v)});
            }
        }
    }
    
    // Nếu vẫn thiếu, thêm cạnh ngẫu nhiên
    while (edges.size() < m) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n);
        if (u != v && !edges.count({min(u, v), max(u, v)})) {
            cout << u << " " << v << " " << rnd.next(1, 1000000) << "\n";
            edges.insert({min(u, v), max(u, v)});
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