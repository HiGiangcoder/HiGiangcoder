#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
const int MAXM = 505; // Giới hạn nhỏ để test ý tưởng

inline int addmod(int a, int b) {
    int s = a + b;
    if (s >= MOD) s -= MOD;
    return s;
}

// dp_inc[n][d] = số dãy tăng (không giảm) tổng = n, phần tử tối đa ≤ d
int dp_inc[MAXM][MAXM];
int inc_sum[MAXM];
int bitonic[MAXM];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M;
    cin >> M;

    // -------------------------------
    // Bước 1: DP cho dãy tăng
    // -------------------------------
    dp_inc[0][0] = 1;
    for (int d = 1; d <= M; d++) {
        dp_inc[0][d] = 1;
        for (int n = 1; n <= M; n++) {
            if (n - d >= 0)
                dp_inc[n][d] = addmod(dp_inc[n][d - 1], dp_inc[n - d][d]);
            else
                dp_inc[n][d] = dp_inc[n][d - 1];
        }
    }

    // -------------------------------
    // Bước 2: Tổng số dãy tăng có tổng = n
    // -------------------------------
    for (int n = 1; n <= M; n++) {
        long long sum = 0;
        for (int d = 1; d <= n; d++) sum += dp_inc[n][d];
        inc_sum[n] = sum % MOD;
    }

    // -------------------------------
    // Bước 3: Ghép 2 dãy tăng → bitonic
    // -------------------------------
    for (int n = 1; n <= M; n++) {
        long long total = 0;
        for (int a = 1; a <= n; a++) {
            for (int b = 1; b <= n; b++) {
                for (int peak = 1; peak <= min(a, b); peak++) {
                    if (a + b - peak == n) {
                        total += 1LL * inc_sum[a] * inc_sum[b];
                        if (total >= 8LL * MOD) total %= MOD;
                    }
                }
            }
        }
        bitonic[n] = total % MOD;
    }

    // -------------------------------
    // Bước 4: Xuất kết quả
    // -------------------------------
    for (int n = 1; n <= M; n++) {
        cout << bitonic[n] << "\n";
    }

    return 0;
}
