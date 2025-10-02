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
const int MAX = 5e5 + 7; 

int n, q;
vector<int> adj[MAX];

int cntTime(0);
ii timeInOut[MAX];

void dfs(int u, int p) {
    timeInOut[u].fi = ++cntTime;

    for (int v : adj[u]) if (v != p) {
        dfs(v, u);
    }

    timeInOut[u].se = ++cntTime;
}

class SegmentTree {
private:
    int st[MAX * 2 * 4], lz[MAX * 2 * 4];
    void lazy(int id, int l, int r) {
        maximize(st[id], lz[id]);
        if (l < r) {
            maximize(lz[id << 1], lz[id]);
            maximize(lz[id << 1 | 1], lz[id]);
        }
        lz[id] = 0;
    }
    void update(int u, int v, int val, int id, int l, int r) {
        lazy(id, l, r);
        if (v < l || r < u) return;
        if (u <= l && r <= v) {
            lz[id] = val;
            lazy(id, l, r);
            return;
        }

        int mid = (l + r) >> 1;
        update(u, v, val, id << 1, l, mid);
        update(u, v, val, id << 1 | 1, mid + 1, r);

        st[id] = max(st[id << 1], st[id << 1 | 1]);
    }

    int get(int u, int v, int id, int l, int r) {
        lazy(id, l, r);
        if (v < l || r < u) return 0;
        if (u <= l && r <= v) return st[id];

        int mid = (l + r) >> 1;
        return max(get(u, v, id << 1, l, mid), get(u, v, id << 1 | 1, mid + 1, r));
    }
    
public:
    SegmentTree() {
        memset(st, 0, sizeof(st));
        memset(lz, 0, sizeof(lz));
    }
    void update(int u, int v, int val) {
        update(u, v, val, 1, 1, n * 2);
    }
    int get(int u, int v) {
        return get(u, v, 1, 1, n * 2);
    }
} fillQuery, emptyQuery;

void process() {
    cin >> n;

    for (int i = 1; i < n; i ++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1, 1);

    cin >> q;
    for (int i = 1; i <= q; i ++) {
        int type, u; cin >> type >> u;
        if (type == 1) {
            fillQuery.update(timeInOut[u].fi, timeInOut[u].se, i);
        }
        if (type == 2) {
            emptyQuery.update(timeInOut[u].fi, timeInOut[u].fi, i);
        }
        if (type == 3) {
            int idFill = fillQuery.get(timeInOut[u].fi, timeInOut[u].fi);
            int idEmpty = emptyQuery.get(timeInOut[u].fi, timeInOut[u].se);

            if (idEmpty >= idFill) cout << 0 << '\n';
            else cout << 1 << '\n';
        }
    }
}


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    #define TASK ""
    if (fopen(TASK".inp", "r")) {
        freopen(TASK".inp", "r", stdin);
        freopen(TASK".out", "w", stdout);
    }

    process();

    return 0;
}


