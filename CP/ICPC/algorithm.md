
## 1. Quy hoạch động (Dynamic Programming) nâng cao

### 1.1. DP trên chữ số (Digit DP)
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

### 1.3. DP bitmask
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

## 2. Cấu trúc dữ liệu nâng cao

### 2.1. Segment Tree 1D
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;
int n, arr[N];
int tree[4*N];

void build(int id, int l, int r) {
    if (l == r) {
        tree[id] = arr[l];
        return;
    }
    int mid = (l + r) / 2;
    build(2*id, l, mid);
    build(2*id+1, mid+1, r);
    tree[id] = tree[2*id] + tree[2*id+1];
}

void update(int id, int l, int r, int pos, int val) {
    if (l == r) {
        tree[id] = val;
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) update(2*id, l, mid, pos, val);
    else update(2*id+1, mid+1, r, pos, val);
    tree[id] = tree[2*id] + tree[2*id+1];
}

int query(int id, int l, int r, int u, int v) {
    if (v < l || r < u) return 0;
    if (u <= l && r <= v) return tree[id];
    int mid = (l + r) / 2;
    return query(2*id, l, mid, u, v) + 
           query(2*id+1, mid+1, r, u, v);
}
```

### 2.2. Segment Tree 2D
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 100;
int n, m;
int arr[N][N];
int tree[4*N][4*N];

void buildY(int idx, int lx, int rx, int idy, int ly, int ry) {
    if (ly == ry) {
        if (lx == rx) tree[idx][idy] = arr[lx][ly];
        else tree[idx][idy] = tree[2*idx][idy] + tree[2*idx+1][idy];
    } else {
        int mid = (ly + ry) / 2;
        buildY(idx, lx, rx, 2*idy, ly, mid);
        buildY(idx, lx, rx, 2*idy+1, mid+1, ry);
        tree[idx][idy] = tree[idx][2*idy] + tree[idx][2*idy+1];
    }
}

void buildX(int idx, int lx, int rx) {
    if (lx != rx) {
        int mid = (lx + rx) / 2;
        buildX(2*idx, lx, mid);
        buildX(2*idx+1, mid+1, rx);
    }
    buildY(idx, lx, rx, 1, 0, m-1);
}

int queryY(int idx, int idy, int ly, int ry, int y1, int y2) {
    if (y2 < ly || ry < y1) return 0;
    if (y1 <= ly && ry <= y2) return tree[idx][idy];
    int mid = (ly + ry) / 2;
    return queryY(idx, 2*idy, ly, mid, y1, y2) +
           queryY(idx, 2*idy+1, mid+1, ry, y1, y2);
}

int queryX(int idx, int lx, int rx, int x1, int x2, int y1, int y2) {
    if (x2 < lx || rx < x1) return 0;
    if (x1 <= lx && rx <= x2) return queryY(idx, 1, 0, m-1, y1, y2);
    int mid = (lx + rx) / 2;
    return queryX(2*idx, lx, mid, x1, x2, y1, y2) +
           queryX(2*idx+1, mid+1, rx, x1, x2, y1, y2);
}
```

### 2.3. Fenwick Tree (BIT) 1D và 2D
**BIT 1D:**
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;
int n, bit[N];

void update(int idx, int delta) {
    for (; idx <= n; idx += idx & -idx)
        bit[idx] += delta;
}

int query(int idx) {
    int sum = 0;
    for (; idx > 0; idx -= idx & -idx)
        sum += bit[idx];
    return sum;
}

int range_query(int l, int r) {
    return query(r) - query(l-1);
}
```

**BIT 2D:**
```cpp
int n, m;
int bit[N][N];

void update(int x, int y, int delta) {
    for (int i = x; i <= n; i += i & -i)
        for (int j = y; j <= m; j += j & -j)
            bit[i][j] += delta;
}

int query(int x, int y) {
    int sum = 0;
    for (int i = x; i > 0; i -= i & -i)
        for (int j = y; j > 0; j -= j & -j)
            sum += bit[i][j];
    return sum;
}

int range_query(int x1, int y1, int x2, int y2) {
    return query(x2, y2) - query(x1-1, y2) - 
           query(x2, y1-1) + query(x1-1, y1-1);
}
```

### 2.4. LiChao Tree
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll INF = 1e18;
const int MAXN = 1e5+5;

struct Line {
    ll m, b; // y = mx + b
    Line(ll m = 0, ll b = INF) : m(m), b(b) {}
    ll eval(ll x) { return m*x + b; }
};

Line tree[4*MAXN];

void add_line(Line new_line, int id, int l, int r) {
    int mid = (l + r) / 2;
    bool left = new_line.eval(l) < tree[id].eval(l);
    bool middle = new_line.eval(mid) < tree[id].eval(mid);
    
    if (middle) swap(tree[id], new_line);
    if (l == r) return;
    
    if (left != middle) add_line(new_line, 2*id, l, mid);
    else add_line(new_line, 2*id+1, mid+1, r);
}

ll query(ll x, int id, int l, int r) {
    if (l == r) return tree[id].eval(x);
    int mid = (l + r) / 2;
    if (x <= mid) return min(tree[id].eval(x), query(x, 2*id, l, mid));
    else return min(tree[id].eval(x), query(x, 2*id+1, mid+1, r));
}
```

## 3. Thuật toán luồng (Flow)

