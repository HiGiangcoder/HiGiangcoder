#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

int n, m;
vector<vector<int>> adj;
vector<int> path;
vector<bool> visited;

bool find_path(int u, int count) {
    path.push_back(u);
    visited[u] = true;

    if (count == n) {
        return true; // Đã tìm thấy đường đi qua n đỉnh
    }

    for (int v : adj[u]) {
        if (!visited[v]) {
            if (find_path(v, count + 1)) {
                return true;
            }
        }
    }

    // Backtrack
    path.pop_back();
    visited[u] = false;
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    adj.resize(n + 1);
    visited.resize(n + 1, false);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Thử bắt đầu từ mọi đỉnh
    for (int i = 1; i <= n; ++i) {
        if (find_path(i, 1)) {
            for (int j = 0; j < path.size(); ++j) {
                cout << path[j] << (j == path.size() - 1 ? "" : " ");
            }
            cout << endl;
            return 0;
        }
    }

    cout << -1 << endl;
    return 0;
}