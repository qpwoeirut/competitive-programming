/*
ID: zhongbr1
TASK: pprime
LANG: C++11
*/

#include <fstream>
#include <cmath>
#include <set>
#include <vector>

using namespace std;

int a, b;
set<int> palins;
vector<int> digits;
int tmp;
void gen_palins() {
	if (digits[0] * pow(10, (digits.size() * 2) - 2) > b) {
		return;
	}

	tmp = 0;
	for (int i=0; i<digits.size(); i++) {
		tmp += (digits[i] * pow(10, (digits.size() * 2) - 1 - i));
		if (i != (digits.size() * 2) - 1 - i) {
			tmp += digits[i] * pow(10, i);
		}
	}
	if (a <= tmp && tmp <= b) {
		palins.insert(tmp);
	}

	tmp = 0;
	for (int i=0; i<digits.size(); i++) {
		tmp += (digits[i] * pow(10, (digits.size() * 2) - 2 - i));
		if (i != (digits.size() * 2) - 2 - i) {
			tmp += digits[i] * pow(10, i);
		}
	}
	if (a <= tmp && tmp <= b) {
		palins.insert(tmp);
	}

	for (int i=0; i<10; i++) {
		digits.push_back(i);
		gen_palins();
		digits.pop_back();
	}
}

int main() {
	ifstream fin("pprime.in");
	ofstream fout("pprime.out");

	fin >> a >> b;

	for (int i=1; i<10; i++) {
		if (a <= i && i <= b) {
			palins.insert(i);
		}
		digits.clear();
		digits.push_back(i);
		gen_palins();
	}

	bool valid;
	for (set<int>::iterator it = palins.begin(); it != palins.end(); it++) {
		valid = true;
		for (int i=2; i<=sqrt(*it); i++) {
			if (*it % i == 0) {
				valid = false;
				break;
			}
		}
		if (valid == true) {
			fout << *it << endl;
		}
	}

	return 0;
}
