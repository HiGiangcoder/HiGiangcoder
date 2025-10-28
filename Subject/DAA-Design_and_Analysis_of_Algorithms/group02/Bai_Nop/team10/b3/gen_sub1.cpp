#include "testlib.h"
#include <iostream>
#include <vector>
#include <set>
#include <utility>
using namespace std;

const int MAXN = 12;

void printEdges(const vector<pair<int,int> >& e) {
    for (size_t i = 0; i < e.size(); i++)
        cout << e[i].first << " " << e[i].second << "\n";
}

void printEdgesSet(const set<pair<int,int> >& e) {
    for (set<pair<int,int> >::iterator it = e.begin(); it != e.end(); ++it)
        cout << it->first << " " << it->second << "\n";
}

void genComplete(int n) {
    cout << n << " " << n * (n - 1) / 2 << "\n";
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            cout << i << " " << j << "\n";
}

void genCycle(int n) {
    cout << n << " " << n << "\n";
    for (int i = 1; i <= n; i++)
        cout << i << " " << (i % n) + 1 << "\n";
}

void genDense(int n) {
    vector<pair<int,int> > e;
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            if (rnd.next(0, 1))
                e.push_back(make_pair(i, j));
    cout << n << " " << e.size() << "\n";
    printEdges(e);
}

void genSparse(int n) {
    int m = rnd.next(n - 1, n + 2);
    set<pair<int,int> > e;
    for (int i = 2; i <= n; i++) {
        int j = rnd.next(1, i - 1);
        e.insert(make_pair(min(i,j), max(i,j)));
    }
    while ((int)e.size() < m) {
        int u = rnd.next(1, n), v = rnd.next(1, n);
        if (u != v)
            e.insert(make_pair(min(u,v), max(u,v)));
    }
    cout << n << " " << e.size() << "\n";
    printEdgesSet(e);
}

void genNoHamilton(int n) {
    int mid = n / 2;
    vector<pair<int,int> > e;
    for (int i = 1; i <= mid; i++)
        for (int j = i + 1; j <= mid; j++)
            if (rnd.next(0, 1)) e.push_back(make_pair(i, j));
    for (int i = mid + 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            if (rnd.next(0, 1)) e.push_back(make_pair(i, j));
    cout << n << " " << e.size() << "\n";
    printEdges(e);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int type = atoi(argv[1]);
    int seed = atoi(argv[2]);
    rnd.setSeed(seed);
    int n = rnd.next(4, MAXN);
    if (type == 1) genComplete(n);
    else if (type == 2) genCycle(n);
    else if (type == 3) genDense(n);
    else if (type == 4) genSparse(n);
    else genNoHamilton(n);
}
