#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    // Đọc input
    int n = inf.readInt();
    int m = inf.readInt();

    vector<tuple<int,int,long long>> edges(m);
    for(int i = 0; i < m; i++){
        int u = inf.readInt();
        int v = inf.readInt();
        long long w = inf.readInt();
        edges[i] = {u, v, w};
    }

    // Đọc output chuẩn và output thí sinh
    long long correct = ans.readLong();
    long long contestant = ouf.readLong();

    // So sánh
    if(correct != contestant) {
        quitf(_wa, "Expected %lld, found %lld", correct, contestant);
    }

    quitf(_ok, "Output correct");
}
