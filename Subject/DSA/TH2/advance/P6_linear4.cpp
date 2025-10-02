#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll = long long;
using ii = pair<int, int>;

const int MOD = 1e9 + 7;
const int MAX = 1e5 + 5;

#define TASK ""

int n, k;
int cnt[MAX];
void process() {
    cin >> n >> k;

    for (int i = 1; i <= n; i ++) cnt[i] = 0;

    int numdistinct = 0;
    int nummax = 0;

    for (int i = 1; i <= n; i ++) {
        int x; cin >> x;
        if (cnt[x] ++ == 0) numdistinct ++;
        if (cnt[x] <= 2) nummax ++;
    }

    if (numdistinct <= k * 2 && k * 2 <= nummax) {
        cout << "YES\n";
    }
    else cout << "NO\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    if (fopen(TASK".inp", "r")) {
        freopen(TASK".inp", "r", stdin);
        freopen(TASK".out", "w", stdout);
    }

    int t; cin >> t;
    while (t --) {
        process();
    }
    
    return 0;
}