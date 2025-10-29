#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
// #define int long long
const int MAXN = 10;
const int MAXW = 1e9;
void genNormalCase() {
    int n = rnd.next(3, MAXN);
    int m = rnd.next(n, 20);
    cout << n << ' '<<m << "\n";
    
    for(int i = 1;i<=m;++i){
        cout << rnd.next(1,n) << ' ' << rnd.next(1,n) << ' '<<rnd.next(1, MAXW) << "\n";
    }
    
}

void genSpecialCase() {
    int p = rnd.next(0,2);
    if (p == 0){
        int n = rnd.next(3, MAXN);
        int m = rnd.next(n, 20);
        cout << n << ' '<<m << "\n";
        for(int i = 2;i<=n;++i){
            cout << rnd.next(1,i-1) << ' '<< i << ' '<< rnd.next(1, 3) << '\n';
        }
        for(int i = n;i<=m;++i){
            cout << rnd.next(1,n) << ' ' << rnd.next(1,n) << ' '<<rnd.next(1, 3) << "\n";
        }
    } else {
        int n = rnd.next(3, MAXN);
        int m = rnd.next(n, 20);
        cout << n << ' '<<m << "\n";
        for(int i = 3;i<=n;++i){
            cout << rnd.next(2,i-1) << ' '<< i << ' '<< rnd.next(1, 3) << '\n';
        }
        for(int i = n + 1;i<=m;++i){
            cout << rnd.next(1,n) << ' ' << rnd.next(1,n) << ' '<<rnd.next(1, 3) << "\n";
        }
        cout << 1 << ' '<< 2 << ' '<<1<<'\n';
        cout << 1 << ' '<< 2 << ' '<< 2 << '\n';
    }
}

void genEdgeCase() {
    int n = rnd.next(MAXN, MAXN);
    int m = rnd.next(20, 20);
    cout << n << ' '<<m << "\n";
    for(int i = 2;i<=n;++i){
        cout << rnd.next(1,i-1) << ' '<< i << ' '<< rnd.next(1, MAXW) << '\n';
    }
    for(int i = n;i<=m;++i){
        cout << rnd.next(1,n) << ' ' << rnd.next(1,n) << ' '<<rnd.next(1, MAXW) << "\n";
    }
}

void genStressCase() {
    int n = rnd.next(3, MAXN);
    int m = rnd.next(n, 20);
    cout << n << ' '<<m << "\n";
    for(int i = 2;i<=n;++i){
        cout << rnd.next(1,i-1) << ' '<< i << ' '<< rnd.next(1, MAXW) << '\n';
    }
    for(int i = n;i<=m;++i){
        cout << rnd.next(1,n) << ' ' << rnd.next(1,n) << ' '<<rnd.next(1, MAXW) << "\n";
    }
    
}

main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int type = atoi(argv[1]);
    int seed = atoi(argv[2]);
    rnd.setSeed(seed);
    
    if (type == 1) genNormalCase();
    else if (type == 2) genSpecialCase();
    else if (type == 3) genEdgeCase();
    else genStressCase();
    return 0;
}
