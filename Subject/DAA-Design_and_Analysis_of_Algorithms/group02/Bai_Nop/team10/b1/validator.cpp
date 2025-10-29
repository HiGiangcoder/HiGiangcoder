#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main() {
    registerValidation();
    int n = inf.readInt(1, 100000, "n");
    inf.readEoln(); 

    // Dòng 2: đọc n số nguyên
    vector<int> a = inf.readInts(n, -100000, 100000, "a_i");
    inf.readEoln(); 
    inf.readEof();
}
