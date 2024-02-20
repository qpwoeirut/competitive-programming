/*
 * snakes.cpp
 *
 *  Created on: Mar 31, 2019
 *      Author: Stanley
 */

#include <cstdio>
#include <fstream>
#include <algorithm>
#include <iostream>

using namespace std;

int N, K;
int groups[400];
int min_waste[400][400][400];
const int MAX_VAL = 4100100;
int dp(int idx, int sz_idx, int changes) {
	if (idx == N || sz_idx == N) {
		return 0;
	}
	if (changes < 0) {
		return MAX_VAL;
	}
	if (min_waste[idx][sz_idx][changes] != MAX_VAL) {
		return min_waste[idx][sz_idx][changes];
	}

	int tmp = MAX_VAL;
	if (groups[idx+1] > groups[sz_idx]) {
		for (int i=idx+1; i<N; i++) {
			if (groups[idx+1] <= groups[i]) {
				tmp = min(tmp, dp(idx+1, i, changes - 1));
			}
		}
		min_waste[idx][sz_idx][changes] = tmp;
	}
	else {
		tmp = dp(idx+1, sz_idx, changes);
		for (int i=idx+1; i<N; i++) {
			if (groups[idx+1] <= groups[i]) {
				tmp = min(tmp, dp(idx+1, i, changes - 1));
			}
		}
	}

	min_waste[idx][sz_idx][changes] = (groups[sz_idx] - groups[idx]) + tmp;

	return min_waste[idx][sz_idx][changes];
}

int main() {
	ifstream fin("snakes.in");
	ofstream fout("snakes.out");

	fin >> N >> K;

	for (int i=0; i<N; i++) {
		fin >> groups[i];
		for (int j=0; j<N; j++) {
			for (int k=0; k<N; k++) {
				min_waste[i][j][k] = MAX_VAL;
			}
		}
	}

	int ans = dp(0, 0, K);
	cout << ans << endl;
	fout << ans << endl;
	fout.close();

//	FILE * fout = fopen("snakes.out", "w");
//	fprintf(fout, "%d", ans);
//	fclose(fout);

	return 0;
}
