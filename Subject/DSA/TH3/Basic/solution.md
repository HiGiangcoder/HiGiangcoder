## Bài 1: Kiểm tra tính hợp lệ của chuỗi Latex
**Đề bài**:  
Kiểm tra chuỗi Latex có hợp lệ không bằng cách đảm bảo các dấu ngoặc `{}`, `[]`, `()` được đóng mở đúng thứ tự.

**Đầu vào**:  
Chuỗi `s` (1 ≤ |s| ≤ 10⁵).

**Đầu ra**:  
`1` nếu chuỗi hợp lệ, ngược lại `0`.

**Lời giải**:  
Sử dụng ngăn xếp (stack) để kiểm tra tính cân bằng của các dấu ngoặc. Khi gặp dấu mở, đẩy vào ngăn xếp. Khi gặp dấu đóng, kiểm tra xem có khớp với dấu mở trên cùng của ngăn xếp không.

**Mã nguồn**:
````cpp
#include<bits/stdc++.h>
using namespace std;

int decode[256];

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    string s; cin >> s;

    decode['{'] = -3;
    decode['}'] = 3;
    decode['['] = -2;
    decode[']'] = 2;
    decode['('] = -1;
    decode[')'] = 1;

    vector<int> stk;

    for (char c : s) if (decode[c] != 0) {
        if (decode[c] < 0) stk.push_back(decode[c]);
        else if (stk.empty() || stk.back() != -decode[c]) {
            cout << 0;
            return 0;
        } else stk.pop_back();
    }
    cout << (stk.empty() ? 1 : 0);
    return 0;
}
````

---

## Bài 2: Chèn vào danh sách liên kết đơn đã sắp xếp
**Đề bài**:  
Chèn giá trị `x` vào danh sách liên kết đơn đã sắp xếp sao cho danh sách vẫn giữ thứ tự tăng dần.

**Đầu vào**:  
- Số nguyên `N` (0 ≤ N ≤ 10⁵), số phần tử trong danh sách.  
- `N` số nguyên của danh sách liên kết.  
- Số nguyên `x`, giá trị cần chèn.

**Đầu ra**:  
Danh sách liên kết sau khi chèn, cách nhau bởi dấu cách.

**Lời giải**:  
Duyệt danh sách liên kết để tìm vị trí thích hợp và chèn nút mới vào.

**Mã nguồn**:
````cpp
#include <iostream>
using namespace std;

class SinglyLinkedListNode {
public:
    int data;
    SinglyLinkedListNode *next;

    SinglyLinkedListNode(int node_data) {
        this->data = node_data;
        this->next = nullptr;
    }
};

SinglyLinkedListNode* insertSortedLinkedList(SinglyLinkedListNode* head, int x) {
    SinglyLinkedListNode *newNode = new SinglyLinkedListNode(x);
    if (head == NULL || head->data >= x) {
        newNode->next = head;
        return newNode;
    } 

    SinglyLinkedListNode *ptr = head;
    while (ptr->next != NULL && ptr->next->data < x) ptr = ptr->next;
    newNode->next = ptr->next;
    ptr->next = newNode;
    return head;
}

void printLinkedList(SinglyLinkedListNode* head) {
    while (head != NULL) {
        cout << head->data << ' ';
        head = head->next;
    }
}

int main() {
    int n, x;
    cin >> n;
    SinglyLinkedListNode* head = NULL;

    for (int i = 0; i < n; i++) {
        int value;
        cin >> value;
        head = insertSortedLinkedList(head, value);
    }
    cin >> x;
    head = insertSortedLinkedList(head, x);
    printLinkedList(head);
    return 0;
}
````

---

## Bài 3: Nhập và tính giá trị đa thức
**Đề bài**:  
Nhập một đa thức, hiển thị dạng chuẩn và tính giá trị tại `x`.

**Đầu vào**:  
- Số nguyên `n` (0 ≤ n ≤ 100), số đơn thức.  
- `n` cặp số: hệ số (số thực) và số mũ (nguyên không âm).  
- Số thực `x`.

**Đầu ra**:  
- Đa thức dạng chuẩn.  
- Giá trị của đa thức tại `x`, làm tròn 2 chữ số thập phân.

**Lời giải**:  
Sử dụng danh sách liên kết để lưu các đơn thức. Tính giá trị đa thức bằng cách duyệt qua danh sách và áp dụng công thức.

**Mã nguồn**:
````cpp
#include <bits/stdc++.h>
using namespace std;

struct DONTHUC {
    int somu;
    double heso;

