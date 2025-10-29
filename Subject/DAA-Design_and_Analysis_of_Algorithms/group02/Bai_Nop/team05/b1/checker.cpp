#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readLong();
    vector<int> a(n);
    for (int i=0;i<n;i++) a[i] = inf.readLong();

        long long correct = ans.readLong();
        long long contestant = ouf.readLong();
        if (contestant != correct)
            quitf(_wa, "Wrong output: expected %d, found %d", correct, contestant);
    quitf(_ok, "All queries correct");
}
