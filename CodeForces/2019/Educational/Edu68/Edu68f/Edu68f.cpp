/*
 * Edu68f.cpp
 *
 *  Created on: Jul 14, 2019
 *      Author: Stanley
 */

#include <iostream>

using namespace std;

typedef long long LL;

bool sol(const int& n, const int& k) {
	if (n == 0) return false;
	if (n == 1 || n == 2 || n == k) return true;

	return sol(n-k, k) || sol(n-2, k) || sol(n-1, k);
}

int main() {
	int N;
	LL T;
	cin >> T;

	int n, k;
	for (int i=0; i<T; i++) {
		cin >> n >> k;
		cout << (sol(n, k) ? "Alice": "Bob") << endl;
	}

	return 0;
}


// 0 1 2 3 4 5 6 7 8 9 10
// L W W W L W W W L W W
// L W W L W W L W W L W
// L W W L W W L W W W L W W
