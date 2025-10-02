## Bài 1: Kiểm kê hàng hóa
**Mô tả**:  
Cửa hàng X bán nhiều loại hàng, mỗi loại có mã riêng. Trong quá trình bán hàng, nhân viên chỉ ghi lại mã hàng mà không ghi số lượng. Hãy xác định số lượng bán ra của từng mã hàng.

**Đầu vào**:  
- Dòng đầu tiên chứa số nguyên `N` (1 ≤ N ≤ 5 × 10⁴), là số lượng mã hàng được ghi lại.  
- `N` dòng tiếp theo, mỗi dòng chứa một mã hàng (tối đa 100 ký tự).

**Đầu ra**:  
- Với mỗi mã hàng, in ra mã hàng và số lượng bán được.  
- Sắp xếp kết quả theo số lượng giảm dần. Nếu số lượng bằng nhau, sắp xếp theo mã hàng tăng dần.

**Lời giải**:  
Sử dụng một hash map để đếm số lần xuất hiện của từng mã hàng. Sau đó, sắp xếp kết quả theo tần suất giảm dần và theo mã hàng tăng dần nếu tần suất bằng nhau.

**Mã nguồn**:
````cpp
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
````

---

## Bài 2: Truy vấn tìm kiếm nhị phân
**Mô tả**:  
Cho một mảng số nguyên `A` và `Q` truy vấn. Với mỗi truy vấn:  
- Nếu `type = 1`, tìm vị trí đầu tiên xuất hiện của `y` trong `A`.  
- Nếu `type = 2`, tìm vị trí cuối cùng xuất hiện của `y` trong `A`.  
Nếu không tìm thấy, trả về `-1`.

**Đầu vào**:  
- Dòng đầu tiên chứa hai số nguyên `N` và `Q` (1 ≤ N ≤ 10⁵, 1 ≤ Q ≤ 5 × 10⁵).  
- Dòng thứ hai chứa `N` số nguyên `A[i]` (-10⁹ ≤ A[i] ≤ 10⁹).  
- `Q` dòng tiếp theo, mỗi dòng chứa một truy vấn dạng `type x y`.

**Đầu ra**:  
- Với mỗi truy vấn, in ra kết quả trên một dòng.

**Lời giải**:  
Sắp xếp mảng kèm theo chỉ số ban đầu. Sử dụng tìm kiếm nhị phân để tìm vị trí đầu tiên và cuối cùng của giá trị cần tìm.

**Mã nguồn**:
````cpp
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
````

---

## Bài 3: Phát hiện virus trong tệp
**Mô tả**:  
Cho một tệp hình chữ nhật kích thước `N × M` chứa các ký tự thường. Xác định xem mỗi mẫu virus có xuất hiện trong tệp hay không (theo chiều ngang hoặc dọc).

**Đầu vào**:  
- Dòng đầu tiên chứa ba số nguyên `N`, `M`, và `Q` (1 ≤ N × M ≤ 10⁵, 1 ≤ Q ≤ 10⁴).  
- `N` dòng tiếp theo, mỗi dòng chứa `M` ký tự.  
- `Q` dòng tiếp theo, mỗi dòng chứa một mẫu virus (độ dài từ 2 đến 10).

**Đầu ra**:  
- Một dòng duy nhất gồm `Q` ký tự, ký tự thứ `i` là `1` nếu mẫu virus thứ `i` xuất hiện, ngược lại là `0`.

**Lời giải**:  
Tính trước hash cho các mẫu virus. Duyệt qua tất cả các chuỗi con trong tệp (theo chiều ngang và dọc) để kiểm tra khớp.

**Mã nguồn**:
````cpp
#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

// Global variables
int N, M, Q;
vector<string> file;
vector<string> viruses;
unordered_set<size_t> virusHashes;
unordered_set<string> foundSubstrings;

// Function to compute hash for a string
size_t computeHash(const string &s) {
    const int p = 31; // A prime number
    const int m = 1e9 + 9; // A large prime modulus
    size_t hash_value = 0;
    size_t p_pow = 1;

    for (char c : s) {
        hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }

    return hash_value;
}

