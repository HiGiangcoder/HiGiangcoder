// check 2 code
#include<bits/stdc++.h>

using namespace std;

mt19937 rng(chrono :: steady_clock().now().time_since_epoch().count());
int random(int l, int r) {
	return uniform_int_distribution<int>(l, r)(rng);
}

#define TASK ""

void make_test() {
	ofstream inp(TASK".inp");
	
	inp.close();
}

int main() {	
	system("g++ "TASK".cpp -o "TASK);
	system("g++ "TASK"_brute.cpp  -o "TASK"_brute");
	
	int numtest = 100;
	for (int t = 1; t <= numtest; t ++) {
		system(TASK".exe");
		system(TASK"_brute.exe");
		
		cout << "TEST " << t << ": ";
		if (system("fc "TASK".out "TASK".ans") != 0) {
			cout  << "Wrong answer"  << endl;
			return 0;
		}
		else {
			cout  << "Accept" << endl;
		}
	}
}
