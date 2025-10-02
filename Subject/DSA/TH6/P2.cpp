#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll = long long;
using ii = pair<int, int>;

const int MOD = 1e9 + 7;
const int MAX = 1e2 + 5;
const int MAXW = 1e5 + 7;

#define TASK ""

int n, numW;
int w[MAX], c[MAX];
ll dp[MAXW];

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    if (fopen(TASK".inp", "r")) {
        freopen(TASK".inp", "r", stdin);
        freopen(TASK".out", "w", stdout);
    }

    cin >> n >> numW;
    for (int i = 1; i <= n; i++) {
        cin >> w[i] >> c[i];
    }
    
    for (int i = 1; i <= n; i++) {
        for (int j = numW; j >= w[i]; j--) {
            dp[j] = max(dp[j], dp[j - w[i]] + c[i]);
        }
    }

    int ans = max_element(dp, dp + numW + 1) - dp;
    cout << dp[ans] << endl;

    
    return 0;
}