/*
ID: zhongbr1
TASK: milk3
LANG: C++11
*/

#include <fstream>
#include <set>

using namespace std;

pair<int, int> add(int a, int b, const int capacity) {
	if (b < capacity) {
		if (a+b > capacity) {
			a = a - (capacity - b);
			b = capacity;
		}
		else {
			b = a + b;
			a = 0;
		}
	}

	return make_pair(a, b);
}

int cap[3];
bool used[20][20][20];
set<int> possible;
void recurse(const int amt[3], int tab) {
	if (amt[0] == 0) {
		possible.insert(amt[2]);
	}

	for (int i=0; i<3; i++) {
		if (amt[i] == 0) {
			continue;
		}
		for (int j=0; j<3; j++) {
			if (i == j) {
				continue;
			}

			pair<int, int> tmp = add(amt[i], amt[j], cap[j]);
			int next_amt[3];

			next_amt[0] = amt[0];
			next_amt[1] = amt[1];
			next_amt[2] = amt[2];
			next_amt[i] = tmp.first;
			next_amt[j] = tmp.second;
			if (used[next_amt[0]][next_amt[1]][next_amt[2]] == false) {
				used[next_amt[0]][next_amt[1]][next_amt[2]] = true;
				recurse(next_amt, tab+1);
			}
		}
	}
}

int main() {
	ifstream fin("milk3.in");
	ofstream fout("milk3.out");

	fin >> cap[0] >> cap[1] >> cap[2];
	int start[3] = {0, 0, cap[2]};
	used[0][0][cap[2]] = true;
	recurse(start, 0);

	bool first = true;
	for (set<int>::iterator it = possible.begin(); it != possible.end(); it++) {
		if (first == false) {
			fout << " ";
		}
		fout << *it;
		first = false;
	}
	fout << endl;

	return 0;
}
