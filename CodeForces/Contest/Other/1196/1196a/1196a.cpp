/*
 * 1196a.cpp
 *
 *  Created on: Jul 24, 2019
 *      Author: Stanley
 */

#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

LL solve() {
	LL a[3];
	cin >> a[0] >> a[1] >> a[2];
	sort(a, a+3);

	return (a[0] + a[1] + a[2]) / 2;
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
