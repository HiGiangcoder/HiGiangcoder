#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll = long long;
using ii = pair<int, int>;

const int MOD = 1e9 + 7;
const int MAX = 1e5 + 5;

#define TASK ""

int n, m;
vector<int> adj[MAX];

vector<int> ans;
bool visited[MAX];

void dfs(int u) {
    visited[u] = true;
    if (u != 0) ans.push_back(u);

    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs(v);
        }
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    if (fopen(TASK".inp", "r")) {
        freopen(TASK".inp", "r", stdin);
        freopen(TASK".out", "w", stdout);
    }

    cin >> n >> m;
    while (m--) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(0);
    sort(ans.begin(), ans.end());

    for (int i = 1; i < n; ++i) {
        cout << (visited[i] ? "CO" : "KHONG") << "\n";
    }
    
    return 0;
}