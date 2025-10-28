#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(0, 200000, "m");
    inf.readEoln();

    for (int i = 0; i < m; ++i) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readSpace();
        int w = inf.readInt(1, 1000000000, "w");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}