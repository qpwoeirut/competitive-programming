/*
ID: zhongbr1
TASK: hamming
LANG: C++11
*/

#include <fstream>
#include <set>

using namespace std;

int get_dist(int a, int b) {
	int d = 0;
	int c = a ^ b;
	while (c > 0) {
		if (c & 1) {
			d++;
		}
		c >>= 1;
	}

	return d;
}

int main() {
	ifstream fin("hamming.in");
	ofstream fout("hamming.out");

	int N, bits, dist;
	fin >> N >> bits >> dist;

	set<int> ans;
	ans.insert(0);
	bool valid;
	for (int i=1; i<(1 << bits); i++) {
		valid = true;
		for (set<int>::iterator it = ans.begin(); it != ans.end(); it++) {
			if (get_dist(*it, i) < dist) {
				valid = false;
				break;
			}
		}
		if (valid) {
			ans.insert(i);

			if (ans.size() == N) {
				break;
			}
		}

	}

	int col = 0;
	for (set<int>::iterator it = ans.begin(); it != ans.end(); it++) {
		if (col != 0) {
			fout << " ";
		}
		fout << *it;
		col++;
		if (col == 10) {
			fout << endl;
			col = 0;
		}
	}
	if (col != 0) {
		fout << endl;
	}

	return 0;
}
