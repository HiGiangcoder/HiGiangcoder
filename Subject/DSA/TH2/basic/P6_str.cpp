#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll = long long;
using ii = pair<int, int>;

const int MOD = 1e9 + 7;
const int MAX = 1e5 + 5;

#define TASK ""

int cnt[10], n;
int sum(0);

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    if (fopen(TASK".inp", "r")) {
        freopen(TASK".inp", "r", stdin);
        freopen(TASK".out", "w", stdout);
    }
    
    string s; cin >> s;
    n = s.length();
    for (int i = 0; i < n; ++i) {
        int num = s[i] - '0';
        cnt[num]++;
        sum += num;
    }

    if (sum % 3 == 1) {
        for (int i = 1; i <= 9; i += 3) {
            if (cnt[i] > 0) {
                cnt[i]--;
                sum -= i;
                break;
            }
        }
        if (sum % 3 == 1) {
            int num1(-1), num2(-1);
            for (int i = 8; i >= 0; i -= 3) {
                if (cnt[i] > 0) num2 = num1, num1 = i;
                if (cnt[i] > 1) num2 = i;
            }
            cnt[num1]--;
            cnt[num2]--;
            sum -= num1 + num2;
        }
    } else if (sum % 3 == 2) {
        for (int i = 2; i <= 9; i += 3) {
            if (cnt[i] > 0) {
                cnt[i]--;
                sum -= i;
                break;
            }
        }
        if (sum % 3 == 2) {
            int num1(-1), num2(-1);
            for (int i = 7; i >= 0; i -= 3) {
                if (cnt[i] > 0) num2 = num1, num1 = i;
                if (cnt[i] > 1) num2 = i;
            }
            cnt[num1]--;
            cnt[num2]--;
            sum -= num1 + num2;
        }
    }

    for (int i = 9; i >= 0; --i) {
        for (int j = 0; j < cnt[i]; ++j) cout << i;
    }

    return 0;
}