#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int MOD = 998244353;

int n,m;
long long l[5], r[5];
int k[5], p[5][5];

ll v[10];
int check[10];

ll GetAns(int id) {
    if (id > n) {
        for (int i = 1; i <= m; i ++) {
            ll sum(0);
            for (int j = 1; j <= k[i]; j ++) sum += v[p[i][j]];
            if (sum < l[i]) check[i] = -1;
            else if (sum > r[i]) check[i] = 1;
        }

        return 1;
    }

    ll l = 0, r = 1e18;
    
    ll boundl, boundr;

    while (l <= r) {
        ll mid = (l + r) / 2;
        check[id] = 0;

        v[id] = mid;

        GetAns(id + 1);

        if (check[id] <= 0) {
            l = mid + 1;
            boundr = mid;
        }
        else {
            r = mid - 1;
        }
    }

    while (l <= r) {
        ll mid = (l + r) / 2;
        check[id] = 0;

        v[id] = mid;

        GetAns(id + 1);

        if (check[id] >= 0) {
            r = mid - 1;
            boundl = mid;
        }
        else {
            l = mid + 1;
        }
    }
    return max(0LL, boundr - boundl + 1)
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    bool fre[9]; memset(fre, 0, sizeof(fre));

    cin >> n >> m;
    int dem = 0;
    for(int i = 1; i <= m; i++){
        cin >> l[i] >> r[i] >> k[i];
        for(int j = 1; j <= k[i]; j++) {
            cin >> p[i][j];
            fre[p[i][j]] = true;
        }
    }

    ll ans = GetAns(1);
    
    if (ans > 0) for (int i = 1; i <= n; i ++) if (!fre[i]) {
        cout << "infinity";
        return 0;
    }

    cout << ans;

    return 0;
}

