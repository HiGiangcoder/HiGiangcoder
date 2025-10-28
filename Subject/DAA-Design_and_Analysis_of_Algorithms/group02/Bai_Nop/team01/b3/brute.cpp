#include <bits/stdc++.h>
using namespace std;

const int MAXN = 13;
int n, m;
bool g[MAXN + 36][MAXN + 36];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // cout << -1;
    // return 0;

    cin >> n >> m;

    if(n == 1)
    {
        cout << 1 << '\n';
        return 0;
    } 

    for(int i = 1; i <= m;i ++)
    {
        int u, v;
        cin >> u >> v;
        g[u][v] = g[v][u] = true;   
    }
    vector<int> perm;
    for(int i = 1; i <= n; i++) perm.push_back(i);
    do {
        bool ok = true;
        for(int i = 1; i < n; i++) {
            if(!g[perm[i-1]][perm[i]]) {
                ok = false;
                break;
            }
        }
        if(ok) {
            for(int i = 0; i < n; i++) {
                cout << perm[i] << ' ';
            }
            return 0;
        }
    } while (next_permutation(perm.begin(), perm.end()));
    cout << -1;
    return 0;
}
