#include <iostream>
#include <vector>
using namespace std;


const int MOD = 1e9 + 7;
const int MAX = 2e5 + 5;

int cnt[202];
int n, d;
int a[MAX];

int main() {
    cin >> n >> d;
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }

    int ans(0);
    for (int i = 0; i <= n; i ++) {
        cnt[a[i]] ++;
        if (i > d) {
            cnt[a[i - d - 1]] --;

            int num(0);
            int res(0);
            int mid = (d + 1) / 2;

            for (int val = 0; val <= 200; val ++) if (cnt[val] > 0) {
                num += cnt[val];
                
                if (num > mid && res > 0) {
                    res += val;
                    break;
                }
                if (num > mid || (num == mid && d % 2 == 1)) {
                    res = val * 2;
                    break;
                }  
                if (num == mid) { // d % 2 == 0
                    res = val;
                }
            }

            if (a[i] >= res) ans ++;
        }
    }
    cout << ans;
    
    return 0;
}