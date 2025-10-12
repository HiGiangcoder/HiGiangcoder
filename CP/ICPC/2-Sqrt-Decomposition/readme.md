# Chia căn (Square Root Decomposition)

### 1. Ý tưởng cơ bản
Chia dữ liệu thành các khối có kích thước ≈ √n, cho phép thực hiện các thao tác trong O(√n) thay vì O(n).

### 2. Ứng dụng cơ bản: Range Sum Query
```cpp
#include <bits/stdc++.h>
using namespace std;

class SQRTDecomposition {
private:
    int n, block_size, block_count;
    vector<int> arr, block_sum, lazy;

public:
    SQRTDecomposition(vector<int>& input) {
        arr = input;
        n = arr.size();
        block_size = sqrt(n);
        block_count = (n + block_size - 1) / block_size;
        block_sum.resize(block_count, 0);
        lazy.resize(block_count, 0);
        
        // Xây dựng các khối
        for (int i = 0; i < n; i++) {
            block_sum[i / block_size] += arr[i];
        }
    }
    
    void update(int idx, int val) {
        int block_id = idx / block_size;
        block_sum[block_id] += val - arr[idx];
        arr[idx] = val;
    }
    
    void range_update(int l, int r, int val) {
        int left_block = l / block_size;
        int right_block = r / block_size;
        
        if (left_block == right_block) {
            // Cùng một khối
            for (int i = l; i <= r; i++) {
                arr[i] += val;
                block_sum[left_block] += val;
            }
        } else {
            // Khối trái
            for (int i = l; i < (left_block + 1) * block_size; i++) {
                arr[i] += val;
                block_sum[left_block] += val;
            }
            // Các khối giữa
            for (int i = left_block + 1; i < right_block; i++) {
                lazy[i] += val;
            }
            // Khối phải
            for (int i = right_block * block_size; i <= r; i++) {
                arr[i] += val;
                block_sum[right_block] += val;
            }
        }
    }
    
    int query(int l, int r) {
        int sum = 0;
        int left_block = l / block_size;
        int right_block = r / block_size;
        
        if (left_block == right_block) {
            for (int i = l; i <= r; i++) {
                sum += arr[i] + lazy[left_block];
            }
        } else {
            // Khối trái
            for (int i = l; i < (left_block + 1) * block_size; i++) {
                sum += arr[i] + lazy[left_block];
            }
            // Các khối giữa
            for (int i = left_block + 1; i < right_block; i++) {
                sum += block_sum[i] + lazy[i] * block_size;
            }
            // Khối phải
            for (int i = right_block * block_size; i <= r; i++) {
                sum += arr[i] + lazy[right_block];
            }
        }
        return sum;
    }
};
```

### 3. Mo's Algorithm - Ứng dụng chia căn cho truy vấn
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
int arr[N], freq[N], answer[N];
int current_answer = 0;

struct Query {
    int l, r, idx;
    Query(int l, int r, int idx) : l(l), r(r), idx(idx) {}
};

void add(int idx) {
    freq[arr[idx]]++;
    if (freq[arr[idx]] == 1) current_answer++;
}

void remove(int idx) {
    freq[arr[idx]]--;
    if (freq[arr[idx]] == 0) current_answer--;
}

