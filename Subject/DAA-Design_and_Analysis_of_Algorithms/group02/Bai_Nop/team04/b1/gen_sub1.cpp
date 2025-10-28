#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000;
const int MAX_VAL = 1e5;

int forcedSign = 0;

void genNormalCase() {
    int n = rnd.next(1, MAXN);
    cout << n << "\n";
    for (int i = 0; i < n; i++)
        cout << rnd.next(-MAX_VAL, MAX_VAL) << " \n"[i == n - 1];
}

void genSpecialCase() {
    int n = MAXN;
    cout << n << '\n';
    vector<int> a;
    for (int i = 1; i <= n / 2; i++) {
        int x = rnd.next(-MAX_VAL, MAX_VAL);
        a.push_back(x);
        a.push_back(-x);
    }
    shuffle(a.begin(), a.end(), std::mt19937(rnd.next(1, INT_MAX)));
    for (int i = 0; i < n; i++)
        cout << a[i] << " \n"[i == n - 1];
}

void genEdgeCase() {
    cout << 1 << '\n' << forcedSign * MAX_VAL << '\n';
}

void genEdgeCase2() {
    int n = MAXN;
    cout << n << '\n';
    for (int i = 0; i < n; i++)
        cout << forcedSign * MAX_VAL << " \n"[i == n - 1];
}

void genStressCase() {
    int n = MAXN;
    cout << n << '\n';
    int currentSign = forcedSign ? forcedSign : (rnd.next(0, 1) ? 1 : -1);
    for (int i = 0; i < n; i++) {
        int tmp = rnd.next(0, 2);
        if (!tmp) cout << currentSign * MAX_VAL;
        else cout << rnd.next(-MAX_VAL, MAX_VAL);
        cout << " \n"[i == n - 1];
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int type = atoi(argv[1]);
    int seed = atoi(argv[2]);
    rnd.setSeed(seed);
    forcedSign = atoi(argv[3]);


    if (type == 1) genNormalCase();
    else if (type == 2) genSpecialCase();
    else if (type == 3) genEdgeCase();
    else if (type == 4) genEdgeCase2();
    else genStressCase();

    return 0;
}

