#include "testlib.h"
#include <vector>
#include <numeric>
#include <algorithm>
#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    // Đọc input
    int n = inf.readInt();
    int m = inf.readInt();
    set<pair<int, int>> edges;
    for (int i = 0; i < m; i++) {
        int u = inf.readInt();
        int v = inf.readInt();
        edges.insert({u, v});
        edges.insert({v, u});
    }

    // Đọc output của đáp án và của thí sinh
    long long jans_first = ans.readLong();
    long long pans_first;
    try {
        pans_first = ouf.readLong();
    } catch (...) {
        quitf(_wa, "Contestant output is empty or not a number");
    }

    if (jans_first == -1) {
        if (pans_first != -1) {
            quitf(_wa, "Expected -1, but found a path");
        }
        quitf(_ok, "Correctly found no path");
    }

    // Trường hợp có đáp án
    if (pans_first == -1) {
        quitf(_wa, "Found -1, but a path exists");
    }

    vector<int> p;
    p.push_back(pans_first);
    for (int i = 1; i < n; i++) {
        p.push_back(ouf.readInt());
    }

    // 1. Kiểm tra có phải là hoán vị của 1..n không
    vector<int> sorted_p = p;
    sort(sorted_p.begin(), sorted_p.end());
    for (int i = 0; i < n; i++) {
        if (sorted_p[i] != i + 1) {
            quitf(_wa, "Output is not a permutation of 1..n");
        }
    }

    // 2. Kiểm tra các cạnh có tồn tại trong đồ thị không
    for (int i = 0; i < n - 1; i++) {
        if (edges.find({p[i], p[i+1]}) == edges.end()) {
            quitf(_wa, "Path contains non-existent edge %d-%d", p[i], p[i+1]);
        }
    }

    quitf(_ok, "Found a valid Hamiltonian path");
    return 0;
}