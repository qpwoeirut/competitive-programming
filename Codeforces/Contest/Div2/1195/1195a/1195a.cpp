/*
 * 1195a.cpp
 *
 *  Created on: Jul 17, 2019
 *      Author: Stanley
 */

#include <iostream>

using namespace std;

int main() {
	int N, K;
	cin >> N >> K;

	int ans = 0;
	int ct[1001] = {};
	int tmp;
	for (int i=0; i<N; i++) {
		cin >> tmp;
		ct[tmp-1]++;
	}

	int rem = (N+1) / 2;
	for (int i=0; i<K; i++) {
		while (rem > 0 && ct[i] >= 2) {
			rem--;
			ct[i] -= 2;

			ans += 2;
		}
	}

	ans += rem;
	cout << ans << endl;

	return 0;
}
