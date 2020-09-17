/*
ID: zhongbr1
TASK: subset
LANG: C++11
*/

#include <fstream>
#include <algorithm>
#include <iostream>
typedef long long LL;

using namespace std;

int N, target;
LL max_val[781][39];
LL dp(int sum, int idx) {
	if (sum == target) {
		return 1;
	}
	if (idx == N || sum > target) {
		return 0;
	}
	if (max_val[sum][idx] != -1) {
		return max_val[sum][idx];
	}

	max_val[sum][idx] = dp(sum, idx+1) + dp(sum+idx+1, idx+1);

	return max_val[sum][idx];
}

int main() {
	ifstream fin("subset.in");
	ofstream fout("subset.out");

	fin >> N;

	target = N * (N + 1);
	if (target % 4 != 0) {
		fout << 0 << endl;
		return 0;
	}
	target /= 4;

	for (int i=0; i<=target; i++) {
		for (int j=0; j<N; j++) {
			max_val[i][j] = -1;
		}
	}

	fout << dp(0, 0) / 2 << endl;
	cout << dp(0, 0) / 2 << endl;

	return 0;
}
