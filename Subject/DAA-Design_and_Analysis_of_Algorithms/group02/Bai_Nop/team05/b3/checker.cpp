#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

bool check[15][15];

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();

    // đọc đồ thị
    for(int i = 0; i < m; i++){
        int u = inf.readInt();
        int v = inf.readInt();
        check[u][v] = true;
        check[v][u] = true;
    }

    vector<long long> correct;
    while(!ans.seekEof()) correct.push_back(ans.readLong());

    vector<long long> contestant;
    while(!ouf.seekEof()) contestant.push_back(ouf.readLong());

    cout << "[Checker] Expected: ";
    for(auto x: correct) cout << x << " ";
    cout << "\n[Checker] Contestant: ";
    for(auto x: contestant) cout << x << " ";
    cout << "\n";

    // xử lý trường hợp -1
    if(!contestant.empty() && !correct.empty()) {
        if(contestant[0] == -1 && correct[0] == -1) {
            cout << "[Checker] Both output -1 -> CORRECT\n";
            quitf(_ok, "CORRECT");
        }
        if(contestant[0] != -1 && correct[0] == -1) {
            cout << "[Checker] Expected -1, but contestant output something -> WRONG\n";
            quitf(_wa, "WRONG");
        }
    }

    // nếu output là đường đi hợp lệ
    bool checknode[15] = {};
    for(size_t i = 0; i < contestant.size(); i++) {
        if(contestant[i] < 1 || contestant[i] > n) {
            cout << "[Checker] Node out of range: " << contestant[i] << "\n";
            quitf(_wa, "Node out of range");
        }
        checknode[contestant[i]] = true;
    }

    for(int i = 1; i <= n; i++) {
        if(!checknode[i]) {
            cout << "[Checker] Node missing: " << i << "\n";
            quitf(_wa, "WRONG");
        }
    }

    for(size_t i = 1; i < contestant.size(); i++) {
        if(!check[contestant[i]][contestant[i-1]]) {
            cout << "[Checker] Edge missing: " << contestant[i-1] << " -> " << contestant[i] << "\n";
            quitf(_wa, "WRONG");
        }
    }

    cout << "[Checker] Output correct\n";
    quitf(_ok, "Output correct");
}
