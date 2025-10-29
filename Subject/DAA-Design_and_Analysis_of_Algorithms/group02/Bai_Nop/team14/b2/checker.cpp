// checker.cpp
#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    // Đọc output đúng (từ .ans)
    long long expected = ans.readLong(-1LL, 1000000000000000000LL, "expected");
    ans.readEoln();
    // ans.readEof();

    // Đọc output của thí sinh
    long long contestant = ouf.readLong(-1LL, 1000000000000000000LL, "contestant");
    ouf.readEoln();
    // ouf.readEof(); // Đảm bảo không còn gì sau số đó (chỉ đúng 1 dòng duy nhất)

    if (expected != contestant)
        quitf(_wa, "Wrong answer: expected %lld, found %lld", expected, contestant);
    else
        quitf(_ok, "Correct answer: %lld", contestant);
}
