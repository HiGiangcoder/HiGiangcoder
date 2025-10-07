# Một số lưu ý khi làm bài tập

## Các trường hợp cần lưu ý khi sinh test
1. Hãy đảm rằng bộ test của bạn tồn tại trường hợp bị tràn int
2. Hãy đảm bảo tồn tại trường hợp khai báo mảng kích thước n nhưng lại sử dụng mảng có bắt đầu từ 1
3. Đảm bảo rằng người dùng sử dụng kiểu `unsigned int` thay vì `int`.
4. Đảm bảo rằng mảng thì đúng kiểu dữ liệu nhưng biến tính tổng thì không nhưng vẫn AC
5. Đảm bảo rằng code không xử lý tốt trường hợp đa đồ thị bị sai (lưu đè trọng số trên mảng 2 chiều chẳng hạn).
6. Đảm bảo rằng code chuẩn cho từng subtask phải AC subtask đó (khi chấm sẽ vào source check xem subtask đó từ test nào đến test nào)
7. Đảm bảo rằng có cả trường hợp -1 và trường hợp tồn tại đường đi (cả test nhỏ và test lớn)
8. Đảm bảo rằng code quên không xử lý trường hợp có hướng bị Wrong Answer.
9. Đảm bảo rằng code vét cạn nhưng không tối ưu tốt sẽ bị TLE.
10. Code bẩn lợi dụng việc chỉ check liên thông hay không nhưng vẫn AC.

## Các trường hợp lưu ý khi viết validator
1. Theo tiêu chuẩn, khi sinh nhiều phần tử nào đó trên cùng một dòng, ở cuối dòng không được dư dấu cách.
2. Theo chuẩn, thường cuối mỗi test sẽ xuống 1 dòng (không bắt buộc).

## Các trường hợp lưu ý khi viết checker
1. Đảm bảo rằng với bài có nhiều đáp án, checker sẽ xử lý được trường hợp đó.
2. Hãy kiểm soát file output nếu code của người nộp in ra dữ liệu thừa.