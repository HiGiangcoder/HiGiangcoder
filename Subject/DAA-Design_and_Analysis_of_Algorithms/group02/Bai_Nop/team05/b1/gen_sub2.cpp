#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000;

// Hàm sinh các số trong 1 dòng, space giữa các số, không space thừa cuối dòng
void printArray(const vector<int>& arr) {
    for (size_t i = 0; i < arr.size(); i++) {
        cout << arr[i];
        if (i + 1 < arr.size()) cout << " ";
    }
    cout << endl;
}

void genNormalCase() {
    int n = rnd.next(1, MAXN);
    cout << n << endl;
    vector<int> a(n);
    for (int i = 0; i < n; i++) a[i] = rnd.next(-100000, 100000);
    printArray(a);
}

void genSpecialCase() {
    int n = MAXN;
    cout << n << endl;
    vector<int> a(n);
    for (int i = 0; i < n; i++) a[i] = rnd.next(-100000, 100000);
    printArray(a);
}

void genEdgeCase() {
    int n = MAXN;
    cout << n << endl;
    vector<int> a(n);
    for (int i = 0; i < n; i++) a[i] = -100000;
    printArray(a);
}

void genStressCase() {
    int n = rnd.next(1, 100000);
    cout << n << endl;
    vector<int> a(n);
    for (int i = 0; i < n; i++) a[i] = 100000;
    printArray(a);
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
