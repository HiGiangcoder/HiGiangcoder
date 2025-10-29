#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt();
    int m = inf.readInt();
    for (int i=0;i<m;i++){
        int l = inf.readInt();
        int r = inf.readInt();
        int w = inf.readInt();
        // int correct = *max_element(a.begin()+l-1, a.begin()+r);

    }
    // int correct = ans.readInt(); <--- bug
    // int contestant = ouf.readInt(); <--- bug
    long long correct = ans.readLong();
    long long contestant = ouf.readLong();
    
    if (contestant != correct)
        quitf(_wa, "Query %d: expected %lld, found %lld", 1, correct, contestant);

    quitf(_ok, "All queries correct");
}
