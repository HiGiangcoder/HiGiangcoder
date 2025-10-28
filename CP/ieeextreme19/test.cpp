#include <thread>
#include <iostream>
using namespace std;

int main() {
    unsigned int n = thread::hardware_concurrency();
    cout << "Số luồng phần cứng (hardware threads): " << n << endl;
}
