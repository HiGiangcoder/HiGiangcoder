#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

const int MAXW = 1e9;
const int MAXN = 100000;
const int MAXM = 200000;

void genNormalCase() {
    int n = rnd.next(20000, MAXN);
    int m = rnd.next(n, MAXM/2);
    cout << n << " " << m << "\n";
    for (int i = 0; i < m; i++) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n);
        if (u == v) v = (v % n) + 1;
        cout << u << " " << v << " " << rnd.next(1, (int)1e6) << "\n";
    }
}

void genEdgeCase() {
    int n = MAXN, m = MAXM;
    cout << n << " " << m << "\n";
    for (int i = 0; i < m; i++) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n);
        if (u == v) v = (v % n) + 1;
        cout << u << " " << v << " " << MAXW << "\n";
    }
}

void genSpecialCase() {
    int n = MAXN / 2;
    int m = n;
    cout << n << " " << m << "\n";
    for (int i = 0; i < m; i++) {
        int u = rnd.next(2, n);
        int v = rnd.next(2, n);
        cout << u << " " << v << " " << rnd.next(1, 1000) << "\n";
    }
}

void genStressCase() {
    using ll = long long;
    const ll N_MAX = 100000;
    const ll M_MAX = 200000;
    const int C_MAX = 999999999;

    struct Hen {
        int from, to, cost;
    };

    int n = -1, m = -1;
    vector<Hen> hens;
    bool shuffle_vertices = false;


    /*
        Rough sketch of the graph:
            1 >>(10^9)>> 3>>.
            ^            ^  v
        (0)           (0) v   5 >(10^9)/4> 7>>.
            ^            ^ (0)  ^            ^  |
            0 >>>(1)>>>> 2   \ (0)          (0) |
            \                \ ^            ^ (0)
            .>>>(10^9)/2>>>>>>4 >>>(1)>>>> 6   \
                                    \             \
                                    .>>>(10^9)/8>>>>>>8 ...
    */
        int k = 15;
        int repeat = min((int)(N_MAX / (4 * k)), (int)(M_MAX / (6 * k)));
        n = 4 * k * repeat;
        m = 6 * k * repeat - 2;
        int s = 0;
        int t = n - 1;
        for (int i = 0; i < repeat; i++)
            for (int j = 0; j < k; j++) {
                int base = (i * k + j) * 4;
                hens.push_back({base, base + 1, 0});
                hens.push_back({base, base + 2, 1});
                hens.push_back({base + 1, base + 3, (int)(C_MAX >> (j * 2))});
                hens.push_back({base + 2, base + 3, 0});
                if (base + 4 < n) {
                    hens.push_back({base, base + 4, (int)(C_MAX >> (j * 2 + 1))});
                    hens.push_back({base + 3, base + 4, 0});
                }
            }
        shuffle_vertices = true;
        
        shuffle(hens.begin(), hens.end(), std::mt19937(rnd.next(1, INT_MAX)));
        if (shuffle_vertices) {
            vector<int> perm(n);
            iota(perm.begin(), perm.end(), 0);
            shuffle(perm.begin(), perm.end(), std::mt19937(rnd.next(1, INT_MAX)));
            for (auto &i : hens) {
                i.from = perm[i.from];
                i.to = perm[i.to];
            }
            s = perm[s];
            t = perm[t];
        }

        cout << n << " " << m << "\n";

        for (auto &e : hens)
            cout << e.from+1 << " " << e.to+1 << " " << e.cost+1 << "\n";
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    if (argc < 3) {
        cerr << "Usage: ./gen_sub3 <seed> <type(1=Normal,2=Edge,3=Special,4=Stress)>\n";
        return 1;
    }

    int seed = atoi(argv[1]);
    int type = atoi(argv[2]);
    rnd.setSeed(seed);

    if (type == 1) genNormalCase();
    else if (type == 2) genEdgeCase();
    else if (type == 3) genSpecialCase();
    else genStressCase();

    return 0;
}
