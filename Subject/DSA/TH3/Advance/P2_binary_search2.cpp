#include<iostream>
#include<vector>
using namespace std;
using ll = long long;
using ii = pair<int, int>;

const int MOD = 1e9 + 7;
const int MAX = 1e5 + 5;

#define TASK "" // Retain only relevant defines

int n, q;
int a[MAX];
pair<int, int> res[MAX * 2]; // Adjust size to handle negative values if needed
vector<pair<int, int>> processedArray; 
vector<int> discreteValues; // Store discrete values globally

void CombineSegments(vector<pair<int, int>>& arr, int left, int mid, int right) { // Renamed from Merge
    vector<pair<int, int>> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right) {
        if (arr[i].first <= arr[j].first) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];

    for (int p = 0; p < k; p++) {
        arr[left + p] = temp[p];
    }
}

void CustomArrange(vector<pair<int, int>>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        CustomArrange(arr, left, mid);
        CustomArrange(arr, mid + 1, right);
        CombineSegments(arr, left, mid, right); // Updated reference
    }
}

void Prepare() {
    processedArray.clear();
    for (int i = 1; i <= n; i++) {
        processedArray.push_back({a[i], i});
    }

    CustomArrange(processedArray, 0, processedArray.size() - 1);
}

int CustomLowerBound(const vector<pair<int, int>>& arr, pair<int, int> val) {
    int left = 0, right = arr.size();
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] < val) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
}

int CustomUpperBound(const vector<pair<int, int>>& arr, pair<int, int> val) {
    int left = 0, right = arr.size();
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] <= val) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
}

int FindFirst(int val) {
    int idx = CustomLowerBound(processedArray, make_pair(val, 0));
    if (idx == processedArray.size() || processedArray[idx].first != val) return -1;
    return processedArray[idx].second;
}

int FindLast(int val) {
    int idx = CustomUpperBound(processedArray, make_pair(val, 0x3f3f3f3f));
    if (idx == 0 || processedArray[idx - 1].first != val) return -1;
    return processedArray[idx - 1].second;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    if (fopen(TASK".inp", "r")) {
        freopen(TASK".inp", "r", stdin);
        freopen(TASK".out", "w", stdout);
    }

    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    Prepare();

    while (q --) {
        string s;
        int type, x;

        cin >> s >> type >> x;

        if (type == 1) cout << FindFirst(x) << '\n';
        if (type == 2) cout << FindLast(x) << '\n';
    }
    
    return 0;
}