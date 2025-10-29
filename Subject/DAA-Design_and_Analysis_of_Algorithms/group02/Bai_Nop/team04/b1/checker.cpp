#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        a[i] = inf.readInt(-100000, 100000, "a[i]");

    long long correct = ans.readLong();
    long long contestant = ouf.readLong();

    if (contestant != correct)
        quitf(_wa, "Expected %lld, found %lld", correct, contestant);

    quitf(_ok, "Output is correct");
}

