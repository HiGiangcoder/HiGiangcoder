#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll = long long;
using ii = pair<int, int>;

const int MOD = 1e9 + 7;
const int MAX = 1e5 + 5;

#define TASK ""

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    if (fopen(TASK".inp", "r")) {
        freopen(TASK".inp", "r", stdin);
        freopen(TASK".out", "w", stdout);
    }

    int num; cin >> num;
    int x; cin >> x;

    vector<int> ans;

    while (num > 0) {
        ans.push_back(num % x);
        num /= x;
    }
    reverse(ans.begin(), ans.end());
    for (int x : ans) cout << x;
    
    return 0;
}