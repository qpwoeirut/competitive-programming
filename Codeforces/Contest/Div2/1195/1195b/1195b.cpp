/*
 * 1195b.cpp
 *
 *  Created on: Jul 17, 2019
 *      Author: Stanley
 */

#include <iostream>

using namespace std;

int main() {
	int N, K;
	cin >> N >> K;

	int eaten = 0;
	int ct = 0;
	int add = 1;
	while (N > 0) {
		if (ct <= K) {
			ct += add;
			add++;
		}
		else {
			ct--;
			eaten++;
		}
		N--;
	}

	cout << eaten << endl;

	return 0;
}
