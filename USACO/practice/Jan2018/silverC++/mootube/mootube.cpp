/*
 * mootube.cpp
 *
 *  Created on: Dec 14, 2018
 *      Author: Stanley
 */

#include <fstream>
#include <iostream>
#include <map>
#include <queue>

using namespace std;

struct comp_rel {
	const bool operator() (const pair<int, int>&a, const pair<int, int>&b) const {
		return a.first > b.first;
	}
};

int main() {
	cout << "test1" << endl;
	ifstream fin("mootube.in");
	ofstream fout("mootube.out");

	int video_c, query_c;
	fin >> video_c >> query_c;

	map<int, map<int, int> > adj_mat;
	map<int, map<int, bool> > finalized;
	bool finished[5000];
	fill(finished, finished+video_c, false);

	cout << "test2" << endl;
	int tmp_a, tmp_b, tmp_r;
	for (int v=0; v<video_c; v++) {
		fin >> tmp_a >> tmp_b >> tmp_r;
		adj_mat[tmp_a-1][tmp_b-1] = tmp_r;
		adj_mat[tmp_b-1][tmp_a-1] = tmp_r;
	}

	cout << "test3" << endl;
	priority_queue<pair<int, int>, vector<pair<int, int> >, comp_rel> Q;
	int start, relevance, suggested;
	int cur_rel, cur_node;
	for (int q=0; q<query_c; q++) {
		fin >> start >> relevance;
		start--;
		suggested = 0;
		if (finished[start] == false) {
			Q.push(make_pair(0, start));
			while (Q.size() > 0) {
				cur_rel = Q.top().first;
				cur_node = Q.top().second;
				Q.pop();

				if (finalized[start][cur_node] || adj_mat[start][cur_node] <= cur_rel) {
					continue;
				}

				for (int i=0; i<video_c; i++) {
					if (finalized[cur_node][i] == false && adj_mat[cur_node][i] > 0 &&
						adj_mat[start][i] > 0 && adj_mat[start][i] > cur_rel + adj_mat[cur_node][i]) {
							adj_mat[start][i] = cur_rel + adj_mat[cur_node][i];
							adj_mat[i][start] = cur_rel + adj_mat[cur_node][i];
							Q.push(make_pair(adj_mat[start][i], i));
					}
				}

				finalized[start][cur_node] = true;
			}
			finished[start] = true;
		}

		for (int i=0; i<video_c; i++) {
			if (adj_mat[start][i] >= relevance) {
				suggested++;
			}
		}

		fout << suggested << endl;
	}

	return 0;
}
