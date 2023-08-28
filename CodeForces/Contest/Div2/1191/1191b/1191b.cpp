/*
 * 1191b.cpp
 *
 *  Created on: Jul 12, 2019
 *      Author: Stanley
 */

#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int main() {
	string strs[3];
	cin >> strs[0] >> strs[1] >> strs[2];
	sort(strs, strs+3);

	int triplet = 2;
	if (strs[0] == strs[1] && strs[1] == strs[2]) {
		cout << 0 << endl;
		return 0;
	}
	else if (strs[0] == strs[1] || strs[1] == strs[2] || strs[0] == strs[2]) {
		triplet = 1;
	}

	int seq = 2;
	if (strs[0].back() == strs[1].back() && strs[0][0] + 1 == strs[1][0]) {
		seq--;
	}
	if (strs[1].back() == strs[2].back() && strs[1][0] + 1 == strs[2][0]) {
		seq--;
	}
	if (seq == 0) {
		cout << 0 << endl;
		return 0;
	}

	if (strs[0].back() == strs[2].back() && strs[0][0] + 1 == strs[2][0]) {
		seq = 1;
	}

	if (strs[0].back() == strs[1].back() && strs[0][0] + 2 == strs[1][0]) {
		seq = 1;
	}
	if (strs[1].back() == strs[2].back() && strs[1][0] + 2 == strs[2][0]) {
		seq = 1;
	}
	if (strs[0].back() == strs[2].back() && strs[0][0] + 2 == strs[2][0]) {
		seq = 1;
	}

	cout << min(triplet, seq) << endl;

	return 0;
}
