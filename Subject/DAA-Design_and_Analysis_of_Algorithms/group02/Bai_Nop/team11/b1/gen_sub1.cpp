
#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int n = rnd.next(1, 1000);
    println(n);
    for (int i = 0; i < n; i++)
        cout << (i ? " " : "") << rnd.next(-100000, 100000);
    cout << '\n';
}
