/*
 * two.cpp
 *
 *  Created on: Jan 21, 2019
 *      Author: Stanley
 */

#include <fstream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

bool comp_blob(const pair<int, int>& a, const pair<int, int>& b) {
	if (a.first == b.first) {
		return a.second > b.second;
	}
	else {
		return a.first < b.first;
	}
}

int main() {
	ifstream fin("perimeter.in");
	ofstream fout("perimeter.out");

	int size;
	fin >> size;

	char grid[1001][1001];
	bool visited[1001][1001];
	int blob[1001][1001];
	vector<pair<int, int> > blobs;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			fin >> grid[i][j];
			visited[i][j] = false;
			blob[i][j] = 0;
		}
	}

	int ch_x[4] = {-1, 0, 1, 0};
	int ch_y[4] = {0, 1, 0, -1};

	queue<pair<int, int> > q;
	pair<int, int> cur, next_coord;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (grid[i][j] == '#' && visited[i][j] == false) {
				visited[i][j] = true;
				blobs.push_back(make_pair(1, 0));
				blob[i][j] = blobs.size();
				q.push(make_pair(i, j));

				while (q.size() > 0) {
					cur = q.front();
					q.pop();

					for (int i=0; i<4; i++) {
						next_coord.first = cur.first + ch_x[i];
						next_coord.second = cur.second + ch_y[i];
						if (next_coord.first < 0 || next_coord.first >= size ||
							next_coord.second < 0 || next_coord.second >= size ||
							grid[next_coord.first][next_coord.second] == '.') {
								blobs.back().second++;
								continue;
						}

						if (grid[next_coord.first][next_coord.second] == '#' &&
							visited[next_coord.first][next_coord.second] == false) {
								visited[next_coord.first][next_coord.second] = true;
								blobs.back().first++;
								blob[i][j] = blobs.size();
								q.push(next_coord);
						}
					}
				}
			}
		}
	}

	pair<int, int> largest_blob = *max_element(blobs.begin(), blobs.end(), comp_blob);
	fout << largest_blob.first << " " << largest_blob.second << endl;

	return 0;
}
