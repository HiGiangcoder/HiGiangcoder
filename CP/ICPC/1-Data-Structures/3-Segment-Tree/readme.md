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