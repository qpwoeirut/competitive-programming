/*
 * Edu68a.cpp
 *
 *  Created on: Jul 14, 2019
 *      Author: Stanley
 */

#include <iostream>

using namespace std;

int main() {
	int T;
	cin >> T;

	int queries[101];
	int tmp;
	for (int i=0; i<T; i++) {
		cin >> tmp >> queries[i];
	}

	for (int i=0; i<T; i++) {
		cout << queries[i] * 2 << endl;
	}


	return 0;
}
