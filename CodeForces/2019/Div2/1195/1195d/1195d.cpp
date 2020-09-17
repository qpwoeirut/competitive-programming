/*
 * 1195d.cpp
 *
 *  Created on: Jul 17, 2019
 *      Author: Stanley
 */

#include <iostream>

using namespace std;

typedef long long LL;

const int MOD = 998244353;

LL p10[100];
LL pow10(int pw) {
	if (p10[pw] != 0) {
		return p10[pw];
	}
	int p = pw;
	LL n = 1;
	LL cur = 10;
	while (p > 0) {
		if (p & 1) {
			n *= cur;
			n %= MOD;
		}

		p >>= 1;
		cur = (cur % MOD) * (cur % MOD);
		cur %= MOD;
	}

	p10[pw] = n;
	return n;
}

LL a[100001];
LL f(int i, int j) {
	return ((a[i] * 10) + a[j]) % MOD;
}

LL c[1000000001];
LL compute(int n) {
	if (c[n] != 0) return c[n];
	LL res = 0;
	int p = 0;
	while (n > 0) {
		res += (n % 10) * pow10(p);
		res %= MOD;
		n /= 10;
		p += 2;
	}

	return res;
}

int main() {
	cout << 20000 << endl;
	for (int i=0; i<20000; i++) {
		cout << 1000000000 << " ";
	}
	int N;
	cin >> N;

	int A[100001];
	for (int i=0; i<N; i++) {
		cin >> A[i];
		a[i] = compute(A[i]);
	}

	LL res = 0;
	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
			res += f(i, j);
			res %= MOD;
		}
	}

	cout << res << endl;

	return 0;
}
