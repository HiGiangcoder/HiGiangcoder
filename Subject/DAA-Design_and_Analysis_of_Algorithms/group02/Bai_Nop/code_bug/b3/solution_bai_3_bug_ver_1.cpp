// #pragma GCC optimize("Ofast,unroll-loops")

#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <locale>
#include <map>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <unordered_set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <utility>
#include <valarray>
#include <vector>
#include <cstring>
#include <unordered_map>
#include <cmath>
#include <array>
#include <cassert>
#include <random>
#include <chrono>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<unsigned int> adjmask(max(1, n), 0u);
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        --u; --v;
        if (u >= 0 && v >= 0 && u < n && v < n && u != v) {
            adjmask[u] |= (1u << v);
            adjmask[v] |= (1u << u); // vô hướng
        }
    }

    int FULL = (n == 32 ? -1 : (1 << n)) ; // n ≤ 12 nên 1<<n an toàn
    FULL = (1 << n);

    const int UNVIS = -1, START = -2;

    // par[mask][v] = cha của v trong trạng thái mask, START nếu là điểm bắt đầu
    vector<array<int, 12>> par(1 << n);
    for (int mask = 0; mask < (1 << n); ++mask)
        for (int v = 0; v < 12; ++v) par[mask][v] = UNVIS;

    for (int v = 0; v < n; ++v) par[1 << v][v] = START;

    for (int mask = 1; mask < (1 << n); ++mask) {
        for (int v = 0; v < n; ++v) if (par[mask][v] != UNVIS) {
            unsigned int avail = adjmask[v] & ~((unsigned int)mask);
            while (avail) {
                int u = __builtin_ctz(avail);
                avail &= (avail - 1);
                int nmask = mask | (1 << u);
                if (par[nmask][u] == UNVIS) par[nmask][u] = v;
            }
        }
    }

    int last = -1;
    int fullMask = (1 << n) - 1;
    for (int v = 0; v < n; ++v) if (par[fullMask][v] != UNVIS) { last = v; break; }

    if (last == -1) {
        // cout << -1 << '\n';
        return 0;
    }

    vector<int> path;
    int mask = fullMask, cur = last;
    while (true) {
        path.push_back(cur + 1);
        int p = par[mask][cur];
        if (p == START) break;
        mask ^= (1 << cur);
        cur = p;
    }
    reverse(path.begin(), path.end());
    for (int i = 0; i < (int)path.size(); ++i) {
        if (i) cout << ' ';
        cout << path[i];
    }
    return 0;
}
