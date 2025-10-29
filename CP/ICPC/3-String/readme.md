# String

## 1. Hashing

```cpp
#include <bits/stdc++.h>
using namespace std;

struct StringHash {
    const int base = 31;
    const int mod1 = 1e9+7, mod2 = 1e9+9;
    vector<long long> pow1, pow2, hash1, hash2;
    
    StringHash(string s) {
        int n = s.size();
        pow1.resize(n+1); pow2.resize(n+1);
        hash1.resize(n+1); hash2.resize(n+1);
        
        pow1[0] = pow2[0] = 1;
        for (int i = 0; i < n; i++) {
            pow1[i+1] = pow1[i] * base % mod1;
            pow2[i+1] = pow2[i] * base % mod2;
            hash1[i+1] = (hash1[i] * base + s[i]) % mod1;
            hash2[i+1] = (hash2[i] * base + s[i]) % mod2;
        }
    }
    
    pair<long long, long long> get_hash(int l, int r) {
        // [l, r] 0-based
        long long h1 = (hash1[r+1] - hash1[l] * pow1[r-l+1]) % mod1;
        long long h2 = (hash2[r+1] - hash2[l] * pow2[r-l+1]) % mod2;
        if (h1 < 0) h1 += mod1;
        if (h2 < 0) h2 += mod2;
        return {h1, h2};
    }
};
```

## 2. Z-function

* **Mục đích:** Tìm độ dài tiền tố chung dài nhất giữa xâu và hậu tố bắt đầu tại mỗi vị trí.
* **Định nghĩa:**
  ( Z[i] = ) độ dài lớn nhất sao cho `s[0..Z[i]-1] = s[i..i+Z[i]-1]`.
* **Ý tưởng:** Duy trì đoạn ([l, r]) — vùng khớp xa nhất hiện tại.

  * Nếu (i > r): so khớp mới từ đầu.
  * Nếu (i \le r): (Z[i] = \min(r - i + 1, Z[i-l])), sau đó mở rộng thêm nếu có thể.
* **Độ phức tạp:** (O(n)).
* **Ứng dụng:**

  * Tìm mẫu trong chuỗi: ghép `pattern + '$' + text`.
  * Tính số tiền tố trùng khớp.
  * Xử lý bài toán palindrome, chuỗi con lặp, v.v.
* **Code (C++):**

  ```cpp
  vector<int> z_function(string s) {
      int n = s.size(), l = 0, r = 0;
      vector<int> z(n);
      for (int i = 1; i < n; i++) {
          if (i <= r) z[i] = min(r - i + 1, z[i - l]);
          while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
          if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
      }
      return z;
  }
  ```

## 3. KMP (Knuth-Morris-Pratt)
```cpp
#include <bits/stdc++.h>
using namespace std;

vector<int> prefix_function(string s) {
    int n = s.size();
    vector<int> pi(n, 0);
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j]) j = pi[j-1];
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}

vector<int> kmp_search(string text, string pattern) {
    string s = pattern + '#' + text;
    vector<int> pi = prefix_function(s);
    vector<int> occurrences;
    
    int pattern_len = pattern.size();
    for (int i = pattern_len + 1; i < s.size(); i++)
        if (pi[i] == pattern_len)
            occurrences.push_back(i - 2 * pattern_len);
    
    return occurrences;
}
```

## 4. Aho-Corasick
```cpp
#include <bits/stdc++.h>
using namespace std;

struct AhoCorasick {
    struct Node {
        map<char, int> next;
        int fail = 0;
        int output = 0;
    };
    
    vector<Node> trie;
    
    AhoCorasick() { trie.emplace_back(); }
    
    void insert(string s) {
        int u = 0;
        for (char c : s) {
            if (!trie[u].next.count(c)) {
                trie[u].next[c] = trie.size();
                trie.emplace_back();
            }
            u = trie[u].next[c];
        }
        trie[u].output++;
    }
    
    void build() {
        queue<int> q;
        for (auto [c, v] : trie[0].next) q.push(v);
        
        while (!q.empty()) {
            int u = q.front(); q.pop();
            
            for (auto [c, v] : trie[u].next) {
                int f = trie[u].fail;
                while (f && !trie[f].next.count(c)) f = trie[f].fail;
                
                if (trie[f].next.count(c)) 
                    trie[v].fail = trie[f].next[c];
                else
                    trie[v].fail = 0;
                    
                trie[v].output += trie[trie[v].fail].output;
                q.push(v);
            }
        }
    }
    
    int search(string text) {
        int u = 0, total = 0;
        for (char c : text) {
            while (u && !trie[u].next.count(c)) u = trie[u].fail;
            if (trie[u].next.count(c)) u = trie[u].next[c];
            total += trie[u].output;
        }
        return total;
    }
};
```


