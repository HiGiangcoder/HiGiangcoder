#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    // Đọc input (xác thực cấu trúc)
    int n = inf.readInt(2, 100000, "n");
    int m = inf.readInt(0, 200000, "m");
    for (int i = 0; i < m; ++i) {
        inf.readInt(1, n, "u");
        inf.readInt(1, n, "v");
        inf.readLong(1, 1000000000LL, "w");
    }

    long long correct    = ans.readLong();    // -1 nếu không có đường
    long long contestant = ouf.readLong();

    if (contestant != correct)
        quitf(_wa, "Shortest path expected %lld, found %lld", correct, contestant);

    // Chặn token thừa nhưng cho phép whitespace cuối
    ouf.skipBlanks();
    // ouf.readEof();

    quitf(_ok, "OK");
}
