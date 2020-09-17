/*
 * feast.cpp
 *
 *  Created on: Feb 28, 2019
 *      Author: Stanley
 */

#include <fstream>
#include <algorithm>
#include <queue>

using namespace std;

bool nw[10000000];

int main() {
	ifstream fin("feast.in");
	ofstream fout("feast.out");

	int limit, orange, lemon;
	fin >> limit >> orange >> lemon;

	int a = min(orange, lemon), b = max(orange, lemon);

	nw[0] = true;
	priority_queue<int> water;

	int ans;
	for (int i=0; i<=limit*2; i++) {
		if (nw[i] == false) {
			continue;
		}
		if (i+a < limit) {
			nw[i+a] = true;
			ans = i + a;
		}
		else if (i+a == limit || i+a == limit * 2) {
			fout << limit << endl;
			return 0;
		}
		else if (i+a < limit*2) {
			nw[i+a] = true;
		}

		if (i+b < limit) {
			nw[i+b] = true;
			ans = i + b;
		}
		else if (i+b == limit || i+b == limit * 2) {
			fout << limit << endl;
			return 0;
		}
		else if (i+b < limit*2) {
			nw[i+b] = true;
		}

		if (nw[i/2] == false) {
			water.push(i/2);
		}
	}

	int cur;
	while (water.size() > 0) {
		cur = water.top();
		water.pop();

		if (cur+a < limit && nw[cur+a] == false) {
			water.push(cur+a);
		}
		else if (cur+a == limit) {
			fout << limit << endl;
			return 0;
		}

		if (cur+b < limit && nw[cur+b] == false) {
			water.push(cur+b);
		}
		else if (cur+b == limit) {
			fout << limit << endl;
			return 0;
		}
	}

	fout << max(cur, ans) << endl;

	return 0;
}
