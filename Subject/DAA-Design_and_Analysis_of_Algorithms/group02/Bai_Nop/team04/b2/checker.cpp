#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    // consume input to match format (not used afterwards)
    int n = inf.readInt();
    int m = inf.readInt();
    for (int i = 0; i < m; ++i) {
        inf.readInt();
        inf.readInt();
        inf.readLong();
    }

    long long jury = ans.readLong();
    if (!ans.eof())
        ans.readEoln();
    // ans.readEof();

    long long participant = ouf.readLong();
    if (!ouf.eof())
        ouf.readEoln();
    // ouf.readEof();

    if (participant != jury) {
        quitf(_wa, "Expected %lld, found %lld", jury, participant);
    }

    quitf(_ok, "Answer matches");
}