    DONTHUC(double _heso = 0, int _somu = 0) {
        heso = _heso;
        somu = _somu;
    }
};

struct Node {
    DONTHUC* data;
    Node* next;

    Node(DONTHUC* _data = nullptr) {
        this->data = _data;
        this->next = nullptr;
    }
};

struct DATHUC {
    Node* head;
    Node* tail;
    DATHUC() {
        this->head = nullptr;
        this->tail = nullptr;
    }
};

void Nhap(DATHUC &B, double heso, int somu) {
    DONTHUC* p = new DONTHUC(heso, somu);
    Node* q = new Node(p);
    if (B.head == nullptr) {
        B.head = q;
        B.tail = q;
    } else {
        B.tail->next = q;
        B.tail = q;
    }
}

void Xuat(DATHUC B) {
    Node* p = B.head;
    bool first = true;
    while (p != nullptr) {
        if (!first && p->data->heso > 0) cout << "+";
        if (p->data->heso < 0) cout << "-";
        if (p->data->heso == 0) {
            p = p->next;
            continue;
        }
        first = false;
        if (abs(p->data->heso) != 1) cout << abs(p->data->heso);
        if (p->data->somu > 1) cout << "x^" << p->data->somu;
        else if (p->data->somu == 1) cout << "x";
        p = p->next;
    }
    if (first) cout << "0";
}

double TinhDaThuc(DATHUC B, double x) {
    double S = 0;
    Node* p = B.head;
    while (p != nullptr) {
        S += p->data->heso * pow(x, p->data->somu);
        p = p->next;
    }
    return S;
}

int main() {
    DATHUC B;
    int N;
    cin >> N;
    for (int i = 0; i < N; i++) {
        double heso; int somu;
        cin >> heso >> somu;
        Nhap(B, heso, somu);
    }
    cout << "Da thuc vua nhap la: "; Xuat(B);
    double x; cin >> x;
    cout << "\nVoi x=" << x << ", gia tri da thuc la: "
         << setprecision(2) << fixed << TinhDaThuc(B, x);
    return 0;
}
````

---

## Bài 4: Đảo ngược danh sách liên kết
**Đề bài**:  
Đảo ngược danh sách liên kết đơn và in kết quả.

**Đầu vào**:  
- Số nguyên `N`, số phần tử trong danh sách.  
- `N` số nguyên của danh sách liên kết.

**Đầu ra**:  
Danh sách liên kết sau khi đảo ngược, cách nhau bởi dấu cách.

**Lời giải**:  
Duyệt danh sách và thay đổi con trỏ `next` của từng nút để đảo ngược danh sách.

**Mã nguồn**:
````cpp
void reverseLinkedList(SinglyLinkedList* llist) {
    SinglyLinkedListNode* prev = nullptr;
    SinglyLinkedListNode* current = llist->head;
    SinglyLinkedListNode* next = nullptr;

    while (current != nullptr) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    llist->tail = llist->head;
    llist->head = prev;
}
````

---

## Bài 5: Chuyển đổi thập phân sang nhị phân
**Đề bài**:  
Chuyển đổi số nguyên từ hệ thập phân sang hệ nhị phân.

**Đầu vào**:  
Số nguyên `x` (1 ≤ x ≤ 10⁵).

**Đầu ra**:  
Chuỗi nhị phân tương ứng.

**Lời giải**:  
Sử dụng ngăn xếp để lưu phần dư khi chia `x` cho 2, sau đó in ra theo thứ tự ngược lại.

**Mã nguồn**:
````cpp
stack<int> s;

while (x > 0) {
    s.push(x % 2);
    x /= 2;
}

while (!s.empty()) {
    cout << s.top();
    s.pop();
}
````

---

## Bài 6: Trộn hai danh sách liên kết đã sắp xếp
**Đề bài**:  
Trộn hai danh sách liên kết đơn đã sắp xếp thành một danh sách cũng được sắp xếp.

**Đầu vào**:  
- Số nguyên `T` (T < 10), số bộ test.  
- Mỗi bộ test gồm:  
  - Hai số nguyên `n` và `m`, kích thước của hai danh sách.  
  - `n` số nguyên của danh sách thứ nhất.  
  - `m` số nguyên của danh sách thứ hai.

**Đầu ra**:  
Danh sách liên kết sau khi trộn.

**Lời giải**:  
Sử dụng hai con trỏ để duyệt qua hai danh sách và trộn chúng lại.

