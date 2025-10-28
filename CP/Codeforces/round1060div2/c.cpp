#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ii = pair<int, int>;
#define fi first
#define se second

const int MAX = 4e5 + 5;
const ll inf = 1e18;

int pre_prime[MAX];
int fw[MAX];

void preprocess() {
    for (int i = 2; i < MAX; i ++) {
        for (int j = i; j < MAX; j += i) {
            if (pre_prime[j] == 0) pre_prime[j] = i;
        }
    }
    memset(fw, 0x3f, sizeof(fw));
}

int n;
int a[MAX], b[MAX];

bool fre[MAX];
vector<ii> rollback;

void _upd(int num, bool val) {
    if (fre[num] == val) return;
    rollback.push_back({num, fre[num]});
    fre[num] = val;
}
bool _get(int num) {
    return fre[num];
}
void _clear() {
    while (!rollback.empty()) {
        ii x = rollback.back(); rollback.pop_back();
        fre[x.fi] = x.se;
    }
}

vector<ii> rollback_fw;
void _upd_fw(int idx, int val) {
    rollback_fw.push_back({idx, fw[idx]});
    fw[idx] = val;
}
void _clear_fw() {
    while (!rollback_fw.empty()) {
        ii x = rollback_fw.back(); rollback_fw.pop_back();
        fw[x.fi] = x.se;
    }
}

void update(int idx, int val) {
    for (; idx > 1; idx -= idx & -idx) {
        if (fw[idx] > val) _upd_fw(idx, val);
    }
}
int get(int idx) {
    int res = 1e9;
    for (; idx < MAX; idx += idx & -idx) {
        res = min(res, fw[idx]);
    }
    return res;
}

const int SQRT = 700;
void Upd(int num) {
    while (num > 1) {
        int p = pre_prime[num];
        while (num % p == 0) num /= p;

        if (p >= SQRT) {
            for (int q = p; q < MAX; q += p) {
                // _upd(q, true);
                update(q, q);
            }
        }
        else _upd(p, true);
    }
}

ll Get(int num) {
    ll res = get(num) - num;

    for (int i = 0; i < SQRT; i ++) {
        if (i > 1 && _get(i)) res = min(res, (ll)(i - num % i) % i);
        if (res == 0) return 0;
    }
    return res;
}

void process() {
    cin >> n;
    for (int i = 1; i <= n; i ++) cin >> a[i];
    for (int i = 1; i <= n; i ++) cin >> b[i];
    
    ll ans = inf;

    ll res[2] = {inf, inf};
    for (int i = 1; i <= n; i ++) {
        if (a[i] % 2 == 0) { // even
            ans = min(ans, min(res[0], res[1]) + 0LL);
            res[0] = 0;
        }
        else { // odd
            ans = min(ans, min(res[0], res[1]) + (ll)b[i]);
            res[1] = min(res[1], (ll)b[i]);
        }
    }

    _clear_fw();
    _clear();
    for (int i = 1; i <= n; i ++) {
        ans = min(ans, Get(a[i]) * (ll)b[i]);
        Upd(a[i]);
    }

    _clear_fw();
    _clear();
    for (int i = n; i >= 1; i --) {
        ans = min(ans, Get(a[i]) * (ll)b[i]);
        Upd(a[i]);
    }

    cout << ans << '\n';
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    preprocess();
    
    int t; cin >> t;
    while (t --) {
        process();
    }
}