#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000;
const int MAXVAL = 1e5;

void genNormalCase() {
    int n = rnd.next(100, MAXN);
    cout << n << '\n';
    for (int i=0;i< n;i++ )
        cout << rnd.next(-100000, 100000) << " \n"[i==n-1];
}

void genSpecialCase(int s) {
    if (s % 3 == 0){
        int n = rnd.next(100, 500);
        cout << n << '\n';
        for (int i=0;i< n;i++ ) 
            cout << 36 + (s^1) << " \n"[i==n-1];
    }
    else if (s % 3 == 1){
        int n = rnd.next(100, 500);
        cout << n << '\n';
        for (int i=0;i< n;i++ )
            cout << rnd.next(-1, 1) << " \n"[i==n-1];
    }
    else{
        int n = 1;
        cout << n << '\n';
        cout << MAXVAL - s << '\n';
    }
}

void genEdgeCase(int s) {
    int n = MAXN;
    cout << n << "\n";
    if (s % 2 == 0){
        for (int i=0;i< n;i++ )
            cout << MAXVAL - (s % 3) << " \n"[i==n-1];
    }
    else {
        for (int i=0;i< n;i++ )
            cout << -MAXVAL + (s % 3) << " \n"[i==n-1];
    }
}

void genStressCase(int s) {
    int n = MAXN;
    cout << n << "\n";
    if (s % 3 == 0){
        for (int i=0;i< n;i++ ) 
            cout << rnd.next(-100000,100000) << " \n"[i==n-1];
    }
    else if (s % 3 == 1){
        for (int i=0;i< n;i++ )
            cout << rnd.next(-100000, 0) << " \n"[i==n-1];
    }
    else{
        for (int i=0;i < n;i++ )
            cout << rnd.next(0, 100000) << " \n"[i==n-1];
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int type = atoi(argv[1]);
    int seed = atoi(argv[2]);
    rnd.setSeed(seed);
    
    if (type == 1) genNormalCase();
    else if (type == 2) genSpecialCase(seed);
    else if (type == 3) genEdgeCase(seed);
    else genStressCase(seed);
    return 0;
}
