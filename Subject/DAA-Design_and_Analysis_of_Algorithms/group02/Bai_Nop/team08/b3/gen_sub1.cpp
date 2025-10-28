#include "testlib.h"
#include <bits/stdc++.h>
#define pii pair < int , int >
#define fi first
#define se second
using namespace std;

const int MAXN = 12;
map < pii , int > mp;

void genNormalCase() {
    int n = rnd.next(2, MAXN);
    int m = rnd.next(1, n * (n - 1) / 2);
    cout << n << " " << m << "\n";
    mp.clear();
    vector < pii > edge;
    while (edge.size() < m)
    {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n);
        if (u > v) swap(u, v);
        if (mp[pii(u, v)] == 0 && u != v)
        {
            mp[pii(u, v)] = 1;
            edge.push_back(pii(u, v));
        }
    }
    for (pii x : edge) cout << x.fi << " " << x.se << "\n";
}

void genSpecialCase() {
    int n = rnd.next(5, MAXN);
    int m = n;
    cout << n << " " << m << "\n";
    vector < int > vi;
    for (int i = 1 ; i <= n ; ++i) vi.push_back(i);
    shuffle(vi.begin(), vi.end());
    vector < pii > edge;
    for (int i = 0 ; i < n - 1 ; ++i)
    {
        edge.push_back(pii(vi[i], vi[i + 1]));
    }
    edge.push_back(pii(vi.back(), vi.front()));
    for (pii x : edge) cout << x.fi << " " << x.se << "\n";
}

void genEdgeCase() {
    int n = rnd.next(5, MAXN);
    int m = n - 1;
    cout << n << " " << m << "\n";
    vector < int > vi;
    for (int i = 1 ; i <= n ; ++i) vi.push_back(i);
    shuffle(vi.begin(), vi.end());
    vector < pii > edge;
    for (int i = 0 ; i < n - 1 ; ++i)
    {
        edge.push_back(pii(vi[i], vi[i + 1]));
    }
    for (pii x : edge) cout << x.fi << " " << x.se << "\n";
}

void genStressCase() {
    int n = MAXN;
    int m = n * (n - 1) / 2;
    cout << n << " " << m << "\n";
    mp.clear();
    vector < pii > edge;
    for (int i = 1 ; i <= n ; ++i)
        for (int j = i + 1 ; j <= n ; ++j)
            edge.push_back(pii(i, j));
    for (pii x : edge) cout << x.fi << " " << x.se << "\n";
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
