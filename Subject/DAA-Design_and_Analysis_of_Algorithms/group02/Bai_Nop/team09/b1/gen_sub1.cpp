#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000;

void genNormalCase() { // type 1
    int d = rnd.next(1, 3);
    int n = pow(10, d);
    n = rnd.next(max(1, n - 10), n);
    d = rnd.next(1, 5);
    int lim = pow(10, d);
    cout << n << "\n";
    for (int i = 1; i <= n; i++) {
        cout << rnd.next(-lim, lim);
        if (i < n) cout << " ";
    }
    cout << "\n";
}

void genEdgeCase() {
    if (rnd.next(0, 1) == 0) {
        int lim = 1e5;
        int n = 1e3;
        cout << n << "\n";
        for (int i = 1; i <= n; i++) {
            cout << rnd.next(lim - 100, lim);
            if (i < n) cout << " ";
        }
        cout << "\n";
    }
    else {
        int lim = -1e5;
        int n = 1e3;
        cout << n << "\n";
        for (int i = 1; i <= n; i++) {
            cout << rnd.next(lim, lim + 100);
            if (i < n) cout << " ";
        }
        cout << "\n";
    }
}

void genStressCase() {
    int n = 1e3;
    n = rnd.next(max(1, n - 10), n);
    int d = rnd.next(1, 5);
    int lim = pow(10, d);
    cout << n << "\n";
    for (int i = 1; i <= n; i++) {
        cout << rnd.next(-lim, lim);
        if (i < n) cout << " ";
    }
    cout << "\n";

}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int type = atoi(argv[1]);
    int seed = atoi(argv[2]);
    rnd.setSeed(seed);
    
    if (type == 1) genNormalCase();
    else if (type == 2) genEdgeCase();
    else genStressCase();
    return 0;
}
