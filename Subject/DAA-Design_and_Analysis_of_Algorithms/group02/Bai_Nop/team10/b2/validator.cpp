#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main() {
    registerValidation();
    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 200000, "m");
    inf.readEoln(); 
    for(int i = 1;i<=m;++i){
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readSpace();
        int w = inf.readInt(1, 1e9, "w");
        // if(i != m)
            inf.readEoln();
    }
    inf.readEof();
}
