/* sort template*/
#include <bits/stdc++.h>
using namespace std;

#define fi  first
#define se  second
typedef long long ll;
typedef pair<int, int> ii;

template<class T> bool maximize(T &a, const T &b){ return (a < b ? a = b, 1 : 0); }
template<class T> bool minimize(T &a, const T &b){ return (a > b ? a = b, 1 : 0); }

const int inf = 0x3f3f3f3f;
const int MOD = 1e9 + 7;
const int MAX = 2e5 + 7; 
const int MAXE = 3e5 + 7; 

int n, m;
struct Edge{
    int u, v, w, id;
    const bool operator < (const Edge &x) const {
        return w < x.w;
    }
}edge[MAXE];

int lab[MAX];
int find_root(int u) {
    return lab[u] < 0 ? u : lab[u] = find_root(lab[u]);
}
bool uniona(int u, int v) {
    u = find_root(u);
    v = find_root(v);
    if (u == v) return false;
    if (lab[u] > lab[v]) swap(u, v);
    lab[u] += lab[v];
    lab[v] = u;
    return true;
}

bool check(int u, int v) {
    u = find_root(u);
    v = find_root(v);

    return u != v;
}

bool fre[MAXE];

void process() {
    cin >> n >> m;
    for (int i = 1; i <= m; i ++) {
        cin >> edge[i].u >> edge[i].v >> edge[i].w;
        edge[i].id = i;
    }
    sort(edge + 1, edge + 1 + m);

    for (int i = 1; i <= n; i ++) lab[i] = -1;
    for (int i = 1; i <= m; i ++) fre[i] = false;
    edge[0].w = -1;
    
    vector<int> ans;

    for (int i = 1; i <= m; i ++) if (edge[i].w != edge[i - 1].w) {

        for (int j = i; j <= m && edge[j].w == edge[i].w; j ++) {
            fre[j] = check(edge[j].u, edge[j].v);
        }

        for (int j = i; j <= m && edge[j].w == edge[i].w; j ++) {
            if (!check(edge[j].u, edge[j].v) && fre[j]) ans.push_back(edge[j].id);
            uniona(edge[j].u, edge[j].v);
        }
    }

    for (int i = 2; i <= n; i ++) if (uniona(i - 1, i)) {
        cout << -1 << '\n';
        return;
    }

    sort(ans.begin(), ans.end());

    cout << ans.size() << ' ';
    for (int x : ans) cout << x << ' ';
    cout << '\n';
}


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int t; cin >> t;
    while (t --)
        process();

    return 0;
}

