/*
ID: zhongbr1
TASK: sprime
LANG: C++11
*/

#include <fstream>
#include <cmath>
#include <set>

using namespace std;

int length;
set<int> superprimes;
int n[4] = {1, 3, 7, 9};
bool valid;
void gen(int len, int num) {
	if (len == length) {
		superprimes.insert(num);
		return;
	}
	num *= 10;
	for (int i=0; i<4; i++) {
		valid = true;
		for (int j=3; j<=sqrt(num+n[i]); j++) {
			if ((num+n[i]) % j == 0) {
				valid = false;
				break;
			}
		}
		if (valid == true) {
			gen(len+1, num+n[i]);
		}
	}
}

int main() {
	ifstream fin("sprime.in");
	ofstream fout("sprime.out");

	fin >> length;
	gen(1, 2);
	gen(1, 3);
	gen(1, 5);
	gen(1, 7);

	for (set<int>::iterator it = superprimes.begin(); it != superprimes.end(); it++) {
		fout << *it << endl;
	}

	return 0;
}
