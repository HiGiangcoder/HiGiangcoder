#include<bits/stdc++.h>
using namespace std;

#define oo                             0x3f3f3f3f
#define YESn                           "YES\n"
#define YES                               "YES"
#define NO                                 "NO"
#define endl                              "\n"
#define NOn                             "NO\n"
#define ff                                  first
#define ss                                 second
#define ins                                insert
#define pb                              push_back
#define sqr(x)                  ((x) * 1ll * (x))
#define all(x)                 x.begin(), x.end()
#define allr(x)               x.rbegin(),x.rend()
#define fore(x, graph)        for(auto x : graph)
#define repu(i, x, n) for(int i = x; i <= n; ++i)
#define repd(i, n, x) for(int i = n; i >= x; --i)
#define reset(x, val)   memset(x, val, sizeof(x))

typedef double         db;
typedef long long      ll;
typedef long double    ld;
typedef pair<int,int> pii;
typedef pair<ll, ll>  pll;

template<class T> T gcd(T a, T b)                              { if(b > a) swap(a, b); if(b == 0) return a; return gcd(b, a % b); }
template<class T> T lcm(T a, T b)                                                                     { return a / gcd(a, b) * b; }
template<class T> bool getbit(T val, int i)                                                              { return (val >> i) & 1; }
template<class T> int cntbit(T val)                                         { return val == 0 ? 0 : cntbit(val >> 1) + (val & 1); }
template<class T> ll fpow(T a, const T b) { ll res = 1, x = a, y = b; while(y){if(y & 1)res *= x; x = x * x; y>>=1;}; return res; }
template<class T> ll modfpow(T a, T b, const T &m) { ll res = 1, x = a, y = b; x %= m; while(y){if(y & 1){res *= x; res %= m;}; x = x * x; x %= m; y >>= 1; } return res % m; }
 
#define int ll

const int mod =        1e9 + 7;
const ll INF =        1e18 + 7;
const ll LNF  =       1e18 + 7;
const int LOG =             25;
const int block_size =     725;
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};

mt19937 RND(chrono::high_resolution_clock::now().time_since_epoch().count());
ll rnd(ll l, ll r)
{
    assert(l <= r);ll L = l, R = r;
    ll aft = (L + RND() * 1LL % (R - L + 1));
    return aft;
}

template<class T> bool umax(T &a, T b) { if(a < b){ a = b; return 1;} else return 0;}
template<class T> bool umin(T &a, T b) { if(a > b){ a = b; return 1;} else return 0;}

const int NmX = 1e5 + 5;

int n, m;
vector<pii> G[NmX];

ll dijkstra(int s, int t){
    vector<ll> dist(n + 1, INF);
    dist[s] = 0;
    // priority_queue<pii, vector<pii>, greater<pii>> pqi;
    queue<pii> pq;
    pq.push({0, s});
    while(!pq.empty()){
        pii top = pq.front(); pq.pop();
        int u = top.ss;

        if(dist[u] < top.ff) continue;

        fore(x, G[u]){
            int v = x.ff;
            ll w = x.ss;
            if(umin(dist[v], dist[u] + w)){
                pq.push({dist[v], v});
            }
        }
    }
    if(dist[n] != INF) return dist[t];
    return -1;
}   

void process(){
    cin >> n >> m;
    repu(i, 1, m){
        int u, v, w; cin >> u >> v >> w;
        G[u].pb({v, w});
        // G[v].pb({u, w});
    }
    cout << dijkstra(1, n) << endl;
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);

    if(fopen("DEBUG.inp", "r")){
        freopen("DEBUG.inp", "r", stdin);
        freopen("DEBUG.out", "w", stdout);
    }

    int ntest = 1;
    while(ntest--)
        process();

    cerr << "Time elapsed: " << (1.0 * clock()/CLOCKS_PER_SEC) * 1000 << "ms.\n";
    return 0;
}
