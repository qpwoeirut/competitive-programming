/*
 * nesting_depth.cpp
 *
 *  Created on: Apr 4, 2020
 *      Author: Stanley
 */


#include <iostream>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>

using namespace std;

typedef long long ll;

void solve(int tc) {
	string s;
	cin >> s;

	vector<char> ans;
	int d = 0;
	for (int i=0; i<s.size(); i++) {
		while (s[i] - '0' > d) {
			ans.push_back('(');
			d++;
		}
		while (s[i] - '0' < d) {
			ans.push_back(')');
			d--;
		}
		ans.push_back(s[i]);
		assert(d >= 0);
	}
	while (d > 0) {
		d--;
		ans.push_back(')');
	}

	cout << "Case #" << tc << ": ";
	for (int i=0; i<ans.size(); i++) {
		cout << ans[i];
	}
	cout << endl;
}

int main() {
	int T;
	cin >> T;

	for (int i=1; i<=T; i++) {
		solve(i);
	}

	return 0;
}
