#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll = long long;
using ii = pair<int, int>;

const int MOD = 1e9 + 7;
const int MAX = 1e6 + 5;

#define TASK ""

int lps[MAX];
int ans[MAX], numans(0);

void Detect(const string &s, const string &t) {
    int n = s.size(), m = t.size();

    for (int i = 1; i < m; i ++) {
        lps[i] = lps[i - 1];
        while (lps[i] && t[lps[i]] != t[i]) {
            lps[i] = lps[lps[i] - 1];
        }
        if (t[lps[i]] == t[i]) lps[i] ++;
    }

    int prelps(0);
    for (int i = 0; i < n; i ++) {
        while (prelps && t[prelps] != s[i]) {
            prelps = lps[prelps - 1];
        }
        if (t[prelps] == s[i]) prelps ++;

        if (prelps == m) {
            ans[++ numans] = i + 1 - m + 1;
            prelps = lps[prelps];
        }
    }
}

string s, t;

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    if (fopen(TASK".inp", "r")) {
        freopen(TASK".inp", "r", stdin);
        freopen(TASK".out", "w", stdout);
    }

    cin >> s >> t;
    Detect(s, t);

    if (numans == 0) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
        for (int i = 1; i <= numans; i ++) cout << ans[i] << " \n"[i == numans];
    }
    
    return 0;
}