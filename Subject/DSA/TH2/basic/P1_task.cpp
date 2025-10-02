#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll = long long;
using ii = pair<int, int>;

#define int ll

const int MOD = 1e9 + 7;
const int MAX = 1e5 + 5;

#define TASK ""

int n, k;
ii alicePos;

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    if (fopen(TASK".inp", "r")) {
        freopen(TASK".inp", "r", stdin);
        freopen(TASK".out", "w", stdout);
    }

    cin >> n >> k;
    cin >> alicePos.fi >> alicePos.se;

    ii bobPos1, bobPos2;

    bobPos1 = {alicePos.fi - k / 2, alicePos.se};
    if (k % 2) {
        bobPos1.se --;
        if (bobPos1.se == 0) {
            bobPos1.fi --;
            bobPos1.se = 2;
        }
    }

    bobPos2 = {alicePos.fi + k / 2, alicePos.se};
    if (k % 2) {
        bobPos2.se ++;
        if (bobPos2.se == 3) {
            bobPos2.fi ++;
            bobPos2.se = 1;
        }
    }

    ii bobPos = {-1, -1};

    if (bobPos1.fi >= 1) bobPos = bobPos1;

    if ((bobPos2.fi - 1) * 2 + bobPos2.se <= n) {
        if (bobPos1.fi >= 1) {
            bobPos = bobPos1;
        }
        else bobPos = bobPos2;
    }

    if (bobPos.fi != -1) {
        cout << bobPos.fi << " " << bobPos.se << "\n";
    }
    else {
        cout << "-1\n";
    }
    return 0;
}