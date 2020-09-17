/*
 * 1191d.cpp
 *
 *  Created on: Jul 12, 2019
 *      Author: Stanley
 */

#include <iostream>
#include <algorithm>

using namespace std;

int main() {
	int N;
	cin >> N;

	int stones[N];
	for (int i=0; i<N; i++) {
		cin >> stones[i];
	}

	sort(stones, stones+N);

	bool same = false;
	bool turn = true;
	for (int i=0; i<N; i++) {
		if (i+2 < N && (stones[i] == stones[i+1] || stones[i] + 1 == stones[i+1]) && stones[i+1] == stones[i+2]) {
			cout << "cslnb" << endl;
			return 0;
		}
		if (i+1 < N && stones[i] == stones[i+1]) {
			if (same == true || stones[i] == 0) {
				cout << "cslnb" << endl;
				return 0;
			}
			else {
				same = true;
			}
		}

		if (((stones[i] - i) % 2) != 0) {
			turn = !turn;
		}
	}

	cout << (turn ? "cslnb" : "sjfnb") << endl;

	return 0;
}
