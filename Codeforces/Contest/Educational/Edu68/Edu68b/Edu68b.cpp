/*
 * Edu68b.cpp
 *
 *  Created on: Jul 14, 2019
 *      Author: Stanley
 */

#include <iostream>
#include <algorithm>
#include <set>
#include <string>
#include <vector>

using namespace std;

string grid[50001];
int sol(int n, int m) {
	int r[50001] = {};
	int c[50001] = {};

	for (int i=0; i<n; i++) {
		for (int j=0; j<m; j++) {
			if (grid[i][j] == '.') {
				r[i]++;
				c[j]++;
			}
		}
	}

	int best = 2e9;
	for (int i=0; i<n; i++) {
		for (int j=0; j<m; j++) {
			best = min(best, r[i] + c[j] - (grid[i][j] == '.' ? 1 : 0));
		}
	}

	return best;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int Q;
	cin >> Q;

	int n, m;
	for (int i=0; i<Q; i++) {
		cin >> n >> m;
		for (int j=0; j<n; j++) {
			cin >> grid[j];
		}
		cout << sol(n, m) << endl;
	}

	return 0;
}
