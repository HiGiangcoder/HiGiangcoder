#include "testlib.h"
#include <vector>

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln(); 

    std::vector<int> a = inf.readInts(n, -100000, 100000, "a");

    inf.readEoln(); 

    inf.readEof();

    return 0;
}