### 3.1. Edmonds-Karp
```cpp
#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
int n;
vector<vector<int>> capacity;
vector<vector<int>> adj;

int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int u = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int v : adj[u]) {
            if (parent[v] == -1 && capacity[u][v] > 0) {
                parent[v] = u;
                int new_flow = min(flow, capacity[u][v]);
                if (v == t) return new_flow;
                q.push({v, new_flow});
            }
        }
    }
    return 0;
}

int max_flow(int s, int t) {
    int flow = 0;
    vector<int> parent(n);
    int new_flow;

    while (new_flow = bfs(s, t, parent)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }
    return flow;
}
```

### 3.2. Dinic's Algorithm
```cpp
#include <bits/stdc++.h>
using namespace std;

struct Dinic {
    struct Edge {
        int to, rev;
        long long cap;
        Edge(int to, long long cap, int rev) : to(to), cap(cap), rev(rev) {}
    };
    
    vector<vector<Edge>> adj;
    vector<int> level, iter;
    int n;
    
    Dinic(int n) : n(n), adj(n), level(n), iter(n) {}
    
    void add_edge(int u, int v, long long cap) {
        adj[u].emplace_back(v, cap, adj[v].size());
        adj[v].emplace_back(u, 0, adj[u].size()-1);
    }
    
    void bfs(int s) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto &e : adj[u]) {
                if (e.cap > 0 && level[e.to] < 0) {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
            }
        }
    }
    
    long long dfs(int u, int t, long long f) {
        if (u == t) return f;
        for (int &i = iter[u]; i < adj[u].size(); i++) {
            Edge &e = adj[u][i];
            if (e.cap > 0 && level[u] < level[e.to]) {
                long long d = dfs(e.to, t, min(f, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    adj[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }
    
    long long max_flow(int s, int t) {
        long long flow = 0;
        while (true) {
            bfs(s);
            if (level[t] < 0) return flow;
            fill(iter.begin(), iter.end(), 0);
            long long f;
            while ((f = dfs(s, t, 1e18)) > 0) flow += f;
        }
    }
};
```

## 4. LCA và RMQ

### 4.1. Sparse Table cho RMQ
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5, LOG = 17;
int st[N][LOG];
int lg[N];

void build(int n, vector<int>& arr) {
    for (int i = 0; i < n; i++) st[i][0] = arr[i];
    
    for (int j = 1; j < LOG; j++)
        for (int i = 0; i + (1<<j) <= n; i++)
            st[i][j] = min(st[i][j-1], st[i+(1<<(j-1))][j-1]);
    
    lg[1] = 0;
    for (int i = 2; i <= n; i++) lg[i] = lg[i/2] + 1;
}

int query(int l, int r) {
    int j = lg[r-l+1];
    return min(st[l][j], st[r-(1<<j)+1][j]);
}
```

### 4.2. LCA sử dụng Binary Lifting
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5, LOG = 17;
vector<int> adj[N];
int depth[N];
int parent[N][LOG];

void dfs(int u, int p) {
    parent[u][0] = p;
    for (int v : adj[u]) {
        if (v == p) continue;
        depth[v] = depth[u] + 1;
        dfs(v, u);
    }
}

void preprocess(int n, int root) {
    depth[root] = 0;
    dfs(root, -1);
    
    for (int j = 1; j < LOG; j++)
        for (int i = 0; i < n; i++)
            if (parent[i][j-1] != -1)
                parent[i][j] = parent[parent[i][j-1]][j-1];
            else
                parent[i][j] = -1;
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    
    int diff = depth[u] - depth[v];
    for (int j = 0; j < LOG; j++)
        if (diff & (1<<j))
            u = parent[u][j];
    
    if (u == v) return u;
    
    for (int j = LOG-1; j >= 0; j--)
        if (parent[u][j] != parent[v][j])
            u = parent[u][j], v = parent[v][j];
    
    return parent[u][0];
}
```

## 5. Các bài toán tổ hợp

### 5.1. Hệ số nhị thức và tổ hợp
```cpp
#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9+7;
const int N = 1e6;

long long fact[N], inv_fact[N];

long long powmod(long long a, long long b) {
    long long res = 1;
    for (; b; b >>= 1) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
    }
    return res;
}

void precompute() {
    fact[0] = 1;
    for (int i = 1; i < N; i++)
        fact[i] = fact[i-1] * i % MOD;
    
    inv_fact[N-1] = powmod(fact[N-1], MOD-2);
    for (int i = N-2; i >= 0; i--)
        inv_fact[i] = inv_fact[i+1] * (i+1) % MOD;
}

long long nCk(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fact[n] * inv_fact[k] % MOD * inv_fact[n-k] % MOD;
}

long long nPk(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fact[n] * inv_fact[n-k] % MOD;
}
```

### 5.2. Catalan Number
```cpp
vector<long long> catalan(int n) {
    vector<long long> cat(n+1);
    cat[0] = 1;
    for (int i = 1; i <= n; i++)
        cat[i] = cat[i-1] * (4*i-2) % MOD * powmod(i+1, MOD-2) % MOD;
    return cat;
}
```

## 6. Lý thuyết số quan trọng

### 6.1. Sàng nguyên tố và phân tích thừa số
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e6;
vector<bool> is_prime;
vector<int> primes, spf; // smallest prime factor

void sieve() {
    is_prime.assign(N+1, true);
    spf.resize(N+1);
    
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= N; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            spf[i] = i;
        }
        for (int p : primes) {
            if (i * p > N) break;
            is_prime[i * p] = false;
            spf[i * p] = p;
            if (i % p == 0) break;
        }
    }
}

