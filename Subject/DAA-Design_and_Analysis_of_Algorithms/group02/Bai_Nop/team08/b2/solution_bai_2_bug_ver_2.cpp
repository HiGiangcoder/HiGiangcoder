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

    int n, m; cin >> n >> m;

    vector<vector<pair<int,long long>>> adj(n + 1);
    adj.reserve(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        if (u >= 1 && u <= n) adj[u].push_back({v, w});
    }

    const long long INF = (long long)4e18;
    vector<long long> dist(n + 1, INF);

    using P = pair<long long,int>;
    priority_queue<P, vector<P>, greater<P>> pq;

    dist[1] = 0;
    pq.push({0, 1});

    while (!pq.empty()) {
        auto [du, u] = pq.top(); pq.pop();
        if (du != dist[u]) continue;
        if (u == n) break;
        for (auto [v, w] : adj[u]) {
            if (du + w < dist[v]) {
                dist[v] = du + w;
                pq.push({dist[v], v});
            }
        }
    }

    cout << dist[n];
    // Thiếu trường hợp -1
    return 0;
}
