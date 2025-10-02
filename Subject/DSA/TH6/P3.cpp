#include <bits/stdc++.h>
#define REP(i, n) for (int i = 0, _n = (n); i < _n; i ++)
#define FOR(i, l, r) for (int i = (l), _r = (r); i <= _r; i ++)
#define FORD(i, r, l) for (int i = (r), _l = (l); i >= _l; i --)
#define MAX 1003
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
 
int n, x;
ll a[MAX];
 
int main() {
    ios_base :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
 
    cin >> n >> x;
    FOR(i, 1, n) cin >> a[i];
 
    map<ll, ii> mp;
 
    FOR(i, 3, n) {
        FOR(j, 1, i - 2) {
            mp[a[j] + a[i - 1]] = {j, i - 1};
        }
 
        FOR(j, i + 1, n) {
            ll tmp = a[i] + a[j]; tmp = x - tmp;
 
            if (mp.count(tmp)) {
                cout << mp[tmp].fi << ' ' << mp[tmp].se << ' ' << i << ' ' << j;
                return 0;
            }
        }
    }
 
    cout << "IMPOSSIBLE";
 
    return 0;
}
