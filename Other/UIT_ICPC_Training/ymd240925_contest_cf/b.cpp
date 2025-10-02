/* sort template*/
#include <bits/stdc++.h>

#define BIT(k) (1LL << (k))
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

int n;
ll numk;
ll a[MAX];

void process() {
    cin >> n >> numk;
    for (int i = 1; i <= n; i ++) cin >> a[i];

    for (ll bit = __lg(numk); bit >= 0; bit --) {
        ll val = BIT(bit);
        ll sum(0);

        for (int i = 1; i <= n; i ++) sum += min(a[i], val);

        if (sum <= numk) {
            numk -= sum;
            for (int i = 1; i <= n; i ++) a[i] -= min(a[i], val);
        }
    }

    int id_start = 1;
    for (int i = 1; i <= n; i ++) if (a[i] > 0 && numk > 0) {
        a[i] --;
        numk --;
        id_start = i + 1;
    }

    vector<int> ans;
    for (int i = id_start; i <= n; i ++) if (a[i] != 0) ans.push_back(i);
    for (int i = 1; i < id_start; i ++) if (a[i] != 0) ans.push_back(i);

    if (numk > 0) cout << -1;
    else {
        for (int x : ans) cout << x << ' ';
    }
}


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    process();

    return 0;
}

