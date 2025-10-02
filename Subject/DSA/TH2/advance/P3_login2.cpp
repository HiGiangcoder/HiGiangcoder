#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll = long long;
using ii = pair<int, int>;

const int MOD = 1e9 + 7;
const int MAX = 1e5 + 5;

#define TASK ""

int n, q;
map<string, vector<string>> mp;

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    if (fopen(TASK".inp", "r")) {
        freopen(TASK".inp", "r", stdin);
        freopen(TASK".out", "w", stdout);
    }

    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        string s, t;
        cin >> s >> t;
        mp[s].push_back(t);
    }
    for (int i = 0; i < q; i++) {
        string s;
        cin >> s;

        if (mp.count(s)) {
            for (string x : mp[s]) {
                cout << x << " ";
            }
            cout << '\n';
        }
        else cout << "Chua Dang Ky!\n";
    }
    
    return 0;
}