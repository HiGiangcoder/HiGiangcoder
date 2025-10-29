#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    long long expected = ans.readLong();     // Đáp án chuẩn
    long long contestant = ouf.readLong();   // Output của thí sinh

    if (expected == contestant)
        quitf(_ok, "Correct answer");
    else
        quitf(_wa, "Expected %lld, found %lld", expected, contestant);
}
