#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    long long sumInput = 0;
    for (int i = 0; i < n; ++i) {
        long long a = inf.readLong(-100000LL, 100000LL, "a[i]");
        sumInput += a;
    }

    long long correct = ans.readLong();       // đáp án mẫu (solution tạo)
    long long contestant = ouf.readLong();    // thí sinh

    if (contestant != correct)
        quitf(_wa, "Expected sum=%lld, found %lld", correct, contestant);

    
    // cho phép chỉ whitespace sau output
    ouf.skipBlanks();
    if (!ouf.seekEof())
        quitf(_wa, "Extra tokens after answer");
    quitf(_ok, "OK");
}
