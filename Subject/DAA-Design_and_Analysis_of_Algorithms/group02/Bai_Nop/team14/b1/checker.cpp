#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();  
    for (int i = 0; i < n; i++) inf.readInt(); // đọc hết dãy, không dùng

    long long correct = ans.readLong();       // đáp án chuẩn
    long long contestant = ouf.readLong();    // output thí sinh

    if (contestant != correct) {
        quitf(_wa, "Expected %lld, found %lld", correct, contestant);
    }

    // ouf.readEof(); // kiểm tra không có dữ liệu thừa trong output

    quitf(_ok, "Correct answer: %lld", correct);
}
