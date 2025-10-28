#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    
    // int correct = ans.readInt(); // <--- bug
    // int contestant = ouf.readInt(); // <--- bug
    long long correct = ans.readLong();
    long long contestant = ouf.readLong();

    if (contestant != correct)
        quitf(_wa, "user's answer is not equal to judge's answer");
    
    quitf(_ok, "All queries correct");
}
