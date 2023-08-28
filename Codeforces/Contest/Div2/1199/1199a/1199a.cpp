/*
 * 1199a.cpp
 *
 *  Created on: Jul 30, 2019
 *      Author: Stanley
 */

#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

int main() {
	int N, X, Y;
	cin >> N >> X >> Y;

	int days[100001];
	for (int i=0; i<N; i++) {
		cin >> days[i];
	}

	for (int i=0; i<N; i++) {
		bool good = true;
		for (int j=1; good && i-j >= 0 && j<=X; j++) {
			if (days[i-j] <= days[i]) {
				good = false;
			}
		}

		for (int j=1; good && i+j<N && j<=Y; j++) {
			if (days[i+j] <= days[i]) {
				good = false;
			}
		}

		if (good) {
			cout << i+1 << endl;
			break;
		}
	}

	return 0;
}
