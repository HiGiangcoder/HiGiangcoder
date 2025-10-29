#include <bits/stdc++.h>
using namespace std;

/*
  Thuật toán tìm một đường đi Hamilton trong đồ thị vô hướng
  Sử dụng Dynamic Programming + Bitmask + Parent Tracking
  Độ phức tạp: O(N^2 * 2^N), N ≤ ~20
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    vector<vector<int>> adj(N + 3);
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        // Giả sử đầu vào đỉnh đánh số 0..N-1
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int FULL_MASK = (1 << N) - 1;
    // dp[mask][v] = true nếu tồn tại đường đi qua tập mask và kết thúc tại v
    vector<vector<bool>> dp((1 << N) + 3, vector<bool>(N + 3, false));
    // parent[mask][v] = u lưu đỉnh trước v trong đường đi mask->v
    vector<vector<int>> parent((1 << N) + 3, vector<int>(N + 3, -1));

    // Khởi tạo: mỗi đỉnh i tự nó là đường đi độ dài 1
    for (int i = 0; i < N; i++) {
        dp[1 << i][i] = true;
    }

    // Duyệt từng mask
    for (int mask = 0; mask <= FULL_MASK; mask++) {
        for (int v = 0; v < N; v++) {
            if (!dp[mask][v]) continue;
            // Từ v đi tới các u chưa có trong mask
            for (int u : adj[v]) {
                if (mask & (1 << u)) continue;
                int nextMask = mask | (1 << u);
                if (!dp[nextMask][u]) {
                    dp[nextMask][u] = true;
                    parent[nextMask][u] = v;
                }
            }
        }
    }

    // Tìm vị trí kết thúc của đường đi Hamilton (mask đầy đủ)
    int endV = -1;
    for (int v = 0; v < N; v++) {
        if (dp[FULL_MASK][v]) {
            endV = v;
            break;
        }
    }

    if (endV == -1) {
        cout << -1 ;
        return 0;
    }

    // Khôi phục đường đi
    vector<int> path;
    int mask = FULL_MASK;
    int v = endV;
    while (v != -1) {
        path.push_back(v);
        int p = parent[mask][v];
        mask ^= (1 << v);
        v = p;
    }
    reverse(path.begin(), path.end());

    // In đường đi Hamilton
    for (int x : path) {
        cout << x + 1<< " ";
    }
    return 0;
}
