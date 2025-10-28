#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 12;
const int MAX = 1e9;
bool check[13][13];

void genNormalCase() {
    int n = rnd.next(1, MAXN);
    int m = rnd.next(1, max(n * (n - 1) / 2,1));
    cout << n << " " << m << "\n";
    if(m >= 3 * (n - 1)){
        for(long i = 1; i <= n - 1; i++){
            int x = rnd.next(1, MAX);
            cout << i <<" " << i + 1 <<"\n";
            check[i][i+1] = true;
            check[i+1][i] = true;
            m--;
        }
    }
    while(m--){
        int l = rnd.next(1, n);
        int r = rnd.next(1, n);
        if(check[l][r] == false){
        cout << l << " " << r << "\n";
        check[l][r] = true;
        check[r][l] = true;
        }
        else m++;
    }
}

void genSpecialCase() {
    int n = rnd.next(2, MAXN);
    int m = n * (n - 1) / 2;
    cout << n <<" " << m <<"\n";
    for(long i = 1; i <= n; i++){
        for(long j = i + 1; j <= n; j++){
            cout << i <<" "<< j <<"\n"; 
        }
    }
}
void genEdgeCase() {
    int n = rnd.next(1, MAXN);
    int m = n;
    cout << n << " " << m << "\n";
    long i = 0;
    while(m--){
        i++;
        if(m == 0)
        cout << i <<" "<<1<< "\n";
        else    cout << i <<" " << i + 1<<"\n";
    }
}

void genStressCase() {
    int n = rnd.next(1, MAXN);
    int m = rnd.next(1, max(n * (n - 1) / 2,1));
    cout << n << " " << m << "\n";
    if(m >= 3*(n - 1)){
        for(long i = 1; i <= n - 1; i++){
            cout << i <<" " << i + 1 <<"\n";
            check[i][i+1] = true;
            m--;
        }
    }
    while(m--){
    long i = rnd.next(0, 1);

    if(i == 1){
    int l = rnd.next(1, n);
    int r = l;
    if(check[l][r] == false){
        cout << l << " " << r << "\n";
        check[l][r] = true;
        }
    else m++;
    }
    
    else{
    int l = rnd.next(1, n);
    int r = rnd.next(1, n);

    if(check[l][r] == false){
        cout << l << " " << r << "\n";
        check[l][r] = true;
    }
    else m++;
        }

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