// Function to check for virus patterns
string detectVirus() {
    virusHashes.clear();
    foundSubstrings.clear();

    // Precompute hashes for all virus patterns
    for (const string &virus : viruses) {
        virusHashes.insert(computeHash(virus));
    }

    // Check horizontally
    for (int i = 0; i < N; ++i) {
        for (int len = 2; len <= 10; ++len) {
            for (int j = 0; j + len - 1 < M; ++j) {
                string substring = file[i].substr(j, len);
                if (virusHashes.count(computeHash(substring))) {
                    foundSubstrings.insert(substring);
                }
            }
        }
    }

    // Check vertically
    for (int j = 0; j < M; ++j) {
        for (int len = 2; len <= 10; ++len) {
            for (int i = 0; i + len - 1 < N; ++i) {
                string substring;
                for (int k = 0; k < len; ++k) {
                    substring += file[i + k][j];
                }
                if (virusHashes.count(computeHash(substring))) {
                    foundSubstrings.insert(substring);
                }
            }
        }
    }

    // Build result string
    string result(viruses.size(), '0');
    for (int k = 0; k < viruses.size(); ++k) {
        if (foundSubstrings.count(viruses[k])) {
            result[k] = '1';
        }
    }

    return result;
}

int main() {    
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    if (fopen(".inp", "r")) {
        freopen(".inp", "r", stdin);
        freopen(".out", "w", stdout);
    }

    cin >> N >> M >> Q;

    file.resize(N);
    for (int i = 0; i < N; ++i) {
        cin >> file[i];
    }

    viruses.resize(Q);
    for (int i = 0; i < Q; ++i) {
        cin >> viruses[i];
    }

    cout << detectVirus() << endl;

    return 0;
}
````

---

## Bài 4: Sinh viên cuối hàng
**Mô tả**:  
Ban đầu, các sinh viên xếp hàng theo thứ tự mã số sinh viên từ `1` đến `n`. Khi một sinh viên được gọi, họ sẽ lên đầu hàng. Hãy xác định sinh viên cuối hàng sau mỗi lần gọi.

**Đầu vào**:  
- Dòng đầu tiên chứa hai số nguyên `n` và `m` (1 ≤ n, m ≤ 10⁵).  
- Dòng thứ hai chứa `m` số nguyên, là mã số sinh viên được gọi.

**Đầu ra**:  
- `m` số nguyên, là mã số sinh viên cuối hàng sau mỗi lần gọi.

**Lời giải**:  
Sử dụng một map để theo dõi thứ tự của các sinh viên. Cập nhật map sau mỗi lần gọi và in ra sinh viên cuối hàng.

**Mã nguồn**:
````cpp
#include<bits/stdc++.h>
using namespace std;

const int MAX = 1e5 + 7;

int n, m;

int val[MAX];
map<int, int> mp;

int main() {
    ios_base ::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    if (fopen(".inp", "r")) {
        freopen(".inp", "r", stdin);
        freopen(".out", "w", stdout);
    }

    cin >> n >> m;

    for (int i = n; i >= 1; i --) {
        val[i] = -i + 1;
        mp[val[i]] = i;
    }

    for (int i = 1; i <= m; i ++) {
        int student; cin >> student;        

        mp.erase(val[student]);
        mp[i] = student;
        val[student] = i;

        map<int, int>::iterator it = mp.begin();
        cout << it -> second << " "; // Print the last element in the map
    }


    return 0;
}
````

---

## Bài 5: Thứ tự cuối cùng của sinh viên
**Mô tả**:  
Ban đầu, các sinh viên xếp hàng theo thứ tự mã số sinh viên từ `1` đến `n`. Khi một sinh viên được gọi, họ sẽ lên đầu hàng. Hãy xác định thứ tự cuối cùng của các sinh viên sau tất cả các lần gọi.

**Đầu vào**:  
- Dòng đầu tiên chứa hai số nguyên `n` và `m` (1 ≤ n, m ≤ 10⁵).  
- Dòng thứ hai chứa `m` số nguyên, là mã số sinh viên được gọi.

**Đầu ra**:  
- Một dòng duy nhất chứa thứ tự cuối cùng của các sinh viên.

**Lời giải**:  
Sử dụng một tập hợp để theo dõi các sinh viên đã được gọi. Duyệt ngược danh sách các lần gọi, sau đó thêm các sinh viên còn lại vào danh sách kết quả.

**Mã nguồn**:
````cpp
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main() {
    // Redirect input and output
    if (fopen(".inp", "r")) {
        freopen(".inp", "r", stdin);
        freopen(".out", "w", stdout);
    }

    int n, m;
    cin >> n >> m;

    vector<int> calls(m);
    for (int i = 0; i < m; ++i) {
        cin >> calls[i];
    }

    set<int> called; // To track unique students called
    vector<int> result;

    // Traverse calls in reverse order
    for (int i = m - 1; i >= 0; --i) {
        if (called.find(calls[i]) == called.end()) {
            result.push_back(calls[i]);
            called.insert(calls[i]);
        }
    }

    // Add remaining students in ascending order
    for (int i = 1; i <= n; ++i) {
        if (called.find(i) == called.end()) {
            result.push_back(i);
        }
    }

    // Output the result
    for (int student : result) {
        cout << student << " ";
    }

    return 0;
}
````
