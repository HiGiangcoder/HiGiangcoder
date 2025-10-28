#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

// Biến toàn cục để tiện cho việc đệ quy
int n, m;
vector<vector<int>> adj;
vector<bool> visited;
vector<int> path;

// Hàm đệ quy quay lui để tìm đường đi
bool find_hamiltonian_path(int u, int count) {
    // 1. Thêm đỉnh hiện tại u vào đường đi và đánh dấu đã thăm
    path.push_back(u);
    visited[u] = true;

    // 2. Nếu đã đi qua đủ n đỉnh, ta đã tìm thấy lời giải
    if (count == n) {
        return true;
    }

    // 3. Thử đi đến các đỉnh kề v chưa được thăm
    for (int v : adj[u]) {
        if (!visited[v]) {
            // Nếu việc đi tiếp từ v tìm được lời giải, trả về true luôn
            if (find_hamiltonian_path(v, count + 1)) {
                return true;
            }
        }
    }

    // 4. Quay lui: Nếu không có đường đi nào từ u dẫn đến lời giải,
    // ta xóa u khỏi đường đi và bỏ đánh dấu đã thăm để thử nhánh khác
    visited[u] = false;
    path.pop_back();
    
    return false;
}

int main() {
    // Tăng tốc độ nhập xuất
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;

    adj.resize(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    // Xử lý trường hợp biên n = 1
    if (n == 1) {
        cout << 1 << "\n";
        return 0;
    }

    // Thử bắt đầu từ mỗi đỉnh i từ 1 đến n
    for (int i = 1; i <= n; ++i) {
        visited.assign(n + 1, false);
        path.clear();
        
        if (find_hamiltonian_path(i, 1)) {
            // Nếu tìm thấy, in ra đường đi và kết thúc
            for (int j = 0; j < path.size(); ++j) {
                cout << path[j] << (j == path.size() - 1 ? "" : " ");
            }
            cout << "\n";
            return 0;
        }
    }

    // Nếu vòng lặp kết thúc mà không tìm thấy đường đi nào
    cout << -1 << "\n";

    return 0;
}