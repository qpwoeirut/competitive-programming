/*
 * 1196c.cpp
 *
 *  Created on: Jul 24, 2019
 *      Author: Stanley
 */

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long LL;

struct Robot {
	int x, y;
	bool f[4];
	int ct;

	Robot() {}

	Robot(int _x, int _y, bool f0, bool f1, bool f2, bool f3) {
		x = _x;
		y = _y;
		f[0] = f0;
		f[1] = f1;
		f[2] = f2;
		f[3] = f3;
		ct = f0 + f1 + f2 + f3;
	}
};

bool comp_ct (const Robot& a, const Robot& b) {
	return a.ct < b.ct;
}

void solve() {
	int N;
	cin >> N;

	Robot A[100001];
	vector<int> b[4];
	int x, y;
	bool f0, f1, f2, f3;
	for (int i=0; i<N; i++) {
		cin >> x >> y >> f0 >> f1 >> f2 >> f3;
		A[i] = Robot(x, y, f0, f1, f2, f3);
		if (!f0) {
			b[0].push_back(i);
		}
		if (!f1) {
			b[1].push_back(i);
		}
		if (!f2) {
			b[2].push_back(i);
		}
		if (!f3) {
			b[3].push_back(i);
		}
	}

	int mnx = -1e5, mxx = 1e5, mny = -1e5, mxy = 1e5;
	for (int i=0; i<b[0].size(); i++) {
		mnx = max(mnx, A[b[0][i]].x);
	}
	for (int i=0; i<b[1].size(); i++) {
		mxy = min(mxy, A[b[1][i]].y);
	}
	for (int i=0; i<b[2].size(); i++) {
		mxx = min(mxx, A[b[2][i]].x);
	}
	for (int i=0; i<b[3].size(); i++) {
		mny = max(mny, A[b[3][i]].y);
	}

	if (mnx > mxx || mny > mxy) {
		cout << 0 << endl;
	}
	else {
		cout << 1 << " " << mnx << " " << mny << endl;
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
