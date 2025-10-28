#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt();
    vector<int> a(n+10);
    for (int i=0;i<n;i++) a[i] = inf.readInt();
    int correct = ans.readInt();
    int contestant = ouf.readInt();
    if (!ouf.seekEof())  // kiểm tra xem còn dữ liệu thừa không
        quitf(_fail, "Extra data found in contestant output");
    if (contestant != correct){
        quitf(_wa, "Answer: expected %d, found %d", correct, contestant);
    }
    quitf(_ok, "Answer correct");
}
