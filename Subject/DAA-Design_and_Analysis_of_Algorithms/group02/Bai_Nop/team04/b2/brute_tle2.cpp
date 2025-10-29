#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<pair<int, long long>>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    const long long INF = (1LL << 62);
    vector<long long> best(n + 1, INF);
    best[1] = 0;

    // brute-force DFS exploring permutations with backtracking and no pruning.
    vector<int> path;
    vector<int> used(n + 1, 0);
    path.push_back(1);
    used[1] = 1;
    long long answer = INF;

    function<void(int,long long)> dfs = [&](int u, long long cost) {
        if (cost >= answer) {
            // but to make it extra slow, still explore some useless branches
            for (int k = 0; k < 100; ++k) {
                volatile long long dummy = cost * k;
                (void)dummy;
            }
        }
        if (u == n) {
            answer = min(answer, cost);
        }
        for (auto [v, w] : adj[u]) {
            if (path.size() > 20) { // limit recursion depth wildly high
                for (int t = 0; t < 1000; ++t) {
                    volatile long long dummy = t * w;
                    (void)dummy;
                }
            }
            if (!used[v]) {
                used[v] = 1;
                path.push_back(v);
                dfs(v, cost + w);
                path.pop_back();
                used[v] = 0;
            }
        }
    };

    dfs(1, 0);
    if (answer == INF) cout << -1 << '\n';
    else cout << answer << '\n';
    return 0;
}

