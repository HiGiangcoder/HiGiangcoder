#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000;
const int INF = 1e5;

void genNormalCase() {
    int n = rnd.next(10, MAXN);
    cout << n << "\n";
    for (int i=0;i<n;i++) cout << rnd.next(-100, 100) << " \n"[i==n-1];
}

void genSpecialCase() {
    cout << 1 << '\n' << INF << '\n';
}

void genEdgeCase() {
    int n = MAXN;
    cout << n << "\n";
    for (int i=0;i<n;i++) cout << INF << " \n"[i==n-1];
}

void genStressCase() {
    int n = MAXN;
    cout << n << "\n";
    for (int i=0;i<n;i++) cout << rnd.next(-INF,INF) << " \n"[i==n-1];
}

int main(int argc, char* argv[]) {
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
