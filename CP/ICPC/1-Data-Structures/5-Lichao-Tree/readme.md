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
