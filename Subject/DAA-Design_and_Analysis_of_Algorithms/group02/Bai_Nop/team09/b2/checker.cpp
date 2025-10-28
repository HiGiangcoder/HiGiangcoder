#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    long long contestant = ouf.readLong();
    long long correct = ans.readLong();
    if (contestant != correct)
        quitf(_wa, "Wrong Answer!");
    quitf(_ok, "Correct");
}
