/* sort template*/
#include <bits/stdc++.h>
using namespace std;

#define fi  first
#define se  second
typedef long long ll;
typedef pair<int, int> ii;

mt19937_64 rngll(chrono :: steady_clock :: now().time_since_epoch().count());
ll random(ll l, ll r) {
    return uniform_int_distribution<ll>(l, r)(rngll);
}

template<class T> bool maximize(T &a, const T &b){ return (a < b ? a = b, 1 : 0); }
template<class T> bool minimize(T &a, const T &b){ return (a > b ? a = b, 1 : 0); }

const int inf = 0x3f3f3f3f;
const int MOD = 1e9 + 7;
const int MAX = 2e5 + 7; 

int n, q;
struct Node {
    int val;
    int nextId;
    int cntnum;

    Node() {
        val = 0;
        nextId = -1;
        cntnum = 0;
    }
} idNext[20][MAX * 2];
int cntNode(0);

void build() {
    
}

void add(int pos, int val) {
    
}


void process() {
    cin >> n >> q;
    for (int i = 0; i <= n + q; i ++) idNext[i].se = -1;    

    for (int i = 1; i <= n; i ++) {
        cin >> idNext[i].fi;
        idNext[i - 1].se = i;
    }
    int cntnode = n;

    for (int i = 1; i <= q; i ++) {
        int type, u, v; cin >> type >> u >> v;

        if (type == 1) {
            int ptr = 0;
            for (int rep = 0; rep < u - 1; rep ++) {
                ptr = idNext[ptr].se;
            }
            int nextptr = idNext[ptr].se;

            idNext[ptr].se = ++cntnode;
            ptr = idNext[ptr].se;

            idNext[ptr] = {v, nextptr};
        }
        else {
            int ans = 0;
            int ptr = 0;

            for (int i = 1; i <= v; i ++) {
                ptr = idNext[ptr].se;

                if (i >= u) maximize(ans, idNext[ptr].fi);
            }

            cout << ans << '\n';
        }
    }
}


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    process();

    return 0;
}

