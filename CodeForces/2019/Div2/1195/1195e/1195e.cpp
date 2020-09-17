/*
 * 1195e.cpp
 *
 *  Created on: Jul 17, 2019
 *      Author: Stanley
 */

#include <iostream>

using namespace std;

int main() {
	int N, M, A, B;
	cin >> N >> M >> A >> B;
	int g, x, y, z;
	cin >> g >> x >> y >> z;

	int grid[3000][3000];
	for (int i=0; i<N; i++) {
		for (int j=0; j<M; j++) {
			grid[i][j] = g;
			g = ((g * x) + y % z);
		}
	}

	int sums[3000][3000];
	int cur = 0;
	for (int i=0; i<N; i++) {
		for (int j=0; j<M; j++) {
			cur += grid[i][j];
			if (i == 0) {
				sums[i] = cur;
			}
			else {
				sums[i] = sums[i-1][j];
			}
		}
	}

	int total = 0;


	return 0;
}
