#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt();
    vector<int> a(n);
    for (int i=0;i<n;i++) a[i] = inf.readInt();
    // int correct = ans.readInt(); // <---- bug (long long)
    // int contestant = ouf.readInt(); // <---- bug (long long)
    
    long long correct = ans.readLong();
    long long contestant = ouf.readLong();

    if (contestant != correct){
        quitf(_wa, "Expected %lld, found %lldd", correct, contestant);
    }
    else quitf(_ok, "Correct");
}
