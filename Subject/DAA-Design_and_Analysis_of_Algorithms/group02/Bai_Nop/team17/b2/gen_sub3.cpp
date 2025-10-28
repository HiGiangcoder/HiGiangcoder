#include "testlib.h"
#include <iostream>

using namespace std;

const int MAX_N = 100000;
const int MAX_M = 200000;
const int MAX_W = 1000000000;

// Trường hợp thông thường: Kill SPFA
void genNormalCase() {
    int n = 100000;
    int m = 200000;
    cout << n << " " << m << "\n";
    
    // Tạo đồ thị khiến SPFA phải relax nhiều lần
    // Chain chính với cost lớn
    for (int i = 1; i < n; i++) {
        cout << i << " " << i + 1 << " " << 1000000000 << "\n";
    }
    m -= (n - 1);
    
    // Thêm CÀNG NHIỀU cạnh từ đỉnh 1 CÀNG TỐT
    // Ưu tiên số lượng hơn chất lượng
    for (int i = 0; i < m; i++) {
        int u = 1;
        int v = rnd.next(2, n);
        // Cost NHỎ để tạo nhiều cập nhật
        cout << u << " " << v << " " << rnd.next(1, 100) << "\n";
    } 
}

void genEdgeCase() {
 int n = 100000;
    int m = 200000;
    cout << n << " " << m << "\n";
    
    // Tạo hình sao NGƯỢC - nhiều đỉnh nối vào 1 đỉnh cuối
    for (int i = 1; i < n; i++) {
        cout << i << " " << n << " " << 1000000000 << "\n";
    }
    m -= (n - 1);
    
    // Thêm cạnh từ đỉnh 1 với trọng số tăng dần
    // Điều này tạo ra THỨ TỰ XẤU NHẤT cho heap
    for (int i = 0; i < m; i++) {
        int v = rnd.next(2, n - 1);
        int w = 1000000000 - i; // Trọng số giảm dần
        cout << 1 << " " << v << " " << w << "\n";
    } 
}

  
void genStarCase(){
    int n = 100000;
    int m = 200000;
    cout << n << " " << m << "\n";
    
    set<pair<int, int>> edges;
    int used = 0;
    
    // Hình sao khổng lồ từ đỉnh 1
    for (int i = 2; i <= 50000 && used < m; ++i) {
        cout << 1 << " " << i << " " << rnd.next(900000000, 1000000000) << "\n";
        edges.insert({1, i});
        used++;
    }
    
    // Mạng lưới giữa các leaf - tạo nhiều decrease-key
    for (int i = 2; i <= 50000 && used < m; ++i) {
        for (int j = 0; j < 3 && used < m; ++j) {
            int v = rnd.next(50001, n);
            if (!edges.count({i, v})) {
                cout << i << " " << v << " " << rnd.next(1, 1000) << "\n";
                edges.insert({i, v});
                used++;
            }
        }
    }
    
    // Điền đủ cạnh với trọng số đa dạng
    while (used < m) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n);
        if (u != v && !edges.count({min(u,v), max(u,v)})) {
            cout << u << " " << v << " " << rnd.next(1, 1000000000) << "\n";
            edges.insert({min(u,v), max(u,v)});
            used++;
        }
    } 
}

// Trường hợp cực đại: n, m lớn nhất và trọng số lớn
void genStressCase() {
    int n = 100000;
    int m = 200000;
    int layers = 5;
    int perLayer = n / layers;

    cout << n << " " << m << "\n";
    set<pair<int, int>> edges;

    // Backbone với trọng số lớn
    for (int i = 1; i < n; ++i) {
        cout << i << " " << i + 1 << " " << rnd.next(800000000, 1000000000) << "\n";
        edges.insert({i, i + 1});
    }
    int used = n - 1;

    // Shortcut tập trung - HIỆU QUẢ CAO
    for (int L = 0; L < layers - 1 && used < m; ++L) {
        int startU = L * perLayer + 1;
        int endU = min((L + 1) * perLayer, n);
        int startV = endU + 1;
        int endV = min((L + 2) * perLayer, n);

        // Tập trung vào 500 đỉnh đầu mỗi tầng, mỗi đỉnh 8 connection
        for (int u = startU; u <= min(startU + 500, endU) && used < m; ++u) {
            for (int k = 0; k < 8 && used < m; ++k) {
                int v = rnd.next(startV, min(startV + 500, endV));
                if (!edges.count({u, v})) {
                    cout << u << " " << v << " " << rnd.next(1, 1000) << "\n";
                    edges.insert({u, v});
                    used++;
                }
            }
        }
    }

    // Cạnh xa từ đầu đến cuối đồ thị
    while (used < m) {
        int u = rnd.next(1, n / 20);
        int v = rnd.next(19 * n / 20, n);
        if (!edges.count({u, v})) {
            cout << u << " " << v << " " << rnd.next(1, 100000) << "\n";
            edges.insert({u, v});
            used++;
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int type = atoi(argv[1]);
    if (type == 1) genNormalCase();
    else if (type == 2) genEdgeCase();
    else if(type == 3) genStarCase();
    else genStressCase();
    return 0;
}