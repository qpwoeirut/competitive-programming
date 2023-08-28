/*
 * 1195c.cpp
 *
 *  Created on: Jul 17, 2019
 *      Author: Stanley
 */

#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

int main() {
	int N;
	cin >> N;

	LL h[2][100001];
	for (int i=0; i<N; i++) {
		cin >> h[0][i];
	}
	for (int i=0; i<N; i++) {
		cin >> h[1][i];
	}

	LL mh[2][100001];
	fill(mh[0], mh[0]+N, -1);
	fill(mh[1], mh[1]+N, -1);

	LL mx0 = 0, mx1 = 0;
	for (int idx=0; idx<N; idx++) {
		mh[0][idx] = h[0][idx] + mx1;
		mh[1][idx] = h[1][idx] + mx0;

		mx0 = max(mx0, mh[0][idx]);
		mx1 = max(mx1, mh[1][idx]);
	}

	cout << max(mh[0][N-1], mh[1][N-1]) << endl;

	return 0;
}
