/* Medium-Codeforces tempalte*/
#include <bits/stdc++.h>

#define              fi  first
#define              se  second
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

void prepare();
void process();

#define TASK "" 

bool _multi_test = true;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    if (fopen(TASK".inp", "r")) {
        freopen(TASK".inp", "r", stdin);
        freopen(TASK".out", "w", stdout);
    }

    prepare();
    int t = 1; 
    if (_multi_test) cin >> t;
    while (t --)
        process();

    return 0;
}

/* ---------------------------------------------------------------------------*/
/* ----------------------- author: Nguyen Truong Giang -----------------------*/
/* ---------------------------------------------------------------------------*/

const int MOD = 1e9 + 7;
// const int MOD = 998244353
const int inf = 0x3f3f3f3f;
const int MAX = 1e5 + 7;

void prepare() {_multi_test = false;}

struct Trie {
    int numNode;
    int nodes[MAX * 31][2];

    Trie() {
        numNode = 0;
        memset(nodes, -1, sizeof(nodes));
    }

    void addNum(int num) {
        int ptr = 0;
        for (int i = 29; i >= 0; i --) {
            int dig = GETBIT(num, i);

            if (nodes[ptr][dig] == -1) nodes[ptr][dig] = ++numNode;
            ptr = nodes[ptr][dig];
        }
    }

    int solve(int id = 29, int ptr = 0) {
        if (id < 0) return 0;

        int num = BIT(id);
        int res = inf;
        REP(i, 2) if (nodes[ptr][i] != -1) minimize(res, solve(id - 1, nodes[ptr][i]));

        if (nodes[ptr][0] == -1 || nodes[ptr][1] == -1) num = 0;
        num += res;

        return num;
    }
} trie;

void process() {
    int n; cin >> n;
    while (n --) {
        int num; cin >> num;
        trie.addNum(num);
    }

    cout << trie.solve();
}
