/* long template*/
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
    #define TASK "" /* [PROBLEM NAME IN ONLINE JUDGE]*/
#else
    #define TASK "" /* [NAME PERSONAL]*/
#endif
    
bool MULTI_TEST = false;

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

/* [Author by Giangcoder]*/
/*--------------------[ALL SOLUTION OF PROBLEM]--------------------*/

const int inf = 0x3f3f3f3f;
const int MOD = 1e9 + 7; /* [second modulo: 998244353]*/
const int MAX = 1e5 + 7; /*[max number of node]*/

/*[prepare before solve]*/
void prepare_Global() { 
    MULTI_TEST = false;
}

/*[problem input]*/
void init_Global() { 
}

/* [phase main of solution]*/
void process_Global() {
}


