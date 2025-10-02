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

ll Sum(ll l, ll r, ll k) {
    return max(0LL, min(r, k) - l + 1);
}

ll Cnt(ll n, ll k) {
    ll num = 1;
    
    ll res = 1 <= k;

    while (num < n) {
        ll l = num + 1;
        ll r = l * 2;

        ll cnt = l * 2 - 1;
        minimize(cnt, n - num);

        ll tmp1 = Sum(l - (cnt + 1) / 2 + 1, l, k);
        ll tmp2 = Sum(r, r + cnt / 2 - 1, k);

        res += tmp1 + tmp2;
        num += cnt;
    }
    return res;
}

void process() {
    ll n, k; cin >> n >> k;

    ll l = 1, r = 9e18;
    ll ans(0);

    while (l <= r) {
        ll mid = (l + r) / 2;

        if (Cnt(n, mid) >= k) {
            ans = mid;
            r = mid - 1;
        }else {
            l = mid + 1;
        }
    }

    cout << ans << '\n';
}


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int t; cin >> t;
    while (t --) 
        process();

    return 0;
}

