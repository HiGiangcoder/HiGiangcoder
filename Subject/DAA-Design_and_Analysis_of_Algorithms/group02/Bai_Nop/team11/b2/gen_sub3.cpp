#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
int main(int argc, char* argv[]) {
ios::sync_with_stdio(false);
cin.tie(nullptr);
    
    registerGen(argc, argv, 1);
    int n = rnd.next(1000, 100000);
    int m = rnd.next(0,200000);
    cout << n << " " << m << "\n";
    for (int i = 0; i < m; i++) {
        int u = rnd.next(1, n), v = rnd.next(1, n);
        long long w = rnd.next(1, 1000000000);
        cout << u << " " << v << " " << w << "\n";
    }
}
