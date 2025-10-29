#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000;

void genNormalCase() {
    int n = rnd.next(1001,MAXN);
    cout << n << '\n';
    for(int i=0;i<n;++i){
        int x = rnd.next(-100000, 100000);
        cout << x << " \n"[i == n-1];
    }



}

void genSpecialCase() {
    int n = MAXN;

    cout << n << '\n';

    int p = rnd.next(0,1);

    for(int i=0;i<n;++i){
        cout << (100000 * (p?-1:1)) << " \n"[i == n-1];
    }

}

void genEdgeCase() {
    int n = (rnd.next(0,1) ? 1001 : MAXN);
    cout << n << '\n';

    for(int i=0;i<n;++i){
        cout << 100000 * (rnd.next(0,1)?1:-1) << " \n"[i == n-1];
    }




}

void genStressCase() {
    int n = MAXN;

    cout << n << '\n';
    for(int i=0;i<n;++i){
        cout << rnd.next(-100000, 100000) << " \n"[i == n-1];
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