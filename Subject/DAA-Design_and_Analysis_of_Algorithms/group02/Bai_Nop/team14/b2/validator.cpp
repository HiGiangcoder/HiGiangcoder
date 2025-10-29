// validator.cpp
#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(0, 200000, "m");
    inf.readEoln();

    for (int i = 0; i < m; i++) {
        int u = inf.readInt(1, n, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "v_i");
        inf.readSpace();
        long long w = inf.readLong(1, 1000000000LL, "w_i");
        inf.readEoln();
    }

    inf.readEof();
}
