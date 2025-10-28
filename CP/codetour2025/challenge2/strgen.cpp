#include<bits/stdc++.h>
using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    int t; cin >> t;
    while (t --) {
        string s; cin >> s;
        bool ok = true, existA = false;
        for (int i = 0; i < s.length(); i ++) {
            if (s[i] == 'A') existA = true;
            if (i + 1 < s.length() && s[i] == s[i + 1] && s[i] == 'A') {
                ok = false;
                break;
            }
        }

        if (ok && existA) {
            cout << "YES ";
            if (s[0] == 'B') cout << "NO\n";
            else cout << "YES\n";
        }
        else cout << "NO NO\n";
    }


    return 0;
}

