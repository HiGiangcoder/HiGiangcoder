#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll = long long;
using ii = pair<int, int>;

const int MOD = 1e9 + 7;
const int MAX = 1e5 + 5;

#define TASK ""

int decode[256];

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    if (fopen(TASK".inp", "r")) {
        freopen(TASK".inp", "r", stdin);
        freopen(TASK".out", "w", stdout);
    }

    string s; cin >> s;

    decode['{'] = -3;
    decode['}'] = 3;
    decode['['] = -2;
    decode[']'] = 2;
    decode['('] = -1;
    decode[')'] = 1;

    vector<int> stk;

    for (char c : s) if (decode[c] != 0) {
        if (decode[c] < 0) stk.push_back(decode[c]);
        else if (stk.empty() || stk.back() != -decode[c]) {
            cout << 0;
            return 0;
        } else stk.pop_back();
    }
    if (stk.empty()) cout << 1;
    else cout << 0;
    
    return 0;
}