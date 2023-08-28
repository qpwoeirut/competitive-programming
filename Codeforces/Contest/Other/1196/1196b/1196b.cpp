/*
 * 1196b.cpp
 *
 *  Created on: Jul 24, 2019
 *      Author: Stanley
 */

#include <iostream>
#include <vector>

using namespace std;

typedef long long LL;

void solve() {
	int N, K;
	cin >> N >> K;

	int A[200001];
	for (int i=0; i<N; i++) {
		cin >> A[i];
		A[i] &= 1;
	}

	int cur = 0;
	vector<int> parts;
	for (int i=0; i<N; i++) {
		cur += A[i];
		if (((cur & 1) == 1) && parts.size() + 1 < K) {
			parts.push_back(i+1);
			cur = 0;
		}
	}

	if (cur & 1) {
		cout << "YES" << endl;
		for (int i=0; i<parts.size(); i++) {
			cout << parts[i] << " ";
		}
		cout << N << endl;
	}
	else {
		cout << "NO" << endl;
	}
}

int main() {
	int T;
	cin >> T;
	while (T > 0) {
		T--;
		solve();
	}

	return 0;
}
