#include "../testlib.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    // registerTestlibCmd sẽ tự động mở các file được truyền vào từ script python:
    // argv[1] (inp) -> luồng `inf` (input của test case)
    // argv[2] (out) -> luồng `ouf` (output của thí sinh)
    // argv[3] (ans) -> luồng `ans` (output của đáp án)
    registerTestlibCmd(argc, argv);

    // Đọc kết quả từ file đáp án chuẩn (luồng ans)
    // Dùng readLong() vì tổng có thể vượt quá giới hạn của int
    long long jury_answer = ans.readLong();

    // Đọc kết quả từ file output của thí sinh (luồng ouf)
    long long contestant_answer = ouf.readLong();

    // So sánh hai kết quả
    if (contestant_answer == jury_answer) {
        // Đảm bảo rằng thí sinh không in thừa dữ liệu
        // Nếu còn dữ liệu thừa, ouf.seekEof() sẽ báo lỗi
        ouf.seekEof(); 
        
        // Nếu khớp, trả về verdict OK (Accepted)
        // Script python sẽ nhận được return code 0
        quitf(_ok, "The sum is correct: %lld", jury_answer);
    } else {
        // Nếu không khớp, trả về verdict WA (Wrong Answer)
        // Script python sẽ nhận được return code khác 0
        quitf(_wa, "Wrong sum. Expected %lld, found %lld", jury_answer, contestant_answer);
    }

    return 0; // Dòng này sẽ không bao giờ được thực thi vì quitf đã thoát chương trình
}