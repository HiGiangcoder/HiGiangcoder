# Graph Theory

## 1. Disjoint Set Union (DSU)

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

## 2. DSU rollback

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

## 3. Tìm khớp và cầu
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

### 4. Thành phần liên thông mạnh (Tarjan)
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

## 5. Graph Theory
### 5.1. DSU và DSU rollback
### 5.2. Sắp xếp topo
### 5.3. Đường đi, chu trình Euler
### 5.4. Xử lý chu trình âm
### 5.5. 2-sat
---
### 5.6. Luồng cực đại.
---
### 5.7. LCA, RMQ trên cây
### 5.8. Heavy Light Decomposition
### 5.9. Centroid Decomposition
