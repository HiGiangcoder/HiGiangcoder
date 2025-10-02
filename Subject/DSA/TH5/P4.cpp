#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll = long long;
using ii = pair<int, int>;

const int MOD = 1e9 + 7;
const int MAX = 5e5 + 5;

#define TASK ""

int n;
int num[MAX];
int len[MAX];

void Init() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> num[i];
    }

    map<int, int> cnt;
    for (int i = 1; i <= n; i++) {
        cnt[num[i]]++;
    }

    n = 0;
    for (auto it : cnt) {
        num[++n] = it.se;
        len[n] = it.fi;
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    if (fopen(TASK".inp", "r")) {
        freopen(TASK".inp", "r", stdin);
        freopen(TASK".out", "w", stdout);
    }

    Init();

    ll ans(0);

    int j = 1, sum = 0;
    for (int i = 1; i <= n; i++) {
        while (j <= n && len[j] < 2LL * len[i]) {
            sum += num[j];
            j++;
        }

        ans += 1LL * num[i] * (num[i] - 1) * (num[i] - 2) / 6;
        ans += 1LL * num[i] * (num[i] - 1) / 2 * (sum - num[i]);
    }

    cout << ans << endl;
    
    return 0;
}