vector<pair<int, int>> factorize(int n) {
    vector<pair<int, int>> factors;
    while (n > 1) {
        int p = spf[n];
        int cnt = 0;
        while (n % p == 0) {
            n /= p;
            cnt++;
        }
        factors.emplace_back(p, cnt);
    }
    return factors;
}

long long phi(int n) {
    auto factors = factorize(n);
    long long result = n;
    for (auto [p, cnt] : factors)
        result = result / p * (p-1);
    return result;
}
```

### 6.2. Nghịch đảo modulo
```cpp
long long mod_inv(long long a, long long m) {
    // Extended Euclidean Algorithm
    long long m0 = m, t, q;
    long long x0 = 0, x1 = 1;
    
    if (m == 1) return 0;
    
    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    
    if (x1 < 0) x1 += m0;
    return x1;
}
```

## 7. 2-SAT
```cpp
#include <bits/stdc++.h>
using namespace std;

struct TwoSAT {
    int n;
    vector<vector<int>> adj, adj_rev;
    vector<int> comp, order;
    vector<bool> used, assignment;
    
    TwoSAT(int n) : n(n), adj(2*n), adj_rev(2*n) {}
    
    void add_implication(int a, int b) {
        // (a => b)
        adj[a].push_back(b);
        adj_rev[b].push_back(a);
    }
    
    void add_or(int a, int b) {
        // (a ∨ b) ≡ (¬a => b) ∧ (¬b => a)
        add_implication(a^1, b);
        add_implication(b^1, a);
    }
    
    void add_xor(int a, int b) {
        // (a ⊕ b) ≡ (a ∨ b) ∧ (¬a ∨ ¬b)
        add_or(a, b);
        add_or(a^1, b^1);
    }
    
    void dfs1(int u) {
        used[u] = true;
        for (int v : adj[u]) if (!used[v]) dfs1(v);
        order.push_back(u);
    }
    
    void dfs2(int u, int cl) {
        comp[u] = cl;
        for (int v : adj_rev[u]) if (comp[v] == -1) dfs2(v, cl);
    }
    
    bool solve() {
        order.clear();
        used.assign(2*n, false);
        for (int i = 0; i < 2*n; i++) if (!used[i]) dfs1(i);
        
        comp.assign(2*n, -1);
        for (int i = 0, j = 0; i < 2*n; i++) {
            int u = order[2*n-1-i];
            if (comp[u] == -1) dfs2(u, j++);
        }
        
        assignment.assign(n, false);
        for (int i = 0; i < n; i++) {
            if (comp[2*i] == comp[2*i+1]) return false;
            assignment[i] = comp[2*i] > comp[2*i+1];
        }
        return true;
    }
};
```

## 8. Định lý thặng dư Trung Hoa (CRT)
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll extended_gcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1; y = 0;
        return a;
    }
    ll x1, y1;
    ll g = extended_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

pair<ll, ll> crt(vector<ll> a, vector<ll> m) {
    // Giải hệ x ≡ a[i] (mod m[i])
    ll A = a[0], M = m[0];
    int n = a.size();
    
    for (int i = 1; i < n; i++) {
        ll x, y;
        ll g = extended_gcd(M, m[i], x, y);
        
        if ((a[i] - A) % g != 0) return {-1, -1}; // No solution
        
        ll mod = m[i] / g;
        ll k = ((a[i] - A) / g) % mod * x % mod;
        if (k < 0) k += mod;
        
        A += k * M;
        M *= m[i] / g;
        if (A >= M) A %= M;
    }
    return {A, M};
}
```

## 9. Chia để trị (Divide and Conquer)

### 9.1. Thuật toán nhân ma trận (Giữ nguyên)
```cpp
#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9+7;

vector<vector<long long>> matmul(vector<vector<long long>>& A, 
                                vector<vector<long long>>& B) {
    int n = A.size(), m = B[0].size(), p = B.size();
    vector<vector<long long>> C(n, vector<long long>(m, 0));
    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            for (int k = 0; k < p; k++)
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
    
    return C;
}

vector<vector<long long>> matpow(vector<vector<long long>> A, long long k) {
    int n = A.size();
    vector<vector<long long>> result(n, vector<long long>(n, 0));
    for (int i = 0; i < n; i++) result[i][i] = 1;
    
    while (k > 0) {
        if (k & 1) result = matmul(result, A);
        A = matmul(A, A);
        k >>= 1;
    }
    return result;
}
```

### 9.2. Centroid Decomposition - Chia để trị trên cây sử dụng Centroid

**Centroid**: Một đỉnh trong cây mà khi xóa đi, mỗi thành phần liên thông còn lại có số đỉnh ≤ n/2.

**Ứng dụng**: Giải các bài toán về đường đi trên cây, đếm số cặp đỉnh thỏa mãn điều kiện.

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
vector<int> adj[N];
int sz[N];          // Kích thước cây con
bool removed[N];    // Đánh dấu đỉnh đã bị xóa
int centroid_parent[N]; // Cây centroid decomposition

// Tính kích thước các cây con
void dfs_size(int u, int p) {
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v != p && !removed[v]) {
            dfs_size(v, u);
            sz[u] += sz[v];
        }
    }
}

// Tìm centroid của cây
int find_centroid(int u, int p, int total_size) {
    for (int v : adj[u]) {
        if (v != p && !removed[v] && sz[v] * 2 > total_size)
            return find_centroid(v, u, total_size);
    }
    return u;
}

