#include <bits/stdc++.h> 
#include "testlib.h"
#include <iostream>
#include <vector>

using namespace std;

const int MAX_N_SUB1 = 1000;
const int MAX_A = 100000;

#define ll long long
mt19937 RNG(chrono::high_resolution_clock::now().time_since_epoch().count());
ll rng(ll l, ll r)
{
    assert(l <= r);ll L = l, R = r;
    ll aft = (L + RNG() * 1LL % (R - L + 1));
    return aft;
}



// Trường hợp thông thường: n và a_i ngẫu nhiên
void genNormalCase() {
    int n = rng(1, MAX_N_SUB1);
    std::cout << n << std::endl;
    for (int i = 0; i < n; ++i) {
        std::cout << rng(-MAX_A, MAX_A) << (i == n - 1 ? "" : " ");
    }
    std::cout << std::endl;
}

// Trường hợp đặc biệt: mảng toàn số 0, toàn số dương, hoặc toàn số âm
void genSpecialCase() {
    int n = MAX_N_SUB1;
    std::cout << n << std::endl;
    int val = 0;
    if (rng(0, 2) == 1) val = MAX_A;
    if (rng(0, 2) == 2) val = -MAX_A;
    for (int i = 0; i < n; ++i) {
        std::cout << val << (i == n - 1 ? "" : " ");
    }
    std::cout << std::endl;
}

// Trường hợp biên: n nhỏ nhất, n lớn nhất
void genEdgeCase() {
    int n = rng(1, 2) == 1 ? 1 : MAX_N_SUB1;
    std::cout << n << std::endl;
    for (int i = 0; i < n; ++i) {
        std::cout << rng(-MAX_A, MAX_A) << (i == n - 1 ? "" : " ");
    }
    std::cout << std::endl;
}

// Trường hợp cực đại: n lớn nhất và các giá trị a_i lớn nhất
// (không đủ để gây tràn số int ở subtask 1, nhưng vẫn là test mạnh)
void genStressCase() {
    int n = MAX_N_SUB1;
    std::cout << n << std::endl;
    for (int i = 0; i < n; ++i) {
        std::cout << MAX_A << (i == n - 1 ? "" : " ");
    }
    std::cout << std::endl;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int type = std::atoi(argv[1]);
    
    if (type == 1) genNormalCase();
    else if (type == 2) genSpecialCase();
    else if (type == 3) genEdgeCase();
    else genStressCase();
    
    return 0;
}