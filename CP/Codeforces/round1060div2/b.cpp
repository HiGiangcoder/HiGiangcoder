#include<bits/stdc++.h>
using namespace std;
using ii = pair<int, int>;
using ll = long long;

#define fi first
#define se second

const int MAX = 2e5 + 5;

int n;
int a[MAX];

void process() {
    cin >> n;
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }

    for (int i = 1, nmax = a[1]; i <= n; i ++) {
        nmax = max(nmax, a[i]);
        if (i % 2 == 0) a[i] = nmax;
    }

    ll ans = 0;
    a[0] = a[n + 1] = 1e9;
    for (int i = 1; i <= n; i ++) if (i % 2 == 1) {
        ans += max(0, a[i] - min(a[i - 1], a[i + 1]) + 1);
    }

    // for (int i = 1; i <= n; i ++) cout << a[i] << ' '; cout << '\n';

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    while (t --) {
        process();
    }
}