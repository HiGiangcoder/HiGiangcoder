#include<bits/stdc++.h>
using namespace std;
using ll = long long;

string s[23];
int correct[23];

int cnt[23];
int ans[17];
ll numway(0);
void dfs(int id) {
    for (int i = 1; i <= 22; i ++) if (cnt[i] > correct[i]) return;

    if (id == 16) {
        numway ++;
        if (numway % int(1e8) == 0) cout << numway << endl;

        for (int i = 1; i <= 22; i ++) if (cnt[i] != correct[i]) return;

        for (int i = 0; i < 16; i ++) cout << ans[i];
        exit(0);
    }

    for (char c = '0'; c <= '9'; c ++) {
        ans[id] = c - '0';

        for (int i = 1; i <= 22; i ++) cnt[i] += c == s[i][id];

        dfs(id + 1);

        for (int i = 1; i <= 22; i ++) cnt[i] -= c == s[i][id];
    }
}

int main() {
    freopen(".inp", "r", stdin);

    for (int i = 1; i <= 22; i ++) {
        cin >> s[i] >> correct[i];
    }

    dfs(0);
}