// Xây dựng cây centroid decomposition
void build_centroid_tree(int u, int parent_centroid = -1) {
    dfs_size(u, -1);
    int cent = find_centroid(u, -1, sz[u]);
    
    removed[cent] = true;
    centroid_parent[cent] = parent_centroid;
    
    // Đệ quy trên các cây con sau khi xóa centroid
    for (int v : adj[cent]) {
        if (!removed[v]) {
            build_centroid_tree(v, cent);
        }
    }
}

// Ví dụ: Đếm số cặp đỉnh có khoảng cách = k
long long count_pairs_with_distance(int u, int p, int depth, vector<int>& distances) {
    distances.push_back(depth);
    long long count = 0;
    
    for (int v : adj[u]) {
        if (v != p && !removed[v]) {
            count += count_pairs_with_distance(v, u, depth + 1, distances);
        }
    }
    return count;
}

long long solve(int u, int k) {
    dfs_size(u, -1);
    int cent = find_centroid(u, -1, sz[u]);
    removed[cent] = true;
    
    long long result = 0;
    map<int, int> freq; // Lưu số lượng đỉnh với khoảng cách i từ centroid
    
    // Khởi tạo: khoảng cách từ centroid đến chính nó là 0
    freq[0] = 1;
    
    for (int v : adj[cent]) {
        if (!removed[v]) {
            vector<int> distances;
            // Thu thập tất cả khoảng cách trong cây con
            count_pairs_with_distance(v, cent, 1, distances);
            
            // Đếm số cặp giữa các cây con khác nhau
            for (int dist : distances) {
                if (freq.count(k - dist)) {
                    result += freq[k - dist];
                }
            }
            
            // Cập nhật frequency
            for (int dist : distances) {
                freq[dist]++;
            }
        }
    }
    
    // Đệ quy trên các cây con
    for (int v : adj[cent]) {
        if (!removed[v]) {
            result += solve(v, k);
        }
    }
    
    return result;
}

int main() {
    int n, k;
    cin >> n >> k;
    
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    memset(removed, false, sizeof(removed));
    cout << solve(1, k) << endl;
    
    return 0;
}
```

### 9.3. Ứng dụng Centroid Decomposition cho bài toán khác

#### Bài toán: Tìm đường đi có tổng trọng số bằng K

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
vector<pair<int, int>> adj[N]; // {neighbor, weight}
int sz[N];
bool removed[N];
int min_distance[N]; // Khoảng cách tối thiểu từ centroid đến các đỉnh

// Các hàm dfs_size và find_centroid giống như trên

void dfs_distances(int u, int p, int dist, vector<int>& distances) {
    distances.push_back(dist);
    for (auto [v, w] : adj[u]) {
        if (v != p && !removed[v]) {
            dfs_distances(v, u, dist + w, distances);
        }
    }
}

int count_paths_with_sum(int u, int k) {
    dfs_size(u, -1);
    int cent = find_centroid(u, -1, sz[u]);
    removed[cent] = true;
    
    int result = 0;
    map<int, int> freq;
    freq[0] = 1; // Đường đi từ centroid đến chính nó
    
    for (auto [v, w] : adj[cent]) {
        if (!removed[v]) {
            vector<int> distances;
            dfs_distances(v, cent, w, distances);
            
            // Đếm số đường đi có tổng = k
            for (int dist : distances) {
                if (freq.count(k - dist)) {
                    result += freq[k - dist];
                }
            }
            
            // Cập nhật frequency
            for (int dist : distances) {
                freq[dist]++;
            }
        }
    }
    
    // Đệ quy trên các cây con
    for (auto [v, w] : adj[cent]) {
        if (!removed[v]) {
            result += count_paths_with_sum(v, k);
        }
    }
    
    return result;
}
```

### 9.4. Kỹ thuật Chia để trị cho bài toán dãy số

#### Bài toán: Tìm cặp nghịch thế lớn nhất chia khoảng

```cpp
#include <bits/stdc++.h>
using namespace std;

// Tìm số cặp (i, j) sao cho i < j và a[i] > a[j]
long long count_inversions(vector<int>& arr, int l, int r) {
    if (l >= r) return 0;
    
    int mid = (l + r) / 2;
    long long count = count_inversions(arr, l, mid) + 
                     count_inversions(arr, mid + 1, r);
    
    // Merge và đếm nghịch thế
    vector<int> temp(r - l + 1);
    int i = l, j = mid + 1, k = 0;
    
    while (i <= mid && j <= r) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            // Tất cả phần tử từ i đến mid đều lớn hơn arr[j]
            count += mid - i + 1;
            temp[k++] = arr[j++];
        }
    }
    
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= r) temp[k++] = arr[j++];
    
    for (int i = l; i <= r; i++) {
        arr[i] = temp[i - l];
    }
    
    return count;
}

// Ứng dụng: Tìm số cặp i < j mà a[i] > 2*a[j]
long long count_important_inversions(vector<int>& arr, int l, int r) {
    if (l >= r) return 0;
    
    int mid = (l + r) / 2;
    long long count = count_important_inversions(arr, l, mid) + 
                     count_important_inversions(arr, mid + 1, r);
    
    // Đếm số cặp quan trọng
    int j = mid + 1;
    for (int i = l; i <= mid; i++) {
        while (j <= r && arr[i] > 2LL * arr[j]) {
            j++;
        }
        count += j - (mid + 1);
    }
    
    // Merge
    vector<int> temp(r - l + 1);
    int i = l, k = 0;
    j = mid + 1;
    
    while (i <= mid && j <= r) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }
    
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= r) temp[k++] = arr[j++];
    
    for (int i = l; i <= r; i++) {
        arr[i] = temp[i - l];
    }
    
    return count;
}
```

