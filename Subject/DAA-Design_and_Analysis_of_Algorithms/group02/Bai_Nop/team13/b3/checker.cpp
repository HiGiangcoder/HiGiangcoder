#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();

    // Đọc đồ thị
    vector<vector<bool>> adj(n+1, vector<bool>(n+1,false));
    for (int i = 0; i < m; i++) {
        int u = inf.readInt();
        int v = inf.readInt();
        adj[u][v] = adj[v][u] = true;
    }

    // Đọc đáp án mẫu
    int correct = ans.readInt();

    // Đọc output thí sinh
    int first = ouf.readInt();

    // Trường hợp thí sinh báo không có Hamiltonian
    if (first == -1) {
        if (correct != -1)
            quitf(_wa, "Expected a path, but contestant outputs -1");
        quitf(_ok, "Correctly reports no Hamiltonian path");
    }
    // Mẫu là -1 mà thí sinh đưa path
    if (correct == -1)
        quitf(_wa, "Expected -1, but contestant outputs a path");

    // Đọc đường đi độ dài n
    vector<int> path(n);
    set<int> seen;
    path[0] = first;
    seen.insert(first);

    for (int i = 1; i < n; i++) {
        path[i] = ouf.readInt();
        if (!seen.insert(path[i]).second)
            quitf(_wa, "Vertex %d appears more than once", path[i]);
    }

    // Chỉ cần gọi readEof(): nếu còn bất kỳ ký tự không phải whitespace nào, nó sẽ ném -> WA
    // try {
    //     ouf.readEof();
    // } catch(...) {
    //     quitf(_wa, "Extra data after reading %d vertices", n);
    // }

    // Đảm bảo đủ n đỉnh
    if ((int)seen.size() != n)
        quitf(_wa, "Path does not cover all vertices");

    // Kiểm tra cạnh giữa các đỉnh kề nhau
    for (int i = 0; i + 1 < n; i++) {
        int u = path[i], v = path[i+1];
        if (!adj[u][v])
            quitf(_wa, "No edge between %d and %d", u, v);
    }

    quitf(_ok, "Valid Hamiltonian path");
}
