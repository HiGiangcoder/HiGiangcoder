#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000;
const int MAXEDGE = 1e9;
int par[MAXN + 7];

int Find(int x)
{
    if (par[x] == x) return x;
    return par[x] = Find(par[x]);
}

void genNormalCase() {
    int n = rnd.next(10, MAXN);
    int m = rnd.next(n - 1, 200000);
    cout << n << " " << m << "\n";
    for (int i = 1 ; i <= m ; ++i)
    {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n);
        int w = rnd.next(1, MAXEDGE);
        cout << u << " " << v << " " << w << "\n";
    }
}

void genSpecialCase() {
    int n = rnd.next(10, MAXN);
    int m = rnd.next(n - 1, 200000);
    cout << n << " " << m << "\n";
    for (int i = 1 ; i <= m ; ++i)
    {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n);
        int w = 1;
        cout << u << " " << v << " " << w << "\n";
    }
}

void genEdgeCase() {
    int n = MAXN;
    int m = 200000;
    cout << n << " " << m << "\n";

    for (int i = 1 ; i <= m ; ++i)
    {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n);
        int w = MAXEDGE;
        cout << u << " " << v << " " << w << "\n";
    }
}

void genStressCase() {
    int n = MAXN;
    int m = 200000;
    cout << n << " " << m << "\n";
    for (int i = 1 ; i <= m ; ++i)
    {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n);
        int w = MAXEDGE;
        cout << u << " " << v << " " << w << "\n";
    }
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
