/*
 * crazy.cpp
 *
 *  Created on: Dec 20, 2018
 *      Author: Stanley
 *
 * Converted from previous Java submission
 * Testing differences between languages
 */

#include <fstream>
#include <algorithm>
#include <iterator>
#include <list>
#include <queue>

using namespace std;

int index_of(list<int> l, int val) {
	list<int>::iterator tmp_it = find(l.begin(), l.end(), val);
	int idx = distance(l.begin(), tmp_it);
	return idx;
}

struct Item {
	int x, y;
};

int main() {
	ifstream fin("crazy.in");
	ofstream fout("crazy.out");

	int fenceCount, cowCount;
	fin >> fenceCount >> cowCount;

	int fencePosX[1000], fencePosY[1000];
	list<int> sortedPosX, sortedPosY;
	sortedPosX.push_front(0);
	sortedPosY.push_front(0);
	for (int i = 0; i < fenceCount * 2; i++) {
		fin >> fencePosX[i] >> fencePosY[i];
		sortedPosX.push_back(fencePosX[i]);
		sortedPosY.push_back(fencePosY[i]);
//		cout << "fence i, x, y: " << i << " " << fencePosX[i] << " " << fencePosY[i] << endl;
	}

	int cowPosX[500], cowPosY[500];
	for (int i = 0; i < cowCount; i++) {
		fin >> cowPosX[i] >> cowPosY[i];
		sortedPosX.push_back(cowPosX[i]);
		sortedPosY.push_back(cowPosY[i]);
//		cout << "cow i, x, y: " << i << " " << cowPosX[i] << " " << cowPosY[i] << endl;
	}
	sortedPosX.push_back(1000001);
	sortedPosY.push_back(1000001);

	sortedPosX.sort();
	sortedPosY.sort();
	sortedPosX.unique();
	sortedPosY.unique();

	int maxX = (sortedPosX.size() * 2) + 1;
	int maxY = (sortedPosY.size() * 2) + 1;

	int tmp1, tmp2, x1, y1, x2, y2;
	char grid[maxX][maxY];
	bool visited[maxX][maxY];
	for (int i = 0; i < maxX; i++) {
		for (int j = 0; j < maxY; j++) {
			grid[i][j] = '.';
			visited[i][j] = false;
		}
	}

	for (int i = 0; i < fenceCount * 2; i += 2) {
		tmp1 = index_of(sortedPosX, fencePosX[i]) * 2;
		tmp2 = index_of(sortedPosX, fencePosX[i + 1]) * 2;
		x1 = min(tmp1, tmp2);
		x2 = max(tmp1, tmp2);

		tmp1 = index_of(sortedPosY, fencePosY[i]) * 2;
		tmp2 = index_of(sortedPosY, fencePosY[i + 1]) * 2;
		y1 = min(tmp1, tmp2);
		y2 = max(tmp1, tmp2);
//		cout << fencePosX[i] << " " << fencePosY[i] << " " << fencePosX[i+1] << " " << fencePosY[i + 1] << endl;

		if (x1 == x2) {
			while (y1 <= y2) {
				grid[x1][y1] = 'F';
				y1++;
			}
		} else {
			while (x1 <= x2) {
				grid[x1][y1] = 'F';
				x1++;
			}
		}
	}

	int x, y;
	for (int i = 0; i < cowCount; i++) {
		x = index_of(sortedPosX, cowPosX[i]) * 2;
		y = index_of(sortedPosY, cowPosY[i]) * 2;
		grid[x][y] = 'C';
	}

	short chX[4] = { 0, -1, 0, 1 };
	short chY[4] = { -1, 0, 1, 0 };

	short groupSizes[500] = { };
	queue<Item> Q;
	Item start, cur, next;
	int groupIdx = 0;
	for (int i = 0; i < maxX; i++) {
		for (int j = 0; j < maxY; j++) {
			if (visited[i][j] == false && grid[i][j] == '.') {
				start.x = i;
				start.y = j;
				Q.push(start);
				while (Q.size() > 0) {
					cur = Q.front();
					Q.pop();
					for (int dir = 0; dir < 4; dir++) {
						next.x = cur.x + chX[dir];
						next.y = cur.y + chY[dir];

						if (next.x < 0 || next.x >= maxX || next.y < 0
								|| next.y >= maxY
								|| visited[next.x][next.y] == true
								|| grid[next.x][next.y] == 'F') {
							continue;
						}

						visited[next.x][next.y] = true;
						if (grid[next.x][next.y] == 'C') {
							groupSizes[groupIdx]++;
						}

						Q.push(next);
					}
				}
				groupIdx++;
			}
		}
	}

	int largestGroup = 0;
	largestGroup = *max_element(groupSizes, groupSizes + groupIdx);
	fout << largestGroup;
	fout.close();

	return 0;
}
