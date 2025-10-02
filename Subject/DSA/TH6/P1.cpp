#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll = long long;
using ii = pair<int, int>;

const int MOD = 1e9 + 7;
const int MAX = 5e3 + 5;

#define TASK ""

int n;
int a[MAX];
int dp[MAX];
int trace[MAX];

bool maximize(int &a, int b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}

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

    int ans(0), numtrace;
    for (int i = 1; i <= n; i++) {
        dp[i] = 1;
        for (int j = 1; j < i; j++) {
            if (a[j] < a[i] && maximize(dp[i], dp[j] + 1)) {
                trace[i] = j;
            }
        }
        ans = max(ans, dp[i]);
        if (ans == dp[i]) numtrace = i; 
    }

    cout << ans << endl;
    vector<int> listans;
    while (numtrace) {
        listans.push_back(a[numtrace]);
        numtrace = trace[numtrace];
    }
    reverse(listans.begin(), listans.end());
    for (int x : listans) {
        cout << x << " ";
    }
    
    return 0;
}