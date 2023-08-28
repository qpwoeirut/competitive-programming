/*
 * 1196d.cpp
 *
 *  Created on: Jul 24, 2019
 *      Author: Stanley
 */

#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

typedef long long LL;

inline int c2i(char c) {
	if (c == 'R') {
		return 0;
	}
	else if (c == 'G') {
		return 1;
	}
	else if (c == 'B') {
		return 2;
	}
	else return -1;
}

void solve() {
	int N, K;
	cin >> N >> K;

	string s;
	cin >> s;

	int ct[3][3];
	for (int i=0; i<3; i++) {
		for (int j=0; j<3; j++) {
			ct[i][j] = 0;
		}
	}

	int ans = K - 1;
	int a, b, c;
	for (int i=0; i<N; i++) {
		if (i >= K) {
			ct[(i - K) % 3][c2i(s[i - K])]--;
		}

		ct[i % 3][c2i(s[i])]++;

		for (int j=0; j<3; j++) {
			a = (c2i(s[i]) + j) % 3;
			b = (a+1) % 3;
			c = (a+2) % 3;

			int rem = ((K+2) / 3) + ((K+1) / 3) + (K/3);
			rem -= ct[i % 3][a];
			rem -= ct[(i+1) % 3][b];
			rem -= ct[(i+2) % 3][c];

			ans = min(ans, rem);
		}
	}

	cout << ans << endl;
}

int main() {
	int T;
	cin >> T;
	while (T > 0) {
		T--;
		solve();
	}

	return 0;
}
