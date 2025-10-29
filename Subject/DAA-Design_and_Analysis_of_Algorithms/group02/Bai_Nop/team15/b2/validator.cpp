#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Đọc dòng đầu tiên: n và m
    int n = inf.readInt(2, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(0, 200000, "m");
    inf.readEoln();

    // Đọc m dòng tiếp theo, mỗi dòng chứa một cạnh u, v, w
    for (int i = 0; i < m; i++) {
        // Đọc đỉnh bắt đầu u
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        
        // Đọc đỉnh kết thúc v
        int v = inf.readInt(1, n, "v");
        inf.readSpace();

        // Đọc trọng số w
        int w = inf.readInt(1, 1e9, "w");
        inf.readEoln();
    }

    // Đảm bảo đã đọc hết file và không có dữ liệu thừa
    inf.readEof();
}