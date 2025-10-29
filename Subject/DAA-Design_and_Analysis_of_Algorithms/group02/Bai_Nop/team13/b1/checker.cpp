// checker.cpp
#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);


    // Đọc tổng từ file đáp án chuẩn
    long long correct = ans.readLong();

    // Đọc tổng từ file thí sinh
    long long contestant = ouf.readLong();

    // So sánh
    if (contestant != correct)
        quitf(_wa, "Expected %lld, found %lld", correct, contestant);

    // Nếu đúng
    quitf(_ok, "Output is correct");
}