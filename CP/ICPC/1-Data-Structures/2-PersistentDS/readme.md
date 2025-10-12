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