/*
 * Edu69c.cpp
 *
 *  Created on: Jul 22, 2019
 *      Author: Stanley
 */

#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

bool comp(const int& a, const int& b) {
	return a > b;
}

int main() {
	int N, K;
	cin >> N >> K;

	int A[300001];
	int gaps[300001];
	for (int i=0; i<N; i++) {
		cin >> A[i];
		if (i > 0) {
			gaps[i-1] = A[i] - A[i-1];
		}
	}

	if (N <= K) {
		cout << 0 << endl;
		return 0;
	}

	int cost = A[N-1] - A[0];
	sort(gaps, gaps+N-1, comp);
	for (int i=0; i<K-1; i++) {
		cost -= gaps[i];
	}

	cout << cost << endl;

	return 0;
}
