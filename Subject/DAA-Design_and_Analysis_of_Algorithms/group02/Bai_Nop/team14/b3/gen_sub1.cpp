#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 12;

void genNormalCase() {
    int n = rnd.next(6, MAXN);  // kích thước vừa phải
    int maxM = n * (n - 1) / 2;
    int targetM = rnd.next(n + 1, maxM / 2); // thêm cạnh phụ để đồ thị tự nhiên

    cout << n << " " << targetM << "\n";

    set<pair<int,int>> edges;

    // 1️⃣ Tạo một đường Hamilton ngẫu nhiên
    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 1);
    shuffle(perm.begin(), perm.end()); // random permutation

    for (int i = 0; i < n - 1; i++) {
        int u = perm[i], v = perm[i + 1];
        if (u > v) swap(u, v);
        edges.insert({u, v});
    }

    // 2️⃣ Thêm các cạnh ngẫu nhiên khác để đồ thị tự nhiên
    while ((int)edges.size() < targetM) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n);
        if (u == v) continue;
        if (u > v) swap(u, v);
        edges.insert({u, v});
    }

    // 3️⃣ In ra đồ thị
    for (auto [u, v] : edges)
        cout << u << " " << v << "\n";
}

void genCompleteGraph() {
    int n = rnd.next(5, MAXN);
    int m = n * (n - 1) / 2;
    cout << n << " " << m << "\n";
    for (int u = 1; u <= n; ++u)
        for (int v = u + 1; v <= n; ++v)
            cout << u << " " << v << "\n";
}

void genPathGraph() {
    int n = rnd.next(5, MAXN);
    cout << n << " " << n - 1 << "\n";
    for (int i = 1; i < n; i++)
        cout << i << " " << i + 1 << "\n";
}

void genCycleGraph() {
    int n = rnd.next(5, MAXN);
    cout << n << " " << n << "\n";
    for (int i = 1; i < n; i++)
        cout << i << " " << i + 1 << "\n";
    cout << n << " " << 1 << "\n"; // khép vòng
}

void genDisconnectedGraph() {
    int n = rnd.next(6, MAXN);
    vector<pair<int,int>> edges;
    int split = n / 2;
    for (int i = 1; i < split; i++) edges.push_back({i, i + 1});
    for (int i = split + 1; i < n; i++) edges.push_back({i, i + 1});
    cout << n << " " << (int)edges.size() << "\n";
    for (auto [u, v] : edges) cout << u << " " << v << "\n";
}

void genStarGraph() {
    int n = rnd.next(5, MAXN);
    int center = rnd.next(1, n);
    cout << n << " " << n - 1 << "\n";
    for (int i = 1; i <= n; i++)
        if (i != center) cout << center << " " << i << "\n";
}

void genSpecialCase() {
    int type = rnd.next(1, 5);  // random từ 1..5 (xác suất đều)
    switch (type) {
        case 1: genCompleteGraph(); break;
        case 2: genPathGraph(); break;
        case 3: genCycleGraph(); break;
        case 4: genDisconnectedGraph(); break;
        case 5: genStarGraph(); break;
    }
}

void genEdgeCase() {
    // Edge case 1: chọn ngẫu nhiên giữa "min case" và "max case"
    int choice = rnd.next(1, 2);

    if (choice == 1) {
        // 1️⃣ Trường hợp nhỏ nhất (n = 1 hoặc 2)
        int n = rnd.next(1, 2);
        int m = (n == 1 ? 0 : rnd.next(0, 1));
        cout << n << " " << m << "\n";
        if (m == 1)
            cout << "1 2\n"; // cạnh duy nhất
    } 
    else {
        // 2️⃣ Trường hợp lớn nhất (n = MAXN)
        int n = MAXN;

        // Tạo đồ thị cực đại hoặc cực thưa
        bool dense = rnd.next(0, 1);
        int m;
        set<pair<int,int>> edges;

        if (dense) {
            // Gần đầy đủ: thiếu 1 cạnh
            m = n * (n - 1) / 2 - 1;
            for (int u = 1; u <= n; ++u)
                for (int v = u + 1; v <= n; ++v)
                    edges.insert({u, v});
            // Xóa ngẫu nhiên 1 cạnh
            auto it = next(edges.begin(), rnd.next(0, (int)edges.size() - 1));
            edges.erase(it);
        } else {
            // Gần rời rạc: chỉ có n cạnh
            m = n;
            // Bắt đầu từ một đường Hamilton (đảm bảo liên thông)
            vector<int> p(n);
            iota(p.begin(), p.end(), 1);
            shuffle(p.begin(), p.end());
            for (int i = 0; i < n - 1; i++) {
                int u = p[i], v = p[i + 1];
                if (u > v) swap(u, v);
                edges.insert({u, v});
            }
            // Thêm vài cạnh ngẫu nhiên để đủ m
            while ((int)edges.size() < m) {
                int u = rnd.next(1, n);
                int v = rnd.next(1, n);
                if (u == v) continue;
                if (u > v) swap(u, v);
                edges.insert({u, v});
            }
        }

        cout << n << " " << m << "\n";
        for (auto [u, v] : edges)
            cout << u << " " << v << "\n";
    }
}


void genStressCase() {
    int n = MAXN;                            // kích thước lớn nhất
    int maxM = n * (n - 1) / 2;
    int m = rnd.next(maxM * 3 / 4, maxM);    // đồ thị cực dày, gần đầy đủ

    cout << n << " " << m << "\n";

    // Đảm bảo có ít nhất 1 đường Hamilton thật
    set<pair<int,int>> edges;

    // 1️⃣ Tạo một Hamilton path ngẫu nhiên
    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 1);
    shuffle(perm.begin(), perm.end());

    for (int i = 0; i < n - 1; i++) {
        int u = perm[i], v = perm[i + 1];
        if (u > v) swap(u, v);
        edges.insert({u, v});
    }

    // 2️⃣ Thêm các cạnh ngẫu nhiên khác cho tới khi đạt m
    while ((int)edges.size() < m) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n);
        if (u == v) continue;
        if (u > v) swap(u, v);
        edges.insert({u, v});
    }

    // 3️⃣ In toàn bộ danh sách cạnh
    for (auto [u, v] : edges)
        cout << u << " " << v << "\n";
}


int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int seed = atoi(argv[2]);
    rnd.setSeed(seed);

    int type = (argc > 1) ? atoi(argv[1]) : 1;
    if (type == 1) genNormalCase();
    else if (type == 2) genSpecialCase();
    else if (type == 3) genEdgeCase();
    else genStressCase();
    return 0;
}
