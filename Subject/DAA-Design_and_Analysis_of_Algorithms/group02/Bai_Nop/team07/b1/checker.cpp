#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    long long correct = ans.readLong();
    long long contestant = ouf.readLong();
    if (contestant != correct)
        quitf(_wa, "Expected %lld, found %lld", correct, contestant);
    quitf(_ok, "All queries correct");
}
