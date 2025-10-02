#include <iostream>
#include <stack>
using namespace std;

int main() {
    int x;
    cin >> x;

    stack<int> s;

    while (x > 0) {
        s.push(x % 2);
        x /= 2;
    }

    while (!s.empty()) {
        cout << s.top();
        s.pop();
    }

    return 0;
}