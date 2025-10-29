#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    inf.readSpace();
    int m = inf.readInt();
    inf.readEoln();

    // Đọc m cạnh của đồ thị
    for (int i = 0; i < m; i++) {
        inf.readInt(); 
        inf.readSpace();
        inf.readInt(); 
        inf.readSpace();
        inf.readInt(); 
        inf.readEoln();
    }
        
    long long correct = ans.readLong();
    long long contestant = ouf.readLong();

    if (contestant != correct)
        // Dùng %lld để in ra kiểu long long
        quitf(_wa, "Wrong Answer: expected %lld, found %lld", correct, contestant);
    
    // Nếu đúng, thông báo OK
    quitf(_ok, "Correct Answer");
}
