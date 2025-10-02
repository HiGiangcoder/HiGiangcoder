#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll = long long;

const int MOD = 1e9 + 7;
const int MAX = 5e4 + 5;

#define TASK ""

bool CompareStrings(const string &a, const string &b) {
    if (a.length() != b.length()) return a.length() < b.length();
    return a < b;
}

bool ComparePairs(const pair<int, string> &a, const pair<int, string> &b) {
    if (a.first != b.first) return a.first > b.first; // Tần suất giảm dần
    return CompareStrings(a.second, b.second); // Chuỗi tăng dần
}

void Merge(vector<string> &vec, int left, int mid, int right) {
    vector<string> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right) {
        if (CompareStrings(vec[i], vec[j])) {
            temp[k++] = vec[i++];
        } else {
            temp[k++] = vec[j++];
        }
    }

    while (i <= mid) temp[k++] = vec[i++];
    while (j <= right) temp[k++] = vec[j++];

    for (int l = 0; l < temp.size(); l++) {
        vec[left + l] = temp[l];
    }
}

void MergeSort(vector<string> &vec, int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    MergeSort(vec, left, mid);
    MergeSort(vec, mid + 1, right);
    Merge(vec, left, mid, right);
}

void CustomSort(vector<string> &vec) {
    MergeSort(vec, 0, vec.size() - 1);
}

void Merge(vector<pair<int, string>> &vec, int left, int mid, int right) {
    vector<pair<int, string>> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right) {
        if (ComparePairs(vec[i], vec[j])) {
            temp[k++] = vec[i++];
        } else {
            temp[k++] = vec[j++];
        }
    }

    while (i <= mid) temp[k++] = vec[i++];
    while (j <= right) temp[k++] = vec[j++];

    for (int l = 0; l < temp.size(); l++) {
        vec[left + l] = temp[l];
    }
}

void MergeSort(vector<pair<int, string>> &vec, int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    MergeSort(vec, left, mid);
    MergeSort(vec, mid + 1, right);
    Merge(vec, left, mid, right);
}

void CustomSort(vector<pair<int, string>> &vec) {
    MergeSort(vec, 0, vec.size() - 1);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    if (fopen(TASK".inp", "r")) {
        freopen(TASK".inp", "r", stdin);
        freopen(TASK".out", "w", stdout);
    }

    int n; cin >> n;
    vector<string> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    CustomSort(arr); // Sắp xếp mảng

    vector<pair<int, string>> freqArr;
    int count = 1;

    for (int i = 1; i < n; i++) {
        if (arr[i] == arr[i - 1]) {
            count++;
        } else {
            freqArr.emplace_back(count, arr[i - 1]);
            count = 1;
        }
    }
    freqArr.emplace_back(count, arr[n - 1]); // Thêm phần tử cuối cùng

    CustomSort(freqArr); // Sắp xếp theo tần suất và chuỗi

    for (const auto &p : freqArr) {
        cout << p.second << ' ' << p.first << '\n';
    }

    return 0;
}