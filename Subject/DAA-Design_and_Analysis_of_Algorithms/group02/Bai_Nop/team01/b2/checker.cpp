#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt();
    int m = inf.readInt();
    vector<pair<pair<int, int>, int>> a(m+10);
    for (int i=0;i<m;i++) {
        a[i].first.first = inf.readInt();
        a[i].first.second = inf.readInt();
        a[i].second = inf.readInt();
    }
    long long correct = ans.readLong();
    long long contestant = ouf.readLong();
    if (!ouf.seekEof())  // kiểm tra xem còn dữ liệu thừa không
        quitf(_fail, "Extra data found in contestant output");
    if (contestant != correct){
        quitf(_wa, "Answer: expected %d, found %d", correct, contestant);
    }
    quitf(_ok, "Answer correct");
}
