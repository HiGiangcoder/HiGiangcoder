#include <bits/stdc++.h>
using namespace std;

bool edge[15][15];
int n, m;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        edge[u][v] = edge[v][u] = true;
    }

    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 1);

    do {
        bool ok = true;
        for (int i = 0; i + 1 < n; ++i) {
            if (!edge[perm[i]][perm[i+1]]) {
                ok = false;
                break;
            }
        }
        if (ok) {
            for (int i = 0; i < n; ++i)
                cout << perm[i] << ' ';
            return 0;
        }
    } while (next_permutation(perm.begin(), perm.end()));

    cout << -1;
    return 0;
}
