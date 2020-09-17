/*
 * esab_atad.cpp
 *
 *  Created on: Apr 4, 2020
 *      Author: Stanley
 */


#include <iostream>
#include <algorithm>
#include <cassert>
#include <string>

using namespace std;

typedef long long ll;

void setIO() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
}

int T, B;
string ans;
void flip() {
	for (int i=0; i<B; i++) {
		if (ans[i] == '0') {
			ans[i] = '1';
		}
		else if (ans[i] == '1') {
			ans[i] = '0';
		}
	}
}

void rev() {
	for (int i=0; i<B-i; i++) {
		swap(ans[i], ans[B-i-1]);
	}
}

int Q = 0;
int same = -1, diff = -1;
void handle_quantum() {
	assert(diff != -1 || same != -1);
	char ch_diff, ch_same;
	if (diff == -1) {
		Q++;
        assert(Q <= 150);
		cout << same+1 << endl;
	    cout.flush();
		cin >> ch_same;
		assert(ch_same != 'N');

		if (ans[same] != ch_same) {
			flip();
		}
	}
	else if (same == -1) {
		Q++;
        assert(Q <= 150);
		cout << diff+1 << endl;
	    cout.flush();
		cin >> ch_diff;
		assert(ch_diff != 'N');

		if (ans[diff] != ch_diff) {
			flip();
		}
	}
	else {
		Q++;
        assert(Q <= 150);
		cout << diff+1 << endl;
		cin >> ch_diff;
		assert(ch_diff != 'N');

		Q++;
        assert(Q <= 150);
		cout << same+1;
		cin >> ch_same;
		assert(ch_same != 'N');

		if (ans[diff] != ch_diff && ans[same] != ch_same) {
			flip();
		}
		else if (ans[diff] != ch_diff) {
			rev();
		}
		else if (ans[same] != ch_same) {
			flip();
			rev();
		}
	}
}

bool solve(int tc) {
	ans = string(B, '*');

	Q = 0;
	same = diff = -1;
	for (int i=0; i<=B-i-1; i++) {
		Q++;
        assert(Q <= 150);
		if (Q > 1 && Q % 10 == 1) {
			handle_quantum();
		}
		cout << i+1 << endl;
	    cout.flush();
		cin >> ans[i];
		assert(ans[i] != 'N');

		if (i == B-i-1) break;
		Q++;
        assert(Q <= 150);
		if (Q > 1 && Q % 10 == 1) {
			handle_quantum();
		}
		cout << B-i << endl;
	    cout.flush();
		cin >> ans[B-i-1];
		assert(ans[B-i-1] != 'N');


		if (same == -1 && ans[i] == ans[B-i-1]) {
			same = i;
		}
		if (diff == -1 && ans[i] != ans[B-i-1]) {
			diff = i;
		}
	}

	cout << ans << endl;
	cout.flush();
	char verdict;
	cin >> verdict;
	return verdict == 'Y';
}

int main() {
	setIO();

	cin >> T >> B;

	for (int i=1; i<=T; i++) {
		if (solve(i) == false) {
			return 0;
		}
	}

	return 0;
}
