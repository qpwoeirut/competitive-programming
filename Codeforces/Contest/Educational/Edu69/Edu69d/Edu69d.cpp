/*
 * Edu69d.cpp
 *
 *  Created on: Jul 22, 2019
 *      Author: Stanley
 */

#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

int main() {
	LL N, M, K;
	cin >> N >> M >> K;

	int A[300001];
	LL sum[300002];
	for (int i=0; i<N; i++) {
		cin >> A[i];
		sum[i] = (i == 0 ? 0 : sum[i-1] + A[i-1]);
	}

	LL mx = 0;
	for (int i=0; i<=N; i++) {
		for (int j=i+1; j<=N; j++) {
			mx = max(mx, (sum[j] - sum[i]) - (K * ((j - i + M) / M)));
		}
	}

	cout << mx << endl;

	return 0;
}