### 9.5. Chia để trị tối ưu hóa DP

#### Kỹ thuật Divide and Conquer Optimization
Áp dụng khi DP có dạng:
```
dp[i][j] = min_{k<j} {dp[i-1][k] + cost(k, j)}
```
và cost function thỏa mãn điều kiện quadrangle inequality.

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 5005;
const long long INF = 1e18;
long long dp[N][N], C[N][N];
int opt[N][N];

// Hàm tính cost (giả sử đã được tính trước)
void precompute_cost(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            C[i][j] = C[i][j-1] + arr[j-1]; // Ví dụ cost là tổng
        }
    }
}

void solve(int i, int l, int r, int optL, int optR) {
    if (l > r) return;
    
    int mid = (l + r) / 2;
    dp[i][mid] = INF;
    int bestK = -1;
    
    for (int k = optL; k <= min(mid-1, optR); k++) {
        long long cur = dp[i-1][k] + C[k+1][mid];
        if (cur < dp[i][mid]) {
            dp[i][mid] = cur;
            bestK = k;
        }
    }
    
    solve(i, l, mid-1, optL, bestK);
    solve(i, mid+1, r, bestK, optR);
}

// Ví dụ: Chia dãy thành k đoạn với cost tối thiểu
long long partition_dp(vector<int>& arr, int k) {
    int n = arr.size();
    precompute_cost(arr);
    
    // Khởi tạo
    for (int i = 0; i <= k; i++) {
        for (int j = 0; j <= n; j++) {
            dp[i][j] = INF;
        }
    }
    dp[0][0] = 0;
    
    for (int i = 1; i <= k; i++) {
        solve(i, 1, n, 0, n-1);
    }
    
    return dp[k][n];
}
```

**Ưu điểm của Centroid Decomposition**:
- Giảm độ phức tạp từ O(n²) xuống O(n log n) cho nhiều bài toán trên cây
- Dễ dàng kết hợp với các cấu trúc dữ liệu khác
- Ứng dụng rộng rãi trong các bài toán đếm đường đi, tìm đường đi ngắn nhất, v.v.

**Lưu ý khi sử dụng**:
- Luôn đảm bảo tính chất centroid: mỗi cây con có kích thước ≤ n/2
- Cẩn thận với việc xóa đỉnh và cập nhật trạng thái
- Sử dụng các cấu trúc dữ liệu phù hợp (map, vector) để lưu trữ thông tin

## 10. Xử lý xâu

### 10.1. KMP (Knuth-Morris-Pratt)
```cpp
#include <bits/stdc++.h>
using namespace std;

vector<int> prefix_function(string s) {
    int n = s.size();
    vector<int> pi(n, 0);
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j]) j = pi[j-1];
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}

vector<int> kmp_search(string text, string pattern) {
    string s = pattern + '#' + text;
    vector<int> pi = prefix_function(s);
    vector<int> occurrences;
    
    int pattern_len = pattern.size();
    for (int i = pattern_len + 1; i < s.size(); i++)
        if (pi[i] == pattern_len)
            occurrences.push_back(i - 2 * pattern_len);
    
    return occurrences;
}
```

### 10.2. Aho-Corasick
```cpp
#include <bits/stdc++.h>
using namespace std;

struct AhoCorasick {
    struct Node {
        map<char, int> next;
        int fail = 0;
        int output = 0;
    };
    
    vector<Node> trie;
    
    AhoCorasick() { trie.emplace_back(); }
    
    void insert(string s) {
        int u = 0;
        for (char c : s) {
            if (!trie[u].next.count(c)) {
                trie[u].next[c] = trie.size();
                trie.emplace_back();
            }
            u = trie[u].next[c];
        }
        trie[u].output++;
    }
    
    void build() {
        queue<int> q;
        for (auto [c, v] : trie[0].next) q.push(v);
        
        while (!q.empty()) {
            int u = q.front(); q.pop();
            
            for (auto [c, v] : trie[u].next) {
                int f = trie[u].fail;
                while (f && !trie[f].next.count(c)) f = trie[f].fail;
                
                if (trie[f].next.count(c)) 
                    trie[v].fail = trie[f].next[c];
                else
                    trie[v].fail = 0;
                    
                trie[v].output += trie[trie[v].fail].output;
                q.push(v);
            }
        }
    }
    
    int search(string text) {
        int u = 0, total = 0;
        for (char c : text) {
            while (u && !trie[u].next.count(c)) u = trie[u].fail;
            if (trie[u].next.count(c)) u = trie[u].next[c];
            total += trie[u].output;
        }
        return total;
    }
};
```

## 11. Kỹ thuật hai con trỏ
```cpp
#include <bits/stdc++.h>
using namespace std;

// Ví dụ: Tìm số cặp (i, j) sao cho a[i] + a[j] <= target
int two_pointers(vector<int>& arr, int target) {
    sort(arr.begin(), arr.end());
    int n = arr.size();
    int count = 0;
    int j = n - 1;
    
    for (int i = 0; i < n; i++) {
        while (j > i && arr[i] + arr[j] > target) j--;
        if (j <= i) break;
        count += j - i;
    }
    return count;
}

