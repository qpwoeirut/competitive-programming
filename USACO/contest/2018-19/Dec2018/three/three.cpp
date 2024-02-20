/*
 * three.cpp
 *
 *  Created on: Dec 16, 2018
 *      Author: Stanley
 */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>

using namespace std;

struct Item {
	int r, c;
	int group;
};

struct Coord {
	char val;
	int group;
	bool visited;
};

int height, sz;
Coord grid[100][10];
int bounds[4] = {0, height-1, 0, 9};
int ch_r[4] = {0,  1,  0, -1};
int ch_c[4] = {1,  0, -1,  0};
vector<int> group_sz;
queue<Item> q;
Item start, cur, next_coord;

void mark_group() {
	while (q.size() > 0) {
		cur = q.front();
		q.pop();
		cout << "cur r, c, val, group: " << cur.r << " " << cur.c << " " << grid[cur.r][cur.c].val << " " << cur.group << endl;
		for (int i = 0; i < 4; i++) {
			next_coord.r = cur.r + ch_r[i];
			next_coord.c = cur.c + ch_c[i];
			if (grid[next_coord.r][next_coord.c].visited == true ||
				next_coord.r < 0 || next_coord.r >= height ||
				next_coord.c < 0 || next_coord.c >= 10 ||
				grid[next_coord.r][next_coord.c].val != grid[cur.r][cur.c].val) {
				continue;
			}
			next_coord.group = cur.group;
			grid[next_coord.r][next_coord.c].group = next_coord.group;
			grid[next_coord.r][next_coord.c].visited = true;
			group_sz[cur.group]++;
			q.push(next_coord);
		}
	}
}

void mark_groups() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < 10; j++) {
			if (grid[i][j].visited == false && grid[i][j].val != '0') {
				grid[i][j].visited = true;
				start.r = i;
				start.c = j;
				start.group = group_sz.size();
				grid[i][j].group = start.group;
				group_sz.push_back(1);
				q.push(start);
				mark_group();
			}
		}
	}
}

void gravity() {
	int down;
	for (int i = height - 2; i >= 0; i--) {
		for (int j = 0; j < 10; j++) {
			if (grid[i][j].val != '0') {
				for (down = 1; i + down < height; down++) {
					if (grid[i + down][j].val != '0') {
						break;
					}
				}
				grid[i + down - 1][j].val = grid[i][j].val;
				if (down > 1) {
					grid[i][j].val = '0';
				}
			}
		}
	}
}

bool remove_groups() {
	bool changed = false;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < 10; j++) {
			if (grid[i][j].val != '0' && group_sz[grid[i][j].group] >= sz) {
				cout << "removed i, j, val, group: " << i << " " << j << " " << grid[i][j].val << " " << grid[i][j].group << endl;
				changed = true;
				grid[i][j].val = '0';
				grid[i][j].group = -1;
			}
		}
	}

	return changed;
}

int main() {
	ifstream fin("mooyomooyo.in");
	ofstream fout("mooyomooyo.out");

	fin >> height >> sz;

	for (int i=0; i<height; i++) {
		for (int j=0; j<10; j++) {
			fin >> grid[i][j].val;
		}
	}

	bool change;
	do {
		for (int i=0; i<height; i++) {
			for (int j=0; j<10; j++) {
				grid[i][j].group = -1;
				grid[i][j].visited = (grid[i][j].val == 0);
			}
		}
		group_sz.clear();
		mark_groups();
		for (int i=0; i<group_sz.size(); i++) {
			cout << "i, sz: " << i << " " << group_sz[i] << endl;
		}
		change = remove_groups();
		gravity();
		for (int i=0; i<height; i++) {
			for (int j=0; j<10; j++) {
				cout << grid[i][j].val;
			}
			cout << endl;
		}
	} while (change);

	for (int i=0; i<height; i++) {
		for (int j=0; j<10; j++) {
			fout << grid[i][j].val;
		}
		fout << endl;
	}

	return 0;
}
