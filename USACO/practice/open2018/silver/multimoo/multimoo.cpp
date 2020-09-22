/*
 * multimoo.cpp
 *
 *  Created on: Jul 28, 2018
 *      Author: Stanley
 *
 * 2/10 on first submission at 8:52pm on Jul 28, 2018
 * 9/10 on second submission at 8:53pm
 *
 *
 */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <queue>
#include <set>
#include <vector>

using namespace std;

struct Coord {
	int val;
	int reg_id;
};

struct Region {
	int size;
	int val;
	vector<int *> neighbor_coords;
	set<int> neighbor_reg_ids;
	set<int> visited_ids;
};

int ch_r[4] = {1,  0, -1,  0};
int ch_c[4] = {0,  1,  0, -1};

Region regions[62500];

int size;
Coord grid[250][250];

int next_row, next_col;
int cur_size = 0, cur_reg_id = 0;

bool comp_size(Region a, Region b) {
	return a.size < b.size;
}

bool comp_second(pair< pair<int, int>, int> a, pair< pair<int, int>, int> b) {
	return a.second < b.second;
}

void floodfill(int cur_row, int cur_col, int cur_val) {
	grid[cur_row][cur_col].reg_id = cur_reg_id;
	cur_size++;

	for (int i=0; i<4; i++) {
		next_row = cur_row + ch_r[i];
		next_col = cur_col + ch_c[i];
		if (next_row < 0 || next_row >= size || next_col < 0 || next_col >= size) continue;

		if (grid[next_row][next_col].val == cur_val && grid[next_row][next_col].reg_id == -1) {
			floodfill(next_row, next_col, cur_val);
		}
		else if (grid[next_row][next_col].val != cur_val) {
			regions[cur_reg_id].neighbor_coords.push_back(&(grid[next_row][next_col].reg_id));
		}
	}
}

int cur_reg_size;
set<int> visited;
void combine(int cur_val, int next_val, Region * cur_reg) {
	cur_reg_size += cur_reg->size;

	for (set<int>::iterator iter = cur_reg->neighbor_reg_ids.begin(); iter != cur_reg->neighbor_reg_ids.end(); iter++) {
		if (regions[*iter].val == next_val && binary_search(visited.begin(), visited.end(), *iter) == false) {
			visited.insert(*iter);
			combine(next_val, cur_val, &regions[*iter]);
		}
	}
}

int main() {
	ifstream fin("multimoo.in");
	ofstream fout("multimoo.out");

	fin >> size;

	for (int r=0; r<size; r++) {
		for (int c=0; c<size; c++) {
			fin >> grid[r][c].val;
			grid[r][c].reg_id = -1;
		}
	}

	for (int r=0; r<size; r++) {
		for (int c=0; c<size; c++) {
			if (grid[r][c].reg_id == -1) {
				floodfill(r, c, grid[r][c].val);
				regions[cur_reg_id].size = cur_size;
				regions[cur_reg_id].val = grid[r][c].val;
				cur_size = 0;
				cur_reg_id++;
			}
		}
	}
	const int REG_COUNT = cur_reg_id;

	int best_reg1 = max_element(regions, regions+REG_COUNT, comp_size)->size;

	for (int r=0; r<REG_COUNT; r++) {
		for (int i = 0; i < regions[r].neighbor_coords.size(); i++) {
			regions[r].neighbor_reg_ids.insert(*(regions[r].neighbor_coords[i]));
		}
	}

	map<pair<int, int>, int> double_reg_size;

//	set<int> neighbor_regs;
//	for (int r=0; r<REG_COUNT; r++) {
//		neighbor_regs = regions[r].neighbor_reg_ids;
//		for (set<int>::iterator iter = neighbor_regs.begin(); iter != neighbor_regs.end(); iter++) {
//			pair<int, int> vals = minmax(*iter, regions[r].val);
//			if (double_reg_size.find(vals) == double_reg_size.end()) {
//				cur_reg_size = 0;
//				visited.clear();
//				visited.insert(r);
//				combine(regions[r].val, regions[*iter].val, &regions[r]);
//				double_reg_size[vals] = cur_reg_size;
//			}
//		}
//	}

	queue<int> need_to_visit;
	int cur_reg_idx;
	for (int r=0; r<REG_COUNT; r++) {
		need_to_visit.push(r);
		while (need_to_visit.size() > 0) {
			cur_reg_idx = need_to_visit.front();
			need_to_visit.pop();

			for (set<int>::iterator iter = regions[cur_reg_idx].neighbor_reg_ids.begin(); iter != regions[cur_reg_id].neighbor_reg_ids.end(); iter++) {

			}
		}
	}

	int best_reg2 = max_element(double_reg_size.begin(), double_reg_size.end(), comp_second)->second;

	fout << best_reg1 << endl << best_reg2;
	cout << best_reg1 << endl << best_reg2;

	return 0;
}

