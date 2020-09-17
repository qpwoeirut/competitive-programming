/*
 * 1a.cpp
 *
 *  Created on: May 25, 2019
 *      Author: Stanley
 */

#include <iostream>

using namespace std;

int main() {
	int N, M, A;
	cin >> N >> M >> A;

	long long rows = (N + A - 1) / A;
	long long cols = (M + A - 1) / A;
	long long ans = rows * cols;

	cout << ans << endl;

	return 0;
}
