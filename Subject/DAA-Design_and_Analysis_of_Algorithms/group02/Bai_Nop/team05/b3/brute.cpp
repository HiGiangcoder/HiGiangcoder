#include <iostream>
#include <vector>
using namespace std;

int n, m;
vector<vector<int>> graph;
vector<int> path;
vector<bool> visited;

bool hamiltonUtil(int pos) {
    if (pos == n) return true;

    for (int v = 1; v <= n; v++) {
        if (graph[path[pos - 1]][v] && !visited[v]) {
            path[pos] = v;
            visited[v] = true;

            if (hamiltonUtil(pos + 1))
                return true;

            visited[v] = false;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    graph.assign(n + 1, vector<int>(n + 1, 0));

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u][v] = graph[v][u] = 1;
    }

    path.resize(n);
    visited.assign(n + 1, false);

    bool found = false;
    for (int start = 1; start <= n && !found; start++) {
        fill(visited.begin(), visited.end(), false);
        path[0] = start;
        visited[start] = true;

        if (hamiltonUtil(1)) {
            for (int i = 0; i < n; i++)
                cout << path[i] << (i == n - 1 ? '\n' : ' ');
            found = true;
        }
    }
    if (!found) cout << -1 << '\n';
}
