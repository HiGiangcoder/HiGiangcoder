/* sort template*/
#include <bits/stdc++.h>
using namespace std;

#define fi  first
#define se  second
typedef long long ll;
typedef pair<int, int> ii;

template<class T> bool maximize(T &a, const T &b){ return (a < b ? a = b, 1 : 0); }
template<class T> bool minimize(T &a, const T &b){ return (a > b ? a = b, 1 : 0); }

const int inf = 0x3f3f3f3f;
const int MOD = 998244353;
const int MAXRC = 227 + 7; 
const int MAXN = 722 + 7; 

int dp[MAXRC][MAXRC][MAXN];

int lazyR[MAXRC];
int lazyC[MAXRC];
int lazyMainDiagonal[MAXRC * 2];
int lazySecondaryDiagonal[MAXRC * 2];

int r, c, n;

void Add(int &vari, const int &numadd) {
    vari += numadd;
    if (vari >= MOD) vari -= MOD;
    if (vari < 0) vari += MOD;
}

void UpdR(int r, int val) {
    Add(lazyR[r], -val);
}

void UpdC(int c, int val) {
    Add(lazyC[c], -val);
}

void UpdMainDiagonal(int u, int v, int val) {
    Add(lazyMainDiagonal[u - v + MAXRC], -val);
}

void UpdSecondaryDiagonal(int u, int v, int val) {
    Add(lazySecondaryDiagonal[u + v], -val);
}

void Lazy(int k) {
    int sum(0);
    for (int i = 1; i <= r; i ++) {
        for (int j = 1; j <= c; j ++) {
            Add(sum, dp[i][j][k - 1]);
        }
    }
    
    for (int i = 1; i <= r; i ++) {
        for (int j = 1; j <= c; j ++) {
            dp[i][j][k] = sum;

            Add(dp[i][j][k], lazyR[i]);
            Add(dp[i][j][k], lazyC[j]);
            Add(dp[i][j][k], lazyMainDiagonal[i - j + MAXRC]);
            Add(dp[i][j][k], lazySecondaryDiagonal[i + j]);
            Add(dp[i][j][k], 3LL * dp[i][j][k - 1] % MOD); 
        }
    }

    for (int i = 1; i <= MAXRC * 2; i ++) {
        if (i <= MAXRC) lazyR[i] = lazyC[i] = 0;
        lazyMainDiagonal[i] = lazySecondaryDiagonal[i] = 0;
    }
}

void process() {
    cin >> r >> c >> n;

    for (int i = 1; i <= r; i ++) for (int j = 1; j <= c; j ++) {
        dp[i][j][0] = 1;
    }

    for (int k = 1; k <= n; k ++) {
        for (int i = 1; i <= r; i ++) {
            for (int j = 1; j <= c; j ++) {
                UpdR(i, dp[i][j][k - 1]);
                UpdC(j, dp[i][j][k - 1]);
                UpdMainDiagonal(i, j, dp[i][j][k - 1]);
                UpdSecondaryDiagonal(i, j, dp[i][j][k - 1]);
            }
        }

        Lazy(k);
    }

    int ans(0);
    for (int i = 1; i <= r; i ++) {
        for (int j = 1; j <= c; j ++) {
            Add(ans, dp[i][j][n]);
        }
    }
    cout << ans;
}


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    process();

    return 0;
}

