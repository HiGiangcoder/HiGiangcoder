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