// Ví dụ: Tìm đoạn con có tổng bằng S
void subarray_sum(vector<int>& arr, int S) {
    int n = arr.size();
    int left = 0, sum = 0;
    
    for (int right = 0; right < n; right++) {
        sum += arr[right];
        while (sum > S && left <= right) {
            sum -= arr[left];
            left++;
        }
        if (sum == S) {
            // Tìm thấy đoạn [left, right]
            cout << left << " " << right << endl;
        }
    }
}
```

## 12. Hashing
```cpp
#include <bits/stdc++.h>
using namespace std;

struct StringHash {
    const int base = 31;
    const int mod1 = 1e9+7, mod2 = 1e9+9;
    vector<long long> pow1, pow2, hash1, hash2;
    
    StringHash(string s) {
        int n = s.size();
        pow1.resize(n+1); pow2.resize(n+1);
        hash1.resize(n+1); hash2.resize(n+1);
        
        pow1[0] = pow2[0] = 1;
        for (int i = 0; i < n; i++) {
            pow1[i+1] = pow1[i] * base % mod1;
            pow2[i+1] = pow2[i] * base % mod2;
            hash1[i+1] = (hash1[i] * base + s[i]) % mod1;
            hash2[i+1] = (hash2[i] * base + s[i]) % mod2;
        }
    }
    
    pair<long long, long long> get_hash(int l, int r) {
        // [l, r] 0-based
        long long h1 = (hash1[r+1] - hash1[l] * pow1[r-l+1]) % mod1;
        long long h2 = (hash2[r+1] - hash2[l] * pow2[r-l+1]) % mod2;
        if (h1 < 0) h1 += mod1;
        if (h2 < 0) h2 += mod2;
        return {h1, h2};
    }
};
```

## 13. Game Theory
```cpp
#include <bits/stdc++.h>
using namespace std;

// Grundy numbers cho game Nim
int mex(unordered_set<int>& s) {
    int m = 0;
    while (s.count(m)) m++;
    return m;
}

vector<int> grundy_numbers(int n, vector<int>& moves) {
    vector<int> dp(n+1, 0);
    for (int i = 1; i <= n; i++) {
        unordered_set<int> s;
        for (int move : moves) {
            if (i >= move) s.insert(dp[i - move]);
        }
        dp[i] = mex(s);
    }
    return dp;
}

// Sprague-Grundy Theorem
int combined_game(vector<int>& piles, vector<int>& moves) {
    auto grundy = grundy_numbers(*max_element(piles.begin(), piles.end()), moves);
    int xor_sum = 0;
    for (int pile : piles) xor_sum ^= grundy[pile];
    return xor_sum; // != 0: first player wins
}
```


## 14. Persistent Data Structures

### 14.1. Persistent Segment Tree
```cpp
#include <bits/stdc++.h>
using namespace std;

struct Node {
    int left, right;
    int sum;
    Node() : left(0), right(0), sum(0) {}
};

const int N = 1e5;
Node tree[32 * N]; // Đủ cho persistent segment tree
int roots[N], a[N];
int next_node = 1;

int build(int l, int r) {
    int id = next_node++;
    if (l == r) {
        tree[id].sum = a[l];
        return id;
    }
    int mid = (l + r) / 2;
    tree[id].left = build(l, mid);
    tree[id].right = build(mid+1, r);
    tree[id].sum = tree[tree[id].left].sum + tree[tree[id].right].sum;
    return id;
}

int update(int prev, int l, int r, int pos, int val) {
    int id = next_node++;
    tree[id] = tree[prev];
    if (l == r) {
        tree[id].sum = val;
        return id;
    }
    int mid = (l + r) / 2;
    if (pos <= mid)
        tree[id].left = update(tree[prev].left, l, mid, pos, val);
    else
        tree[id].right = update(tree[prev].right, mid+1, r, pos, val);
    tree[id].sum = tree[tree[id].left].sum + tree[tree[id].right].sum;
    return id;
}

int query(int id, int l, int r, int ql, int qr) {
    if (ql > r || qr < l) return 0;
    if (ql <= l && r <= qr) return tree[id].sum;
    int mid = (l + r) / 2;
    return query(tree[id].left, l, mid, ql, qr) +
           query(tree[id].right, mid+1, r, ql, qr);
}

// Sử dụng:
// roots[0] = build(0, n-1);
// roots[1] = update(roots[0], 0, n-1, pos, val);
// query(roots[version], 0, n-1, ql, qr);
```

## 15. Heavy-Light Decomposition (HLD)

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;
vector<int> adj[N];
int parent[N], depth[N], heavy[N], head[N], pos[N];
int cur_pos;

int dfs(int u) {
    int size = 1;
    int max_c_size = 0;
    for (int v : adj[u]) {
        if (v != parent[u]) {
            parent[v] = u;
            depth[v] = depth[u] + 1;
            int c_size = dfs(v);
            size += c_size;
            if (c_size > max_c_size) {
                max_c_size = c_size;
                heavy[u] = v;
            }
        }
    }
    return size;
}

void decompose(int u, int h) {
    head[u] = h;
    pos[u] = cur_pos++;
    if (heavy[u] != -1)
        decompose(heavy[u], h);
    for (int v : adj[u]) {
        if (v != parent[u] && v != heavy[u])
            decompose(v, v);
    }
}

void init() {
    cur_pos = 0;
    memset(heavy, -1, sizeof heavy);
    dfs(0);
    decompose(0, 0);
}

int query(int a, int b) {
    int res = 0;
    for (; head[a] != head[b]; b = parent[head[b]]) {
        if (depth[head[a]] > depth[head[b]]) swap(a, b);
        // Thực hiện truy vấn từ pos[head[b]] đến pos[b]
        // res = max(res, segment_tree_query(pos[head[b]], pos[b]));
    }
    if (depth[a] > depth[b]) swap(a, b);
    // Thực hiện truy vấn từ pos[a] đến pos[b]
    // res = max(res, segment_tree_query(pos[a], pos[b]));
    return res;
}
```

