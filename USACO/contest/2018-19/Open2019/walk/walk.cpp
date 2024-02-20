/*
 * walk.cpp
 *
 *  Created on: Mar 31, 2019
 *      Author: Stanley
 */

#include <fstream>
#include <iostream>
#include <algorithm>

typedef long long LL;

using namespace std;

bool comp_first(const pair<int, int>& a, const pair<int, int>& b) {
	return a.first < b.first;
}

int main() {
	ifstream fin("walk.in");
	ofstream fout("walk.out");

	int N, G;
	fin >> N >> G;

	const LL Mx = 2019201913, My = 2019201949, Md = 2019201997;

	int dist[750][750];
	pair<int, int> min_dist[7500];
	for (int i=0; i<N; i++) {
		min_dist[i].first = Md;
		min_dist[i].second = -1;
	}
	LL tmp;
	for (int i=0; i<N; i++) {
		for (int j=i + 1; j<N; j++) {
			tmp = (Mx * (i + 1)) + (My * (j + 1));
			tmp %= Md;
			dist[i][j] = tmp;
			if (min_dist[i].first > tmp) {
				min_dist[i].first = tmp;
				min_dist[i].second = j;
			}
			if (min_dist[j].first > tmp) {
				min_dist[j].first = tmp;
				min_dist[j].second = i;
			}
		}
	}

	sort(min_dist, min_dist+N, comp_first);

	int ans = min_dist[N + 1 - G].first;
	cout << ans << endl;
	fout << ans << endl;

	return 0;
}
