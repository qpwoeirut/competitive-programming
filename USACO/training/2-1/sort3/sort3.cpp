/*
 ID: zhongbr1
 TASK: sort3
 LANG: C++11
 */

#include <fstream>
#include <algorithm>
#include <set>

using namespace std;

int vals[1000];
int amt[3] = { 0, 0, 0 };
int ans = 0;

void swap_vals(int val1, int val2) {
	int idx1 = (val1 != 0 ? amt[val1 - 1] : 0), e1 = amt[val1];
	int idx2 = (val2 != 0 ? amt[val2 - 1] : 0), e2 = amt[val2];

	while (idx1 < e1 && idx2 < e2) {
		while (vals[idx1] != val2) {
			idx1++;
			if (idx1 == e1) {
				return;
			}
		}
		while (vals[idx2] != val1) {
			idx2++;
			if (idx2 == e2) {
				return;
			}
		}
		if (vals[idx1] == val2 && vals[idx2] == val1) {
			ans++;
			vals[idx1] = val1;
			vals[idx2] = val2;
			idx1++;
			idx2++;
		}
	}
}

int main() {
	ifstream fin("sort3.in");
	ofstream fout("sort3.out");

	int val_c;
	fin >> val_c;

	for (int i = 0; i < val_c; i++) {
		fin >> vals[i];
		vals[i]--;
		amt[vals[i]]++;
	}
	amt[1] += amt[0];
	amt[2] += amt[1];

	swap_vals(0, 1);
	swap_vals(0, 2);
	swap_vals(1, 2);

	int ans2 = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = (i == 0 ? 0 : amt[i-1]); j < amt[i]; j++) {
			if (vals[j] != i) {
				ans2++;
			}
		}
	}

	ans += (ans2 * 2) / 3;

	fout << ans << endl;

	return 0;
}
