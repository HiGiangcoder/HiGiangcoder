    #include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
bool d[14][14];
int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 12, "n");
    inf.readSpace();
    int m = inf.readInt(1, n*(n-1)/2, "m");
    inf.readEoln();
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= n; j++) d[i][j] = false;
    }
    for (int i = 0; i < m; i++) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readEoln();
        if(u > v) swap(u,v);
        ensuref(!d[u][v], "u must different for v");
        d[u][v] = true;
    }

    inf.readEof();
}
