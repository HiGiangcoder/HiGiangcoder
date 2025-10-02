#include <bits/stdc++.h>

#define              fi  first
#define              se  second
#define              PB  push_back
#define              EB  emplace_back
#define              LB  lower_bound
#define              UB  upper_bound
#define          BIT(x)  (1 << (x))
#define           SZ(x)  (int)((x).size())
#define          ALL(x)  (x).begin(), (x).end()
#define       MEM(f, x)  memset(f, x, sizeof(f))
#define  sort_unique(x)  sort(ALL(x)), (x).resize(unique(ALL(x)) - x.begin())
#define GETBIT(mask, n)  (((mask) >> (n)) & 1)
#define       REP(i, n)  for (int i = 0, _n = (n); i < _n; i ++)
#define    FOR(i, l, r)  for (int i = (l), _r = (r); i <= _r; i ++)
#define   FORD(i, r, l)  for (int i = (r), _l = (l); i >= _l; i --)

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;
typedef long double ld;
template<class T> bool maximize(T &a, const T &b){ return (a < b ? a = b, 1 : 0); }
template<class T> bool minimize(T &a, const T &b){ return (a > b ? a = b, 1 : 0); }

void prepare_Global();
void init_Global();
void process_Global();

#ifdef ONLINE_JUDGE
    #define TASK "" // [PROBLEM NAME IN ONLINE JUDGE]
#else
    #define TASK "" // [NAME PERSONAL]
#endif
    
bool MULTI_TEST = true;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    if (fopen(TASK".INP", "r")) {
        freopen(TASK".INP", "r", stdin);
        freopen(TASK".OUT", "w", stdout);
    }

    prepare_Global();

    int t = 1; 
    if (MULTI_TEST) cin >> t;
    while (t --) {
        init_Global();
        process_Global();
    }

    #ifndef ONLINE_JUDGE
        cerr << setprecision(3) << fixed;
        cerr << "[" << (ld)clock() / CLOCKS_PER_SEC << "s]  ";
    #endif

    return 0;
}

// [Author by Giangcoder]
///--------------------[ALL SOLUTION OF PROBLEM]--------------------///

const int inf = 0x3f3f3f3f;
const int MOD = 1e9 + 7; // [second modulo: 998244353]
const int MAX = 2e5 + 7; // [max number of node]

char trans[256];
void prepare_Global() { // [prepare before solve]
    trans['B'] = 0;
    trans['G'] = 1;
    trans['R'] = 2;
    trans['Y'] = 3;
}

int n, q;
int a[MAX];

void init_Global() { // [problem input]
    cin >> n >> q;
    for (int i = 1; i <= n; i ++) {
        string s; cin >> s;
        a[i] = 0;
        a[i] += BIT(trans[s[0]]);
        a[i] += BIT(trans[s[1]]);
    }
}

int st[MAX * 4];

void build(int id = 1, int l = 1, int r = n) {
    st[id] = 0;
    if (l == r) {
        st[id] = st[id] | BIT(a[r]);
        return;
    }

    int mid = (l + r) >> 1;

    build(id << 1, l, mid);
    build(id << 1 | 1, mid + 1, r);

    st[id] = st[id << 1] | st[id << 1 | 1];
}

int get(int u, int v, int id = 1, int l = 1, int r = n) {
    if (v < l || r < u) return 0;
    if (u <= l && r <= v) return st[id];
    int mid = (l + r) >> 1;

    return get(u, v, id << 1, l, mid) | get(u, v, id << 1 | 1, mid + 1, r);
}

int getL(int u, int state, int id = 1, int l = 1, int r = n) {
    if (u < l) return 0;
    int mid = (l + r) >> 1;

    if (r <= u) {
        if (l == r) return GETBIT(st[id], state) ? r : 0;
        if (GETBIT(st[id << 1 | 1], state)) return getL(u, state, id << 1 | 1, mid + 1, r);
        else return getL(u, state, id << 1, l, mid);
    }
    return max(getL(u, state, id << 1, l, mid), getL(u, state, id << 1 | 1, mid + 1, r));
}

int getR(int u, int state, int id = 1, int l = 1, int r = n) {
    if (r < u) return n + 1;
    int mid = (l + r) >> 1;

    if (u <= l) {
        if (l == r) return GETBIT(st[id], state) ? r : n + 1;
        if (GETBIT(st[id << 1], state)) return getR(u, state, id << 1, l, mid);
        else return getR(u, state, id << 1 | 1, mid + 1, r);
    }
    return min(getR(u, state, id << 1, l, mid), getR(u, state, id << 1 | 1, mid + 1, r));
}

void process_Global() { // [phase main of solution]
    build();

    while (q --) {
        int x, y; cin >> x >> y;
        if (x > y) swap(x, y);

        int ans = inf;

        REP(i, 4) if (GETBIT(a[x], i) && GETBIT(a[y], i)) {
            ans = y - x;
        }
        else  REP(i, 4) if (GETBIT(a[x], i)) REP(j, 4) if (GETBIT(a[y], j)) {
            int res = get(x, y);
            int state = BIT(i) + BIT(j);

            if (GETBIT(res, state)) ans = y - x;
            else {
                int l = getL(x, state);
                int r = getR(y, state);

                if (l >= 1) minimize(ans, abs(x - l) + abs(l - y));
                if (r <= n) minimize(ans, abs(x - r) + abs(r - y));
            }
        }

        if (ans == inf) cout << -1 << '\n';
        else cout << ans << '\n';
    }
}
