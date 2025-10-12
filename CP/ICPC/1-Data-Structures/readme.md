## 1. RMQ
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

## 2. Persistent Data Structures
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

## 3. Segment Tree
### 3.1. Segment Tree 1D
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

### 3.2. Segment Tree 2D
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

## 4. Fenwick Tree
### 4.1. Fenwick Tree (BIT) 1D
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

### 4.2. Fenwick Tree (BIT) 2D
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

## 5. LiChao Tree
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
