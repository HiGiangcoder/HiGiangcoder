#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll = long long;
using ii = pair<int, int>;

const int MOD = 1e9 + 7;
const int MAX = 100 + 5;

#define TASK ""

int n, m;
vector<int> adj[MAX];
int encoder[256];
char decoder[100];
int d[MAX][MAX];
int trace[MAX][MAX];

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    if (fopen(TASK".inp", "r")) {
        freopen(TASK".inp", "r", stdin);
        freopen(TASK".out", "w", stdout);
    }

    cin >> n >> m;
    for (int i = 1; i <= n; i ++) {
        char c; cin >> c;
        encoder[c] = i;
        decoder[i] = c;
    }

    while (m --) {
        char u, v; 
        cin >> u >> v;
        int x = encoder[u], y = encoder[v];

        adj[x].push_back(y);
    }

    memset(d, 0x3f, sizeof(d));

    for (int i = 1; i <= n; i ++) {
        queue<int> q;
        q.push(i);
        d[i][i] = 0;

        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (d[i][v] > d[i][u] + 1) {
                    d[i][v] = d[i][u] + 1;
                    trace[i][v] = u;
                    q.push(v);
                }
            }
        }
    }

    int q; cin >> q;
    while (q --) {
        char u, v; cin >> u >> v;
        int x = encoder[u], y = encoder[v];
        
        if (d[x][y] <= n) {
            vector<int> path;
            while (x != y) {
                path.push_back(y);
                y = trace[x][y];
            }
            path.push_back(x);
            reverse(path.begin(), path.end());
            for (int x : path) {
                cout << decoder[x] << " ";
            }
            cout << '\n';
        }
        else cout << "no_path\n";
    }
    
    return 0;
}