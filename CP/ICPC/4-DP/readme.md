# Dynamic Programming
## 1. Digit DP
**Ý tưởng**: Giải các bài toán đếm/tính toán trên các số trong một khoảng [L, R] thỏa mãn điều kiện nào đó.

**Ví dụ**: Đếm số số trong [L, R] không chứa chữ số 4 và 13
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

string s;
ll dp[20][2][2];

ll solve(int pos, bool tight, bool lastWasOne) {
    if (pos == s.size()) return 1;
    if (dp[pos][tight][lastWasOne] != -1) return dp[pos][tight][lastWasOne];
    
    int upper = tight ? s[pos] - '0' : 9;
    ll ans = 0;
    
    for (int d = 0; d <= upper; d++) {
        if (d == 4) continue;
        if (lastWasOne && d == 3) continue;
        ans += solve(pos+1, tight && (d == upper), d == 1);
    }
    return dp[pos][tight][lastWasOne] = ans;
}

ll count(ll n) {
    if (n < 0) return 0;
    s = to_string(n);
    memset(dp, -1, sizeof dp);
    return solve(0, true, false);
}

int main() {
    ll L, R;
    cin >> L >> R;
    cout << count(R) - count(L-1) << endl;
}
```

### 1.2. DP trên cây (Tree DP)
**Ví dụ**: Bài toán chọn tập đỉnh độc lập có trọng số lớn nhất
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5+5;
vector<int> adj[N];
int weight[N];
int dp[N][2]; // dp[u][0]: không chọn u, dp[u][1]: chọn u

void dfs(int u, int parent) {
    dp[u][1] = weight[u];
    
    for (int v : adj[u]) {
        if (v == parent) continue;
        dfs(v, u);
        dp[u][0] += max(dp[v][0], dp[v][1]);
        dp[u][1] += dp[v][0];
    }
}

int main() {
    int n; cin >> n;
    for (int i = 1; i <= n; i++) cin >> weight[i];
    
    for (int i = 0; i < n-1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    dfs(1, -1);
    cout << max(dp[1][0], dp[1][1]) << endl;
}
```

## 2. DP bitmask
**Ví dụ**: Bài toán người du lịch (TSP)
```cpp
#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
int n;
int dist[20][20];
int dp[1<<16][16];

int tsp() {
    for (int mask = 0; mask < (1<<n); mask++)
        for (int i = 0; i < n; i++)
            dp[mask][i] = INF;
    
    dp[1][0] = 0; // Bắt đầu từ thành phố 0
    
    for (int mask = 1; mask < (1<<n); mask++) {
        for (int i = 0; i < n; i++) {
            if (!(mask & (1<<i))) continue;
            for (int j = 0; j < n; j++) {
                if (mask & (1<<j)) continue;
                int new_mask = mask | (1<<j);
                dp[new_mask][j] = min(dp[new_mask][j], 
                                    dp[mask][i] + dist[i][j]);
            }
        }
    }
    
    int ans = INF;
    for (int i = 0; i < n; i++)
        ans = min(ans, dp[(1<<n)-1][i] + dist[i][0]);
    
    return ans;
}
```

## 3. DP in DAG

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;
vector<int> adj[N];
int dp[N];

int dfs(int u) {
    if (dp[u] != -1) return dp[u];
    dp[u] = 0;
    for (int v : adj[u]) {
        dp[u] = max(dp[u], 1 + dfs(v));
    }
    return dp[u];
}

// Tìm đường đi dài nhất trong DAG
int longest_path(int n) {
    memset(dp, -1, sizeof dp);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans = max(ans, dfs(i));
    }
    return ans;
}
```

---

## 4. Divide & Conquer DP

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 5005;
long long dp[N][N], C[N][N];

void solve(int l, int r, int optL, int optR, int k) {
    if (l > r) return;
    int mid = (l + r) / 2;
    int bestOpt = optL;
    for (int i = optL; i <= min(mid, optR); i++) {
        long long cur = dp[k-1][i-1] + C[i][mid];
        if (cur < dp[k][mid]) {
            dp[k][mid] = cur;
            bestOpt = i;
        }
    }
    solve(l, mid-1, optL, bestOpt, k);
    solve(mid+1, r, bestOpt, optR, k);
}

// Ví dụ: Chia dãy thành k đoạn với cost tối thiểu
void partition_dp(int n, int k) {
    // Khởi tạo dp[0][0] = 0, còn lại là INF
    for (int i = 1; i <= k; i++) {
        solve(1, n, 1, n, i);
    }
}
```

## 5. Dptimize DP (Knuth / Slope Trick / etc)

### 5.1. Knuth Optimization
Áp dụng khi cost function thỏa mãn quadrangle inequality và monotonicity.

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1005;
long long dp[N][N], C[N][N];
int opt[N][N];

void knuth_optimization(int n) {
    for (int i = 1; i <= n; i++) {
        dp[i][i] = 0;
        opt[i][i] = i;
    }
    for (int len = 2; len <= n; len++) {
        for (int i = 1; i + len - 1 <= n; i++) {
            int j = i + len - 1;
            dp[i][j] = LLONG_MAX;
            for (int k = opt[i][j-1]; k <= opt[i+1][j]; k++) {
                long long cur = dp[i][k] + dp[k+1][j] + C[i][j];
                if (cur < dp[i][j]) {
                    dp[i][j] = cur;
                    opt[i][j] = k;
                }
            }
        }
    }
}
```

---

## 6. Convex Hull Trick (CHT)
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Line {
    mutable ll k, m, p;
    bool operator<(const Line& o) const { return k < o.k; }
    bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
    static const ll INF = LLONG_MAX;
    ll div(ll a, ll b) {
        return a / b - ((a ^ b) < 0 && a % b);
    }
    bool isect(iterator x, iterator y) {
        if (y == end()) { x->p = INF; return false; }
        if (x->k == y->k) x->p = x->m > y->m ? INF : -INF;
        else x->p = div(y->m - x->m, x->k - y->k);
        return x->p >= y->p;
    }
    void add(ll k, ll m) {
        auto z = insert({k, m, 0}), y = z++, x = y;
        while (isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p)
            isect(x, erase(y));
    }
    ll query(ll x) {
        auto l = *lower_bound(x);
        return l.k * x + l.m;
    }
};
```

---

## 7. Tree DP
**Ví dụ**: Bài toán chọn tập đỉnh độc lập có trọng số lớn nhất
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5+5;
vector<int> adj[N];
int weight[N];
int dp[N][2]; // dp[u][0]: không chọn u, dp[u][1]: chọn u

void dfs(int u, int parent) {
    dp[u][1] = weight[u];
    
    for (int v : adj[u]) {
        if (v == parent) continue;
        dfs(v, u);
        dp[u][0] += max(dp[v][0], dp[v][1]);
        dp[u][1] += dp[v][0];
    }
}

int main() {
    int n; cin >> n;
    for (int i = 1; i <= n; i++) cin >> weight[i];
    
    for (int i = 0; i < n-1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    dfs(1, -1);
    cout << max(dp[1][0], dp[1][1]) << endl;
}
```
---

## 8. DP SOS (Sum Over Subsets)
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 20; // Số bit tối đa
int dp[1 << N];

void sos_dp(int n) {
    for (int i = 0; i < n; i++) {
        for (int mask = 0; mask < (1 << n); mask++) {
            if (mask & (1 << i))
                dp[mask] += dp[mask ^ (1 << i)];
        }
    }
}

// Để tính tổng trên tất cả tập con của mỗi mask
```