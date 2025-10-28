#include<bits/stdc++.h>
using namespace std;
const int MAX = 1e6 + 7;

int partition(int pivot, int *a, int n) {
    int left = 0, right = n - 1;
    while (left <= right) {
        while (a[left] < pivot) {
            left++;
            count++;
        }
        while (a[right] > pivot) {
            right--;
            count++;
        }
        count += 2;

        if (left <= right) {
            swap(a[left], a[right]);
            left++;
            right--;
        }
    }
    return left - 1;
}

void quicksort(int *a, int l, int r) {
    if (r > l) {
        int pivot = (a[l] + a[r] + a[(l+r)/2])/3;
        int i = partition(pivot, a + l, r - l + 1);

        quicksort(a, l, l + i);
        quicksort(a, l + i + 1, r);
    }
}

int n;
int a[MAX];

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i ++) cin >> a[i];

    return 0;
}

