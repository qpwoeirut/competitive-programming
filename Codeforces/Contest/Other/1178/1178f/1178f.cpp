/*
 * 1178f.cpp
 *
 *  Created on: Jul 20, 2019
 *      Author: Stanley
 */

#include <iostream>

using namespace std;

typedef long long LL;

const int MOD = 998244353;

LL f[501];
int c[501];
int p[501];

LL ways(int strip[], int start, int end, int color) {
	if (p[color] < start || p[color] >= end) return 0;
	LL w = 0;
	int s=p[color], e=p[color];

	for (; start<s; s--) {
		if (strip[s] != strip[p[color]]) {
			s++;
			break;
		}
	}
	for (; e<end; e++) {
		if (strip[e] != strip[p[color]]) {
			e--;
			break;
		}
	}

	for (int i=s; i<e; i++) {

	}

	for (int i=s; i<e; i++) {
		for (int j=i+1; j<e; j++) {
//			w += 1 +
		}
	}

	return w;
}

int main() {
	int N, M;
	cin >> N >> M;

	for (int i=0; i<N; i++) {
		cin >> c[i];
		c[i]--;
		p[c[i]] = i;
	}
	f[0] = 1;
	for (int i=1; i<=N; i++) {
		f[i] = (f[i-1] * i) % MOD;
	}

	cout << ways(c, 0, N, 0);

	return 0;
}
