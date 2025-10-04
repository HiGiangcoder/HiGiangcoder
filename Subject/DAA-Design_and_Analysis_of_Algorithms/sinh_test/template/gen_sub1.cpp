#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000;

void genNormalCase() {
    int n = rnd.next(10, MAXN);
    int q = rnd.next(5, MAXN);
    cout << n << " " << q << "\n";
    for (int i=0;i<n;i++) cout << rnd.next(-100, 100) << " \n"[i==n-1];
    while(q--){
        int l = rnd.next(1, n);
        int r = rnd.next(l, n);
        cout << l << " " << r << "\n";
    }
}

void genSpecialCase() {
    int n = rnd.next(5, 10);
    int q = rnd.next(5, 10);
    cout << n << " " << q << "\n";
    for (int i=0;i<n;i++) cout << 42 << " \n"[i==n-1];
    while(q--){
        int l = rnd.next(1, n);
        int r = rnd.next(l, n);
        cout << l << " " << r << "\n";
    }
}

void genEdgeCase() {
    int n = MAXN;
    int q = MAXN;
    cout << n << " " << q << "\n";
    for (int i=0;i<n;i++) cout << (i%2==0?i:-i) << " \n"[i==n-1];
    for (int i=1;i<=q;i++) cout << i << " " << n << "\n";
}

void genStressCase() {
    int n = MAXN;
    int q = MAXN;
    cout << n << " " << q << "\n";
    for (int i=0;i<n;i++) cout << rnd.next(-1000000,1000000) << " \n"[i==n-1];
    for (int i=0;i<q;i++){
        int l = rnd.next(1,n);
        int r = rnd.next(l,n);
        cout << l << " " << r << "\n";
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int seed = atoi(argv[1]);
    rnd.setSeed(seed);

    int type = (argc > 1) ? atoi(argv[1]) : 1;
    if (type == 1) genNormalCase();
    else if (type == 2) genSpecialCase();
    else if (type == 3) genEdgeCase();
    else genStressCase();
    return 0;
}
