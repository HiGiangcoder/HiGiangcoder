// #include <bits/stdc++.h>
// using namespace std;

// int N, M;
// vector<vector<int>> adj;
// vector<bool> used;
// vector<int> path;

// bool greedyMaxDegree(int start) {
//     path.clear();
//     used.assign(N, false);

//     int cur = start;
//     path.push_back(cur);
//     used[cur] = true;

//     for (int step = 1; step < N; step++) {
//         // Tập các hàng xóm chưa thăm
//         vector<int> cand;
//         for (int v : adj[cur]) {
//             if (!used[v]) cand.push_back(v);
//         }
//         if (cand.empty()) return false;

//         // Chọn đỉnh có bậc lớn nhất
//         int best = cand[0];
//         for (int v : cand) {
//             if ((int)adj[v].size() > (int)adj[best].size())
//                 best = v;
//         }

//         cur = best;
//         path.push_back(cur);
//         used[cur] = true;
//     }
//     return true;
// }

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);

//     cin >> N >> M;
//     adj.assign(N, {});
//     for (int i = 0; i < M; i++) {
//         int u, v;
//         cin >> u >> v;
//         --u; --v;
//         adj[u].push_back(v);
//         adj[v].push_back(u);
//     }

//     // Thử từ mọi đỉnh, in kết quả đầu tiên tìm được
//     for (int s = 0; s < N; s++) {
//         if (greedyMaxDegree(s)) {
//             for (int x : path) cout << x+1 << " ";
//             cout << "\n";
//             return 0;
//         }
//     }
//     cout << -1 << "\n";
//     return 0;
// }


// code a Tan, code cu khong dung thuat
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) {
        return 0;
    }

    vector<vector<int>> adj(n);
    vector<vector<bool>> hasEdge(n, vector<bool>(n, false));
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        if (!hasEdge[u][v]) {
            adj[u].push_back(v);
            adj[v].push_back(u);
            hasEdge[u][v] = hasEdge[v][u] = true;
        }
    }

    if (n == 0) {
        cout << "-1\n";
        return 0;
    }

    int fullMask = (1 << n) - 1;
    vector<vector<int>> parent(1 << n, vector<int>(n, -1));

    for (int v = 0; v < n; ++v) {
        parent[1 << v][v] = -2; // start marker
    }

    for (int mask = 1; mask <= fullMask; ++mask) {
        for (int last = 0; last < n; ++last) {
            if (parent[mask][last] == -1) continue;
            for (int to : adj[last]) {
                if (mask & (1 << to)) continue;
                int nextMask = mask | (1 << to);
                if (parent[nextMask][to] == -1) {
                    parent[nextMask][to] = last;
                }
            }
        }
    }

    int endVertex = -1;
    for (int v = 0; v < n; ++v) {
        if (parent[fullMask][v] != -1) {
            endVertex = v;
            break;
        }
    }

    if (endVertex == -1) {
        cout << -1 << '\n';
        return 0;
    }

    vector<int> path;
    int mask = fullMask;
    int current = endVertex;
    while (true) {
        path.push_back(current);
        int prev = parent[mask][current];
        if (prev == -2) break;
        mask ^= (1 << current);
        current = prev;
    }
    reverse(path.begin(), path.end());

    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << path[i] + 1;
    }
    cout << '\n';
    return 0;
}

