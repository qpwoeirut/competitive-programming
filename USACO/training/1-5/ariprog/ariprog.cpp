/*
ID: zhongbr1
TASK: ariprog
LANG: C++11
*/

#include <fstream>
#include <cmath>
#include <set>

using namespace std;

bool bisquare[200000], known[200000];

int limit;
bool is_bisquare(int n) {
	if (known[n] == true) {
		return bisquare[n];
	}
	known[n] = true;
	float rt;
	int check;
	for (int i=0; i<=limit; i++) {
		rt = sqrt(n - (i*i));
		if (rt < i) {
			break;
		}
		check = rt;
		if (check == rt && check <= limit) {
			bisquare[n] = true;
			return true;
		}
	}

	bisquare[n] = false;
	return false;
}

int main() {
	ifstream fin("ariprog.in");
	ofstream fout("ariprog.out");

	int len;
	fin >> len >> limit;

	int max_num = limit * limit * 2;
	set<pair<int, int> > sequences;

	int cur;
	bool valid;
	for (int a=0; a <= max_num - len; a++) {
		if (is_bisquare(a) == false) {
			continue;
		}
		for (int b=1; b <= max_num / (len-1); b++) {
			cur = a;
			valid = true;
			for (int c=1; c<len; c++) {
				cur = a + (c*b);
				if (cur > max_num || is_bisquare(cur) == false) {
					valid = false;
					break;
				}
			}
			if (valid == true) {
				sequences.insert(make_pair(b, a));
			}
		}
	}

	if (sequences.empty() == true) {
		fout << "NONE" << endl;
	}
	else {
		for (set<pair<int, int> >::iterator it = sequences.begin(); it != sequences.end(); it++) {
			fout << it->second << " " << it->first << endl;
		}
	}

	return 0;
}