int main() {
    int n, q;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> arr[i];
    cin >> q;
    
    vector<Query> queries;
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        queries.emplace_back(l - 1, r - 1, i);
    }
    
    // Sắp xếp truy vấn theo khối
    int block_size = sqrt(n);
    sort(queries.begin(), queries.end(), [&](Query a, Query b) {
        if (a.l / block_size != b.l / block_size)
            return a.l / block_size < b.l / block_size;
        return a.r < b.r;
    });
    
    int cur_l = 0, cur_r = -1;
    for (Query query : queries) {
        while (cur_l > query.l) {
            cur_l--;
            add(cur_l);
        }
        while (cur_r < query.r) {
            cur_r++;
            add(cur_r);
        }
        while (cur_l < query.l) {
            remove(cur_l);
            cur_l++;
        }
        while (cur_r > query.r) {
            remove(cur_r);
            cur_r--;
        }
        answer[query.idx] = current_answer;
    }
    
    for (int i = 0; i < q; i++) {
        cout << answer[i] << "\n";
    }
    
    return 0;
}
```

### 4. Chia căn trên cây - Euler Tour + Mo's Algorithm
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
vector<int> adj[N];
int val[N], euler[2 * N], tin[N], tout[N];
int flat[2 * N], node_freq[N], value_freq[N];
int timer = 0;

void dfs(int u, int p) {
    tin[u] = timer;
    flat[timer] = u;
    timer++;
    for (int v : adj[u]) {
        if (v != p) dfs(v, u);
    }
    tout[u] = timer;
    flat[timer] = u;
    timer++;
}

struct TreeQuery {
    int l, r, idx, lca;
    TreeQuery(int l, int r, int idx, int lca) : l(l), r(r), idx(idx), lca(lca) {}
};

class TreeMo {
private:
    vector<TreeQuery> queries;
    int n, block_size;
    int current_answer;
    vector<int> answer;
    vector<int> node_occurrence;

public:
    TreeMo(int n) : n(n) {
        block_size = sqrt(2 * n);
        node_occurrence.resize(n, 0);
        current_answer = 0;
    }
    
    void add_query(int u, int v, int idx) {
        if (tin[u] > tin[v]) swap(u, v);
        int lca = get_lca(u, v);
        if (lca == u) {
            queries.emplace_back(tin[u], tin[v], idx, -1);
        } else {
            queries.emplace_back(tout[u], tin[v], idx, lca);
        }
    }
    
    void add(int idx) {
        int node = flat[idx];
        node_occurrence[node]++;
        if (node_occurrence[node] == 1) {
            // Thêm node vào kết quả
            value_freq[val[node]]++;
            if (value_freq[val[node]] == 1) current_answer++;
        } else {
            // Xóa node khỏi kết quả
            value_freq[val[node]]--;
            if (value_freq[val[node]] == 0) current_answer--;
        }
    }
    
    void remove(int idx) {
        int node = flat[idx];
        node_occurrence[node]--;
        if (node_occurrence[node] == 1) {
            value_freq[val[node]]++;
            if (value_freq[val[node]] == 1) current_answer++;
        } else {
            value_freq[val[node]]--;
            if (value_freq[val[node]] == 0) current_answer--;
        }
    }
    
    void process() {
        answer.resize(queries.size());
        sort(queries.begin(), queries.end(), [&](TreeQuery a, TreeQuery b) {
            if (a.l / block_size != b.l / block_size)
                return a.l / block_size < b.l / block_size;
            return a.r < b.r;
        });
        
        int cur_l = 0, cur_r = -1;
        for (auto query : queries) {
            while (cur_l > query.l) add(--cur_l);
            while (cur_r < query.r) add(++cur_r);
            while (cur_l < query.l) remove(cur_l++);
            while (cur_r > query.r) remove(cur_r--);
            
            if (query.lca != -1) add(tin[query.lca]);
            answer[query.idx] = current_answer;
            if (query.lca != -1) remove(tin[query.lca]);
        }
    }
    
    vector<int> get_answers() { return answer; }
    
    // Hàm LCA (có thể sử dụng binary lifting như đã trình bày trước đó)
    int get_lca(int u, int v) {
        // Giả sử đã có hàm LCA
        return 0; // Thay bằng implementation thực tế
    }
};
```

