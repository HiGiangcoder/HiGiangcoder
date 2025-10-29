#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000;
const int MAX = 1e9;
void genNormalCase() {
    int n = rnd.next(1, MAXN);
    int m = rnd.next(1, 200000);
    cout << n << " " << m << "\n";
    if(m >= n - 1){
        for(long i = 1; i <= n - 1; i++){
            int x = rnd.next(1, MAX);
            cout << i <<" " << i + 1 <<" " << x<<"\n";
            m--;
        }
    }
      while(m--){
        int l = rnd.next(1, n);
        int r = rnd.next(1, n);
        int x = rnd.next(1, MAX);
        cout << l << " " << r <<" " << x << "\n";
    }
}

void genSpecialCase() {
    int n = rnd.next(1, MAXN);
    int m = rnd.next(1, 200000);
    cout << n << " " << m << "\n";
    if(m >= n - 1){
        for(long i = 1; i <= n - 1; i++){
            int x = rnd.next(1, MAX);
            cout << i <<" " << i + 1 <<" " << x<<"\n";
            m--;
        }
    }
    while(m--){
    long i = rnd.next(0, 2);
    if(i == 1 and m >= 2){
    int l = rnd.next(1, n);
    int r = rnd.next(1, n);
    int x = rnd.next(1, n);
    cout << l << " " << r <<" " << x << "\n";
    cout << l << " " << r <<" " << min(x+1, MAX) << "\n";
    m--;
    }
    else if(i == 2){
    int l = rnd.next(1, n);
    int r = l;
    int x = rnd.next(1, n);
    cout << l << " " << r <<" " << x << "\n";
    }
    else{
    int l = rnd.next(1, n);
    int r = rnd.next(1, n);
    int x = rnd.next(1, MAX);
    cout << l << " " << r <<" " << x << "\n";
        }
    }
}

void genEdgeCase() {
    int n = rnd.next(1, MAXN);
    int m = n;
    cout << n << " " << m << "\n";
    if(m >= n - 1){
        for(long i = 1; i <= n - 1; i++){
            int x = rnd.next(1, MAX);
            cout << i <<" " << i + 1 <<" " << x<<"\n";
            m--;
        }
    }
    long i = 0;
      while(m--){
        i++;
        if(m == 0)
        cout << i <<" "<< 1 <<" " << MAX << "\n";
        else    cout << i <<" " << i + 1 << " "<< MAX <<"\n";
    }
}

void genStressCase() {
    int n = rnd.next(1, MAXN);
    int m = rnd.next(1, 200000);
    cout << n << " " << m << "\n";
    if(m >= n - 1){
        for(long i = 1; i <= n - 1; i++){
            int x = rnd.next(1, MAX);
            cout << i <<" " << i + 1 <<" " << x<<"\n";
            m--;
        }
    }
    while(m--){
        int l = rnd.next(1, n);
        int r = l;
        int x = MAX;
        cout << l << " " << r <<" " << x << "\n";
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
