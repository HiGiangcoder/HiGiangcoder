#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll = long long;
using ii = pair<int, int>;

const int MOD = 1e9 + 7;
const int MAX = 2e5 + 5;

#define TASK ""

ll n, s;
int a[MAX];

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    if (fopen(TASK".inp", "r")) {
        freopen(TASK".inp", "r", stdin);
        freopen(TASK".out", "w", stdout);
    }

    cin >> n >> s;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    priority_queue<ll, vector<ll>, greater<ll>> pq;  

    for (int i = 1; i <= n; i++) {
        pq.push(a[i]);
    }

    ll ans(0);
    while (pq.size() != 1) {
        ll a = pq.top(); pq.pop();
        ll b = pq.top(); pq.pop();

        ans += a + b;
        pq.push(a + b);
    }

    cout << ans << endl;


    return 0;
}