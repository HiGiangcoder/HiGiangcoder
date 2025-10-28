#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");  // đọc n, kiểm tra giới hạn
    inf.readEoln();

    for (int i = 0; i < n; i++) {
        inf.readInt(-100000, 100000, "ai"); // đọc ai, kiểm tra giới hạn
        if (i + 1 < n) inf.readSpace();
    }
    inf.readEoln();

    inf.readEof(); // đảm bảo không có dữ liệu thừa
}
