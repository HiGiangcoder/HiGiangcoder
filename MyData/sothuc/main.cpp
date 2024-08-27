#include<bits/stdc++.h>
using namespace std;

int main() {
    // in ra dung 10 so sau dau phay
    cout << fixed << setprecision(10);

    // kieu so thuc:

    // float: do chinh xac thap

    // double: do chinh xac cao
    double a = 3.98;
    cout << a << endl;

//    cout << fixed << setprecision(10) << a << endl;

    double n = 5;
    double m = 3;

    // dau / no la phep chia so thuc (khong phai phep chia lay phan nguyen)
    cout << n / m << endl;
    cout << endl;
    cout << (long long)(n / m) << endl;
    cout << endl;

    // 5 la kieu int(kieu so nguyen);
    // double(5) la kieu double(kieu so thuc)
    cout << 5 / 3 << endl; // chia lay nguyen
    // ep kieu so thuc -> phep chia la chia so thuc
    cout << double(5) / 3 << endl;
    cout << 5 / double(3) << endl;

    cout << (double)5 / 3 << endl;

    // khong duoc lam kieu nay
    cout << double(5 / 3) << endl; // chia lay nguyen -> ep qua so thuc

    return 0;
}
