/*
ID: zhongbr1
TASK: preface
LANG: C++11
*/

#include <fstream>
#include <map>

using namespace std;

map<char, int> val;
struct comp {
	const bool operator() (const char& a, const char& b) const {
		return val[a] < val[b];
	}
};

map<char, int, comp> n_count;
int calculate(int n, int m, char a, int b, int c) {
	if (n >= 9 * m) {
		n_count[c]++;
		n_count[a]++;
		n -= 9 * m;
	}
	if (n >= 5 * m) {
		n_count[b]++;
		n -= 5 * m;
	}
	if (n >= 4 * m) {
		n_count[b]++;
		n_count[a]++;
		n -= 4 * m;
	}

	n_count[a] += n/val[a];
	n %= val[a];

	return n;
}

int main() {
	ifstream fin("preface.in");
	ofstream fout("preface.out");

	int limit;
	fin >> limit;

	val['I'] = 1; val['V'] = 5; val['X'] = 10; val['L'] = 50; val['C'] = 100; val['D'] = 500; val['M'] = 1000;

	int tmp;
	for (int i=1; i<=limit; i++) {
		tmp = i;
		if (tmp >= 1000) {
			n_count['M'] += tmp / 1000;
			tmp %= 1000;
		}
		calculate(
				calculate(
						calculate(tmp, 100, 'C', 'D', 'M'),
				10, 'X', 'L', 'C'),
		1, 'I', 'V', 'X');
	}

	for (map<char, int>::iterator it = n_count.begin(); it != n_count.end(); it++) {
		if (it->second == 0) {
			continue;
		}
		fout << it->first << " " << it->second << endl;
	}

	return 0;
}