## 16. Bao lồi (Convex Hull) và Convex Hull Trick

### 16.1. Convex Hull (Monotone Chain)
```cpp
#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
    Point() {}
    Point(long long x, long long y) : x(x), y(y) {}
    Point operator - (const Point &p) const {
        return Point(x - p.x, y - p.y);
    }
    long long cross(const Point &p) const {
        return x * p.y - y * p.x;
    }
    bool operator < (const Point &p) const {
        return x < p.x || (x == p.x && y < p.y);
    }
};

vector<Point> convex_hull(vector<Point> points) {
    int n = points.size();
    if (n <= 1) return points;
    sort(points.begin(), points.end());
    vector<Point> hull;
    for (int i = 0; i < n; i++) {
        while (hull.size() >= 2 && 
               (hull.back() - hull[hull.size()-2]).cross(points[i] - hull.back()) <= 0)
            hull.pop_back();
        hull.push_back(points[i]);
    }
    int lower_hull_size = hull.size();
    for (int i = n-2; i >= 0; i--) {
        while (hull.size() > lower_hull_size && 
               (hull.back() - hull[hull.size()-2]).cross(points[i] - hull.back()) <= 0)
            hull.pop_back();
        hull.push_back(points[i]);
    }
    hull.pop_back(); // Điểm đầu được lặp lại
    return hull;
}
```

### 16.2. Convex Hull Trick (Line Container)
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

## 17. Bao hàm loại trừ (Inclusion-Exclusion)

```cpp
#include <bits/stdc++.h>
using namespace std;

// Ví dụ: Đếm số số trong [1, n] chia hết cho ít nhất một số trong mảng primes
long long inclusion_exclusion(long long n, vector<long long>& primes) {
    long long result = 0;
    int k = primes.size();
    for (int mask = 1; mask < (1 << k); mask++) {
        long long product = 1;
        int bits = 0;
        for (int i = 0; i < k; i++) {
            if (mask & (1 << i)) {
                product *= primes[i];
                bits++;
            }
        }
        if (bits % 2 == 1)
            result += n / product;
        else
            result -= n / product;
    }
    return result;
}
```

## 18. Quy hoạch động trên DAG

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

## 19. Quy hoạch động Chia để trị

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

## 20. Một số kĩ thuật tối ưu hóa QHĐ

### 20.1. Knuth Optimization
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

## 21. Kĩ thuật Bao lồi trong QHĐ (Convex Hull Trick)

Đã có ở phần 16.2.

## 22. Quy hoạch động trên cây

Đã có ví dụ ở phần 1.2.

## 23. Quy hoạch động SOS (Sum Over Subsets)

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

## 24. Disjoint Set Union (DSU)

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;
int parent[N], rank_[N];

void make_set(int v) {
    parent[v] = v;
    rank_[v] = 0;
}

int find_set(int v) {
    if (v == parent[v]) return v;
    return parent[v] = find_set(parent[v]);
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (rank_[a] < rank_[b]) swap(a, b);
        parent[b] = a;
        if (rank_[a] == rank_[b]) rank_[a]++;
    }
}
```

## 25. Khớp, cầu. Tìm thành phần liên thông (không trọng số) và thành phần liên thông mạnh.

### 25.1. Tìm khớp và cầu
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;
vector<int> adj[N];
int low[N], disc[N], parent[N];
bool articulation[N];
vector<pair<int, int>> bridges;
int timer;

void dfs(int u) {
    disc[u] = low[u] = ++timer;
    int children = 0;
    for (int v : adj[u]) {
        if (disc[v] == 0) {
            children++;
            parent[v] = u;
            dfs(v);
            low[u] = min(low[u], low[v]);
            
            // Kiểm tra khớp
            if (parent[u] == -1 && children > 1)
                articulation[u] = true;
            if (parent[u] != -1 && low[v] >= disc[u])
                articulation[u] = true;
                
            // Kiểm tra cầu
            if (low[v] > disc[u])
                bridges.push_back({u, v});
        } else if (v != parent[u]) {
            low[u] = min(low[u], disc[v]);
        }
    }
}

void find_articulation_bridges(int n) {
    timer = 0;
    memset(disc, 0, sizeof disc);
    memset(parent, -1, sizeof parent);
    memset(articulation, false, sizeof articulation);
    bridges.clear();
    for (int i = 0; i < n; i++) {
        if (disc[i] == 0) dfs(i);
    }
}
```

### 25.2. Thành phần liên thông mạnh (Tarjan)
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;
vector<int> adj[N];
int low[N], disc[N], comp[N];
bool in_stack[N];
stack<int> st;
int timer, comp_count;

void tarjan(int u) {
    low[u] = disc[u] = ++timer;
    st.push(u);
    in_stack[u] = true;
    for (int v : adj[u]) {
        if (disc[v] == 0) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (in_stack[v]) {
            low[u] = min(low[u], disc[v]);
        }
    }
    if (low[u] == disc[u]) {
        comp_count++;
        while (true) {
            int v = st.top(); st.pop();
            in_stack[v] = false;
            comp[v] = comp_count;
            if (v == u) break;
        }
    }
}

