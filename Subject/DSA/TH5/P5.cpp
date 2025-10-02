#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll = long long;
using ii = pair<int, int>;

const int MOD = 1e9 + 7;
const int MAX = 2e5 + 5;

#define TASK ""

int n; 
int a[MAX];

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    if (fopen(TASK".inp", "r")) {
        freopen(TASK".inp", "r", stdin);
        freopen(TASK".out", "w", stdout);
    }

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    sort(a + 1, a + n + 1);
    ll ans = 0, sum = 0;
    for (int i = 1; i <= n; i ++) {
        ans += (ll)(i - 1) * a[i] - sum;
        sum += a[i];
    }
    
    cout << ans << endl;
    
    return 0;
}