**Mã nguồn**:
````cpp
SinglyLinkedListNode* mergeLists(SinglyLinkedListNode* head_list1, SinglyLinkedListNode* head_list2) {
    SinglyLinkedListNode dummy(0);
    SinglyLinkedListNode* tail = &dummy;

    while (head_list1 && head_list2) {
        if (head_list1->data <= head_list2->data) {
            tail->next = head_list1;
            head_list1 = head_list1->next;
        } else {
            tail->next = head_list2;
            head_list2 = head_list2->next;
        }
        tail = tail->next;
    }

    if (head_list1) tail->next = head_list1;
    else tail->next = head_list2;

    return dummy.next;
}
````

---

## Bài 7: Duyệt cây theo thứ tự NLR (Đệ quy)
**Đề bài**:  
Duyệt cây nhị phân theo thứ tự NLR (Node-Left-Right) bằng đệ quy.

**Đầu vào**:  
- Số nguyên `N`, số nút trong cây.  
- `N` số nguyên là giá trị các nút.

**Đầu ra**:  
Kết quả duyệt cây theo thứ tự NLR.

**Lời giải**:  
Sử dụng đệ quy để duyệt cây theo thứ tự NLR.

**Mã nguồn**:
````cpp
void preOrder(Node *root) {
    if (root == NULL) return;
    cout << root->data << " ";
    preOrder(root->left);
    preOrder(root->right);
}
````

---

## Bài 8: Duyệt cây theo thứ tự NLR (Không đệ quy)
**Đề bài**:  
Duyệt cây nhị phân theo thứ tự NLR (Node-Left-Right) không dùng đệ quy.

**Đầu vào**:  
Giống bài 7.

**Đầu ra**:  
Giống bài 7.

**Lời giải**:  
Sử dụng ngăn xếp để mô phỏng đệ quy và duyệt cây theo thứ tự NLR.

**Mã nguồn**:
````cpp
void preOrder(Node *root) {
    stack<Node*> s;
    s.push(root);

    while (!s.empty()) {
        Node* ptr = s.top();
        s.pop();
        if (ptr == NULL) continue;

        cout << ptr->data << " ";

        if (ptr->right) s.push(ptr->right);
        if (ptr->left) s.push(ptr->left);
    }
}
````

---

## Bài 9: Tìm nút chung của hai danh sách liên kết
**Đề bài**:  
Tìm nút chung đầu tiên của hai danh sách liên kết đơn.

**Đầu vào**:  
- Hai danh sách liên kết.  
- Danh sách thứ ba chứa các nút chung.

**Đầu ra**:  
Giá trị của nút chung đầu tiên, hoặc `NA` nếu không có.

**Lời giải**:  
Tính độ dài của hai danh sách, căn chỉnh chúng và duyệt để tìm nút chung.

**Mã nguồn**:
````cpp
SinglyLinkedListNode* findMergeNode(SinglyLinkedListNode* head1, SinglyLinkedListNode* head2) {
    int len1 = 0, len2 = 0;
    SinglyLinkedListNode* temp1 = head1;
    SinglyLinkedListNode* temp2 = head2;

    while (temp1) { len1++; temp1 = temp1->next; }
    while (temp2) { len2++; temp2 = temp2->next; }

    temp1 = head1;
    temp2 = head2;

    if (len1 > len2) for (int i = 0; i < len1 - len2; i++) temp1 = temp1->next;
    else for (int i = 0; i < len2 - len1; i++) temp2 = temp2->next;

    while (temp1 && temp2) {
        if (temp1 == temp2) return temp1;
        temp1 = temp1->next;
        temp2 = temp2->next;
    }

    return nullptr;
}
````

---

## Bài 10: Nút tổ tiên thấp nhất trong cây BST
**Đề bài**:  
Tìm nút tổ tiên thấp nhất của hai nút trong cây nhị phân tìm kiếm (BST).

**Đầu vào**:  
- Số nguyên `N`, số nút trong cây.  
- `N` số nguyên là giá trị các nút.  
- Hai số nguyên `v1` và `v2`.

**Đầu ra**:  
Giá trị của nút tổ tiên thấp nhất.

**Lời giải**:  
Sử dụng đệ quy để tìm điểm phân tách giữa hai nút.

**Mã nguồn**:
````cpp
Node* lca(Node* root, int v1, int v2) {
    if (root == NULL) return NULL;
    if (root->data == v1 || root->data == v2) return root;

    Node* left = lca(root->left, v1, v2);
    Node* right = lca(root->right, v1, v2);

    if (left && right) return root;
    return left ? left : right;
}
````
