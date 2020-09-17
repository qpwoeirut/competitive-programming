/*
 * one.cpp
 *
 *  Created on: Jan 21, 2019
 *      Author: Stanley
 */
#include <iostream>

#include <fstream>
#include <bitset>
#include <queue>
#include <vector>

using namespace std;

int main() {
	ifstream fin("planting.in");
	ofstream fout("planting.out");

	int field_c;
	fin >> field_c;

	int grass[100001];
	vector<int> paths[100000];
	int tmp_a, tmp_b;
	for (int p=0; p<field_c-1; p++) {
		fin >> tmp_a >> tmp_b;
		paths[tmp_a-1].push_back(tmp_b-1);
		paths[tmp_b-1].push_back(tmp_a-1);
		grass[p] = -1;
	}
	grass[field_c-1] = -1;

	int max_grass = 1;
	bitset<100001> used;

	queue<int> q;
	q.push(0);
	grass[0] = 0;
	for (int i=0; i<field_c; i++) {
		cout << grass[i] << endl;
	}
	cout << endl << endl;

	int cur, cur_grass;
	vector<int> unvisited;
	while (q.size() > 0) {
		cur = q.front();
		q.pop();

		unvisited.clear();
		used.reset();
		used.set(grass[cur]);
		for (int i=0; i<paths[cur].size(); i++) {
			if (grass[paths[cur][i]] != -1) {
				used.set(grass[paths[cur][i]]);
			}
			else {
				unvisited.push_back(paths[cur][i]);
			}
		}

		cur_grass = 0;
		while (unvisited.size() > 0) {
			if (used.test(cur_grass) == false) {
				grass[unvisited[0]] = cur_grass;
				cout << "set: " << grass[unvisited[0]] << " " << cur_grass << endl;
				q.push(unvisited[0]);
				unvisited.erase(unvisited.begin());
			}
			cur_grass++;
		}
		max_grass = max(max_grass, cur_grass);
	}

	for (int i=0; i<field_c; i++) {
		cout << grass[i] << endl;
	}
	cout << endl << endl;

	fout << max_grass;
	cout << max_grass;

	return 0;
}
