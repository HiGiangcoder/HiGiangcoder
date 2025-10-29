#include "testlib.h"

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    long long jans = ans.readLong();
    long long pans = ouf.readLong();

    if (jans == pans) {
        quitf(_ok, "Correct: %lld", jans);
    } else {
        quitf(_wa, "Wrong answer, expected %lld, found %lld", jans, pans);
    }

    return 0;
}