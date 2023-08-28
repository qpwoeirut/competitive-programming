/*
 * Edu68d.cpp
 *
 *  Created on: Jul 14, 2019
 *      Author: Stanley
 */

#include <iostream>
#include <map>

using namespace std;

map<int,bool> visited;
bool sol(const int& n, const int& k) {
	if (k % 3 != 0) {

	}
}

int main() {
	int T;
	cin >> T;

	int n, k;
	for (int i=0; i<T; i++) {
		visited.clear();
//		cin >> n >> k;
		k = 12;
		cout << i << " "  << k << ": " << (sol(i, k) ? "Alice": "Bob") << endl;
	}

	return 0;
}