void scc(int n) {
    timer = comp_count = 0;
    memset(disc, 0, sizeof disc);
    for (int i = 0; i < n; i++) {
        if (disc[i] == 0) tarjan(i);
    }
}
```

## 26. DSU rollback

```cpp
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent, rank;
    stack<tuple<int, int, int, int>> history;
    
    DSU(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    
    int find(int x) {
        while (parent[x] != x) x = parent[x];
        return x;
    }
    
    bool unite(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        if (rank[x] < rank[y]) swap(x, y);
        history.push({y, parent[y], x, rank[x]});
        parent[y] = x;
        if (rank[x] == rank[y]) rank[x]++;
        return true;
    }
    
    void snapshot() {
        history = stack<tuple<int, int, int, int>>();
    }
    
    void rollback() {
        while (!history.empty()) {
            auto [y, parent_y, x, rank_x] = history.top(); history.pop();
            parent[y] = parent_y;
            rank[x] = rank_x;
        }
    }
};
```

## 27. Modulo cơ bản và các biến thể khó

### 27.1. Modulo với số mũ lớn (Định lý Euler)
```cpp
#include <bits/stdc++.h>
using namespace std;

long long phi(long long n) {
    long long result = n;
    for (long long p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            while (n % p == 0) n /= p;
            result -= result / p;
        }
    }
    if (n > 1) result -= result / n;
    return result;
}

long long mod_pow(long long a, long long b, long long mod) {
    long long res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

long long mod_pow_big(long long a, long long b, long long mod) {
    // Sử dụng định lý Euler khi a và mod nguyên tố cùng nhau
    if (__gcd(a, mod) == 1) {
        long long phi_mod = phi(mod);
        b = b % phi_mod;
    }
    return mod_pow(a, b, mod);
}
```

## 28. Ước chung lớn nhất & Thuật toán Euclid (và các biến thể khó)

### 28.1. Euclid mở rộng
```cpp
#include <bits/stdc++.h>
using namespace std;

long long extended_gcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long x1, y1;
    long long g = extended_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}
```

## 29. Lũy thừa nhị phân (và các biến thể khó)

Đã có ở phần trước.

## 30. Sàng nguyên tố (và các biến thể khó)

### 30.1. Sàng nguyên tố tuyến tính
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e7;
vector<int> primes;
int spf[N]; // smallest prime factor

void linear_sieve() {
    for (int i = 2; i < N; i++) {
        if (spf[i] == 0) {
            spf[i] = i;
            primes.push_back(i);
        }
        for (int p : primes) {
            if (p > spf[i] || i * p >= N) break;
            spf[i * p] = p;
        }
    }
}
```

## 31. Nghịch đảo modulo (và các biến thể khó)

Đã có ở phần trước.

## 32. Kiểm tra số nguyên tố (và các biến thể khó)

### 32.1. Miller-Rabin
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll mulmod(ll a, ll b, ll mod) {
    ll res = 0;
    while (b) {
        if (b & 1) res = (res + a) % mod;
        a = (a * 2) % mod;
        b >>= 1;
    }
    return res;
}

ll powmod(ll a, ll b, ll mod) {
    ll res = 1;
    while (b) {
        if (b & 1) res = mulmod(res, a, mod);
        a = mulmod(a, a, mod);
        b >>= 1;
    }
    return res;
}

bool miller_rabin(ll n, int iterations = 5) {
    if (n < 4) return n == 2 || n == 3;
    for (int i = 0; i < iterations; i++) {
        ll a = 2 + rand() % (n - 3);
        if (powmod(a, n - 1, n) != 1) return false;
    }
    return true;
}
```

## 33. Phân tích thừa số nguyên tố (và các biến thể khó)

Đã có ở phần trước.

## 34. Định lý số học

### 34.1. Định lý Wilson
```cpp
// (p-1)! ≡ -1 (mod p) với p là số nguyên tố
bool wilson_theorem(int p) {
    if (p < 2) return false;
    long long fact = 1;
    for (int i = 2; i < p; i++) {
        fact = (fact * i) % p;
    }
    return (fact == p - 1);
}
```

### 34.2. Định lý Lucas
```cpp
#include <bits/stdc++.h>
using namespace std;

long long nCk_mod_p(long long n, long long k, long long p) {
    if (k == 0) return 1;
    long long ni = n % p, ki = k % p;
    if (ni < ki) return 0;
    return nCk_mod_p(n / p, k / p, p) * nCk_mod_p(ni, ki, p) % p;
}
```

### 34.3. Định lý Thặng dư Trung Hoa (CRT)

Đã có ở phần trước.

## 35. Nhân ma trận (cho dp và xử lý đồ thị)

Đã có ở phần trước.

## 36. Chi tiết về hàm sinh

```cpp
// Ví dụ: Hàm sinh cho dãy Fibonacci
// F(x) = x / (1 - x - x^2)
```

## 37. Các lý thuyết trò chơi

### 37.1. Grundy Number (Đã có ở phần trước)
### 37.2. Nim và các biến thể
```cpp
#include <bits/stdc++.h>
using namespace std;

// Nim cơ bản
bool nim_win(vector<int> piles) {
    int xor_sum = 0;
    for (int pile : piles) xor_sum ^= pile;
    return xor_sum != 0;
}

// Misère Nim: thua khi tất cả pile có 1 viên và số pile lẻ
bool misere_nim_win(vector<int> piles) {
    int xor_sum = 0;
    bool all_one = true;
    for (int pile : piles) {
        xor_sum ^= pile;
        if (pile > 1) all_one = false;
    }
    if (all_one) return piles.size() % 2 == 0;
    return xor_sum != 0;
}
```