### 5. Chia căn cho bài toán khác: Range Minimum Query
```cpp
#include <bits/stdc++.h>
using namespace std;

class SqrtRMQ {
private:
    int n, block_size, block_count;
    vector<int> arr, block_min;
    
public:
    SqrtRMQ(vector<int>& input) {
        arr = input;
        n = arr.size();
        block_size = sqrt(n);
        block_count = (n + block_size - 1) / block_size;
        block_min.resize(block_count, INT_MAX);
        
        for (int i = 0; i < n; i++) {
            int block_id = i / block_size;
            block_min[block_id] = min(block_min[block_id], arr[i]);
        }
    }
    
    void update(int idx, int val) {
        int block_id = idx / block_size;
        arr[idx] = val;
        
        // Cập nhật lại toàn bộ khối
        int start = block_id * block_size;
        int end = min((block_id + 1) * block_size, n);
        block_min[block_id] = INT_MAX;
        for (int i = start; i < end; i++) {
            block_min[block_id] = min(block_min[block_id], arr[i]);
        }
    }
    
    int query(int l, int r) {
        int left_block = l / block_size;
        int right_block = r / block_size;
        int min_val = INT_MAX;
        
        if (left_block == right_block) {
            for (int i = l; i <= r; i++) {
                min_val = min(min_val, arr[i]);
            }
        } else {
            // Khối trái
            for (int i = l; i < (left_block + 1) * block_size; i++) {
                min_val = min(min_val, arr[i]);
            }
            // Các khối giữa
            for (int i = left_block + 1; i < right_block; i++) {
                min_val = min(min_val, block_min[i]);
            }
            // Khối phải
            for (int i = right_block * block_size; i <= r; i++) {
                min_val = min(min_val, arr[i]);
            }
        }
        return min_val;
    }
};
```

### 6. Ứng dụng nâng cao: DSU Rollback với chia căn
```cpp
#include <bits/stdc++.h>
using namespace std;

struct RollbackDSU {
    vector<int> parent, rank;
    vector<pair<int*, int>> history;
    
    RollbackDSU(int n) : parent(n), rank(n, 0) {
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
        history.emplace_back(&parent[y], parent[y]);
        history.emplace_back(&rank[x], rank[x]);
        parent[y] = x;
        if (rank[x] == rank[y]) rank[x]++;
        return true;
    }
    
    void snapshot() { history.clear(); }
    
    void rollback() {
        while (!history.empty()) {
            *history.back().first = history.back().second;
            history.pop_back();
        }
    }
};

class SqrtDSU {
private:
    int n, block_size;
    vector<RollbackDSU> dsu_blocks;
    vector<vector<pair<int, int>>> block_edges;
    
public:
    SqrtDSU(int n) : n(n) {
        block_size = sqrt(n);
        int block_count = (n + block_size - 1) / block_size;
        dsu_blocks.resize(block_count, RollbackDSU(n));
        block_edges.resize(block_count);
    }
    
    void add_edge(int u, int v, int time_block) {
        block_edges[time_block].emplace_back(u, v);
    }
    
    void process_block(int block_id) {
        auto& dsu = dsu_blocks[block_id];
        dsu.snapshot();
        
        // Thêm các cạnh từ các khối trước đó
        for (int i = 0; i < block_id; i++) {
            for (auto [u, v] : block_edges[i]) {
                dsu.unite(u, v);
            }
        }
        
        // Xử lý các cạnh trong khối hiện tại
        for (auto [u, v] : block_edges[block_id]) {
            dsu.unite(u, v);
        }
    }
    
    bool connected(int u, int v, int time) {
        int block_id = time / block_size;
        return dsu_blocks[block_id].find(u) == dsu_blocks[block_id].find(v);
    }
};
```

### 7. Ưu điểm và ứng dụng của Chia căn

**Ưu điểm**:
- Dễ cài đặt và debug
- Linh hoạt, áp dụng được cho nhiều loại bài toán
- Hiệu quả với các bài toán có √n ≤ 1000 (n ≤ 10⁶)

**Ứng dụng**:
- Xử lý truy vấn trên dãy số (sum, min, max, mode)
- Mo's algorithm cho các bài toán offline
- DSU với rollback
- Các bài toán trên cây kết hợp Euler Tour
- Phân tách truy vấn theo thời gian

**So sánh với các CTDL khác**:
- Segment Tree: O(log n) mỗi truy vấn nhưng khó cài đặt hơn
- Fenwick Tree: O(log n) nhưng chỉ hỗ trợ một số thao tác nhất định
- Chia căn: O(√n) nhưng dễ cài đặt và linh hoạt

