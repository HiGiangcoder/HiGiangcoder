#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll = long long;
using ii = pair<int, int>;

const int MOD = 1e9 + 7;

#define TASK ""

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    if (fopen(TASK".inp", "r")) {
        freopen(TASK".inp", "r", stdin);
        freopen(TASK".out", "w", stdout);
    }

    priority_queue<string> pq;

    int n; cin >> n;
    while (n --) {
        string s; cin >> s;
        pq.push(s);

    }

    int ans(0);
    string s = "";

    while (!pq.empty()) {
        string t = pq.top(); pq.pop();
        if (t != s) {
            s = t;
            ans ++;
        }
    }
    cout << ans;
    
    return 0;
}