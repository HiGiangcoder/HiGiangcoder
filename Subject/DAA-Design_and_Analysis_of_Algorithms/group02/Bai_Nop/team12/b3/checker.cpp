#include "../testlib.h"
#include <vector>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    // Bước 1: Đọc đồ thị từ file input (inf)
    int n = inf.readInt();
    int m = inf.readInt();
    set<pair<int, int>> edges;
    for (int i = 0; i < m; i++) {
        int u = inf.readInt();
        int v = inf.readInt();
        if (u > v) swap(u, v);
        edges.insert({u, v});
    }

    // Bước 2: Đọc đáp án của giám khảo (ans) để biết có lời giải hay không
    string jury_first_token = ans.readToken();

    // --- THAY ĐỔI CHÍNH ---
    // Bước 3: Đọc output của thí sinh từng token một vào vector
    vector<int> p;
    // while (!ouf.eof()) { // <-- bug: out.eof() vẫn trả về false nếu sau số cuối cùng vẫn còn dấu cách hay xuống dòng
    while (!ouf.seekEof()) { // out.seekEof() sẽ trả về true nếu các kí tự cuối là khoảng trắng hoặc xuống dòng
        // readToken() sẽ đọc một chuỗi ký tự cho đến khi gặp khoảng trắng hoặc cuối dòng
        string token = ouf.readToken();
        if (token.empty()) {
            break; // Đã đọc hết file
        }
        
        // Cố gắng chuyển token thành số nguyên
        try {
            p.push_back(stoi(token));
        } catch (const exception& e) {
            // Nếu token không phải là số, báo lỗi Presentation Error
            quitf(_pe, "Output contains a non-integer token: '%s'", token.c_str());
        }
    }
    // ----------------------
    
    // Trường hợp 1: Đáp án chuẩn là không có đường đi
    if (jury_first_token == "-1") {
        if (p.size() == 1 && p[0] == -1) {
            quitf(_ok, "Correctly reported no path exists.");
        } else {
            quitf(_wa, "Jury found no path (-1), but contestant provided a different answer.");
        }
    }

    // Trường hợp 2: Đáp án chuẩn là có đường đi
    if (p.size() == 1 && p[0] == -1) {
        quitf(_wa, "Contestant reported no path (-1), but a solution exists.");
    }

    // Kiểm tra số lượng đỉnh trong đường đi phải bằng n
    if ((int)p.size() != n) {
        quitf(_wa, "Contestant's path has %zu vertices, but expected %d.", p.size(), n);
    }

    // Kiểm tra đường đi phải là một hoán vị của 1..N
    vector<bool> visited(n + 1, false);
    for (int node : p) {
        if (node < 1 || node > n) {
            quitf(_wa, "Path contains an invalid vertex: %d (out of range [1, %d])", node, n);
        }
        if (visited[node]) {
            quitf(_wa, "Vertex %d appears more than once in the path", node);
        }
        visited[node] = true;
    }

    // Kiểm tra giữa hai đỉnh kề nhau phải có cạnh nối
    for (size_t i = 0; i < p.size() - 1; ++i) {
        int u = p[i];
        int v = p[i+1];
        if (u > v) swap(u, v);
        if (edges.find({u, v}) == edges.end()) {
            quitf(_wa, "Path is invalid: No edge between %d and %d", p[i], p[i+1]);
        }
    }
    
    quitf(_ok, "Contestant found a valid Hamiltonian path.");

    return 0;
}