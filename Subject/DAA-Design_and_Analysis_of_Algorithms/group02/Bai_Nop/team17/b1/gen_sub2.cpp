#include "testlib.h"
#include <iostream>
#include <vector>

#include <bits/stdc++.h> 
using namespace std;
#define ll long long
mt19937 RNG(chrono::high_resolution_clock::now().time_since_epoch().count());
ll rng(ll l, ll r)
{
    assert(l <= r);ll L = l, R = r;
    ll aft = (L + RNG() * 1LL % (R - L + 1));
    return aft;
}


const int MAX_N_SUB2 = 100000;
const int MAX_A = 100000;

// Trường hợp thông thường
void genNormalCase() {
    int n = rng(1001, MAX_N_SUB2);
    std::cout << n << std::endl;
    for (int i = 0; i < n; ++i) {
        std::cout << rng(-MAX_A, MAX_A) << (i == n - 1 ? "" : " ");
    }
    std::cout << std::endl;
}

// Trường hợp đặc biệt
void genSpecialCase() {
    int n = MAX_N_SUB2;
    std::cout << n << std::endl;
    // Mảng toàn số 0
    for (int i = 0; i < n; ++i) {
        std::cout << 0 << (i == n - 1 ? "" : " ");
    }
    std::cout << std::endl;
}

// Trường hợp biên: n=1, hoặc các giá trị a_i ở mức min/max
void genEdgeCase() {
    int n = MAX_N_SUB2;
    std::cout << n << std::endl;
    int val = rng(0, 1) ? -MAX_A : MAX_A;
    for (int i = 0; i < n; ++i) {
        std::cout << val << (i == n - 1 ? "" : " ");
    }
    std::cout << std::endl;
}

// Trường hợp cực đại (gây tràn số): n lớn nhất và các a_i đều dương lớn
void genStressCase() {
    int n = MAX_N_SUB2;
    std::cout << n << std::endl;
    for (int i = 0; i < n; ++i) {
        // Sinh các số dương lớn để tổng chắc chắn vượt 2*10^9
        std::cout << rng(MAX_A - 1000, MAX_A) << (i == n - 1 ? "" : " ");
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