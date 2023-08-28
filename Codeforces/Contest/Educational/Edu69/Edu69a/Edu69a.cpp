/*
 * Edu69a.cpp
 *
 *  Created on: Jul 22, 2019
 *      Author: Stanley
 */

#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

int len[100001];
int solve() {
	int N;
	cin >> N;

	for (int i=0; i<N; i++) {
		cin >> len[i];
	}

	sort(len, len+N);

	return min(len[N-2] - 1, N-2);
}

int main() {
	int T;
	cin >> T;
	while (T > 0) {
		T--;
		cout << solve() << endl;
	}

	return 0;
}
