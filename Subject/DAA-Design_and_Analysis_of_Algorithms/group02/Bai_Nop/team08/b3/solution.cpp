#define nametask ""
#include <bits/stdc++.h>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define SZ(a) (int) a.size()
#define all(a) a.begin(), a.end()
#define FOR(i, a, b) for (int i = a; i <= b; i++)
#define FOD(i, b, a) for (int i = b; i >= a; i--)

using namespace std;
typedef long long ll;
typedef pair <int, int> pi;
const int N = 15;

int n, m;
vector <int> adj[N];
int pre[N];
bool vis[N];
bool ok = 0;
vector <int> res;

void dfs(int u, int cnt){
    if (ok) return;
    if (cnt == n){
        ok = 1;
        int x = u;
        while (x != 0){
            res.pb(x);
            x = pre[x];
        }
        return;
    }
    for (int i = 0; i < SZ(adj[u]); i++){
        int v = adj[u][i];
        if (!vis[v]){
            vis[v] = 1;
            pre[v] = u;
            dfs(v, cnt + 1);
            vis[v] = 0;
        }
    }
}

void solve(){
    cin >> n >> m;
    FOR(i, 1, m){
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    FOR(i, 1, n){
        if (!ok){
            vis[i] = 1;
            pre[i] = 0;
            dfs(i, 1);
            vis[i] = 0;
        }
        else break;
    }
    if (!ok) cout << -1;
    else{
        FOD(i, SZ(res) - 1, 0) cout << res[i] << ' ';
    }
}

signed main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    if (fopen(nametask".inp", "r")){
        freopen(nametask".inp", "r", stdin);
        freopen(nametask".out", "w", stdout);
    }
    solve();
    return 0;
}
