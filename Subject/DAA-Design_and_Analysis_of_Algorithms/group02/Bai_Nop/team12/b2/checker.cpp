#include "../testlib.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    // Khởi tạo checker với 3 luồng file: input, output của thí sinh, output của đáp án
    registerTestlibCmd(argc, argv);

    // Đọc kết quả từ file đáp án chuẩn (luồng ans)
    // Phải dùng readLong() vì khoảng cách có thể rất lớn
    long long jury_answer = ans.readLong();

    // Đọc kết quả từ file output của thí sinh (luồng ouf)
    long long contestant_answer = ouf.readLong();

    // So sánh hai kết quả
    if (contestant_answer == jury_answer) {
        // Kiểm tra xem thí sinh có in thừa dữ liệu gì không
        // Nếu có, checker sẽ báo lỗi. Nếu không, nó sẽ không làm gì cả.
        ouf.seekEof();

        // Nếu khớp, trả về verdict OK (Accepted)
        // Script python sẽ nhận được return code 0
        if (jury_answer == -1) {
            quitf(_ok, "Correct: No path found");
        } else {
            quitf(_ok, "Correct distance: %lld", jury_answer);
        }
    } else {
        // Nếu không khớp, trả về verdict WA (Wrong Answer)
        // Script python sẽ nhận được return code khác 0
        quitf(_wa, "Incorrect distance. Expected %lld, found %lld", jury_answer, contestant_answer);
    }

    return 0;
}