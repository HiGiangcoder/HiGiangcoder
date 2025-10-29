#include "testlib.h"
#include <iostream>
#include <limits>
#include <cmath>

using namespace std;

typedef long long ll;

const double EPS = 1e-9;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    // Đọc input
    int n = inf.readInt();
    int m = inf.readInt();
    for (int i = 0; i < m; ++i) {
        inf.readInt(); inf.readInt(); inf.readLong();
    }
    
    // Đọc kết quả mong đợi
    ll expected = ans.readLong();
    
    // Đọc kết quả thí sinh
    ll contestant = ouf.readLong();
    
    // Kiểm tra định dạng
    // ouf.readEof();
    
    // So sánh kết quả
    if (expected == contestant) {
        quitf(_ok, "Đúng: %lld", expected);
    } else {
        // Kiểm tra trường hợp đặc biệt
        if (expected == -1 && contestant != -1) {
            quitf(_wa, "Sai: Mong đợi -1 (không có đường đi), nhưng nhận được %lld", contestant);
        } else if (contestant == -1 && expected != -1) {
            quitf(_wa, "Sai: Có đường đi độ dài %lld, nhưng output là -1", expected);
        } else {
            ll diff = abs(expected - contestant);
            if (diff > 0) {
                double relative_error = (double)diff / abs(expected);
                if (relative_error > EPS) {
                    quitf(_wa, "Sai: Mong đợi %lld, nhận được %lld (sai số %lld)", 
                          expected, contestant, diff);
                } else {
                    // Cho phép sai số nhỏ do floating point
                    quitf(_ok, "Chấp nhận được: %lld (sai số rất nhỏ)", contestant);
                }
            }
        }
    }
    
    return 0;
}