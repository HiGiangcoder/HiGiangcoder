#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt();
    int q = inf.readInt();
    vector<int> a(n);
    for (int i=0;i<n;i++) a[i] = inf.readInt();
    for (int i=0;i<q;i++){
        int l = inf.readInt();
        int r = inf.readInt();
        // int correct = *max_element(a.begin()+l-1, a.begin()+r);
        int correct = ans.readInt();
        int contestant = ouf.readInt();
        if (contestant != correct)
            quitf(_wa, "Query %d: expected %d, found %d", i+1, correct, contestant);
    }
    quitf(_ok, "All queries correct");
}
