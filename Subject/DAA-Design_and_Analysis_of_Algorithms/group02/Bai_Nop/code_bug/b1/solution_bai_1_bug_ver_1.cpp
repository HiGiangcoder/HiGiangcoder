#include <algorithm>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <utility>
#include <valarray>
#include <vector>
#include <cstring>
#include <cmath>
#include <chrono>
#include <bitset>   
#include <complex>
#include <deque>
#include <fstream>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <map>
#include <numeric>
#include <ostream>
#include <queue>
#include <cassert>

using namespace std;

const int MAXN = 1e5+7;

int a[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // lỗi để sum là int thực chất phải để long long
    int sum = 0,n; cin >> n;
    for(int i = 1; i<=n; i++){
        cin >> a[i];
        sum += a[i];
    }
    cout << sum;
    return 0;
}
