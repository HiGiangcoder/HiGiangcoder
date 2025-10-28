#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000;

long long rd(long long l, long long r) {
    return rnd.next(l, r);
}

void genStressCase() {
    int n = rnd.next(99990, 100000), m = rd(199900, 200000);
    int d = rnd.next(1, 9);
    int lim = pow(10, d);
    cout << n << " " << m << "\n";
    int last_x = -1, last_y = -1, last_w = -1;
    for (int i = 1; i <= m; i++)
        if (rnd.next(0, 1) && i > 1) {
            cout << last_x << " " << last_y << " " << rnd.next(1, lim) << "\n";
        }
        else {
            last_x = rnd.next(1, n);
            last_y = rnd.next(1, n);
            last_w = rnd.next(1, lim);
            cout << last_x << " " << last_y << " " << last_w << "\n";
        }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int type = atoi(argv[1]);
    int seed = atoi(argv[2]);
    rnd.setSeed(seed);
    genStressCase();
    return 0;
}
