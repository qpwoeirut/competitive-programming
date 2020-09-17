/*
ID: zhongbr1
TASK: runround
LANG: C++11
*/

#include <fstream>
#include <algorithm>
#include <cmath>
#include <deque>
#include <set>

typedef unsigned long long ULL;

using namespace std;

bool used[10];

deque<int> digits;
bool to_digits(int num, bool stop_if_invalid = true) {
	digits.clear();
	fill(used, used + 10, false);
	used[0] = true;
	int digit;
	while (num > 0) {
		digit = num % 10;
		if (used[digit] && stop_if_invalid) {
			return false;
		}
		used[digit] = true;
		digits.push_front(num % 10);
		num /= 10;
	}
	return true;
}

bool is_runaround(ULL num) {
	if (to_digits(num) == false) {
		return false;
	}

	set<int> visited;
	int cur = 0;
	for (int i=0; i<digits.size(); i++) {
		cur += digits[cur];
		cur %= digits.size();
		if (visited.find(cur) != visited.end()) {
			return false;
		}
		visited.insert(cur);
	}

	return cur == 0;
}

ULL from_digits(deque<int> D) {
	ULL num = 0;
	for (int i=0; i<D.size(); i++) {
		num += D[i] * pow(10, D.size() - i - 1);
	}

	return num;
}

ULL next_unique_nonzero(deque<int> D) {
	fill(used, used + 10, false);
	used[0] = true;

	for (int idx = 0; idx<D.size(); idx++) {
		if (used[D[idx]]) {
			D[idx]++;
			for (int i=idx; i>=0; i--) {
				if (D[i] == 10) {
					D[i] = 0;
					if (i > 0) {
						D[i - 1]++;
					}
					else {
						D.push_front(1);
						i++;
						idx++;
					}
				}
			}

			for (int i=idx+1; i<D.size(); i++) {
				D[i] = 1;
			}

			return next_unique_nonzero(D);
		}
		used[D[idx]] = true;
	}

	return from_digits(D);
}

int main() {
	ifstream fin("runround.in");
	ofstream fout("runround.out");

	ULL M;
	fin >> M;

	do {
		to_digits(M+1, false);
		M = next_unique_nonzero(digits);
	}
	while (is_runaround(M) == false);

	fout << M << endl;

	return 0;
}
