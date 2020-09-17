/*
 ID: zhongbr1
 TASK: frac1
 LANG: C++11
 */

#include <fstream>
#include <set>

using namespace std;

struct Fraction {
	int n, d;
	double val;
};

struct comp_frac {
	bool operator () (const Fraction& a, const Fraction& b) const {
		return a.val < b.val;
	}
};

int main() {
	ifstream fin("frac1.in");
	ofstream fout("frac1.out");

	int limit;
	fin >> limit;

	set<Fraction, comp_frac> fractions;
	Fraction tmp;
	bool valid;
	for (int i = 2; i <= limit; i++) {
		for (int j = 1; j < i; j++) {
			valid = true;
			for (int d=2; d<i; d++) {
				if (i % d == 0 && j % d == 0) {
					valid = false;
					break;
				}
			}
			if (valid == true) {
				tmp.n = j;
				tmp.d = i;
				tmp.val = j / double(i);
				fractions.insert(tmp);
			}
		}
	}

	fout << "0/1" << endl;
	for (set<Fraction>::iterator it = fractions.begin(); it != fractions.end(); it++) {
		fout << it->n << "/" << it->d << endl;
	}
	fout << "1/1" << endl;

	return 0;
}

