/*
ID: zhongbr1
TASK: wormhole
LANG: C++11
*/

#include <fstream>
#include <algorithm>
#include <bitset>
#include <map>
#include <set>
#include <vector>

using namespace std;


struct Wormhole {
	int x, y;
};

Wormhole whs[12];
bool comp_x (const int a, const int b) {
	return whs[a].x < whs[b].x;
}

int wh_c;
int find_set(const bitset<12>& btst) {
	for (int i=0; i<wh_c; i++) {
		if (btst.test(i) == true) {
			return i;
		}
	}
	return -1;
}

int cycles = 0;
map<int, vector<int> > rows;
vector<pair<int, int> > pairs;
set<int> visited;
int connected[12];
void check() {
	for (int i=0; i<wh_c/2; i++) {
		connected[pairs[i].first] = pairs[i].second;
		connected[pairs[i].second] = pairs[i].first;
	}

	int cur_wh;
	for (int i=0; i<wh_c; i++) {
		cur_wh = connected[i];
		visited.clear();
		while (rows[whs[cur_wh].y].back() != cur_wh) {
			if (find(visited.begin(), visited.end(), cur_wh) != visited.end()) {
				cycles++;
				return;
			}
			else {
				visited.insert(cur_wh);
				for (int i=0; i<rows[whs[cur_wh].y].size(); i++) {
					if (rows[whs[cur_wh].y][i] == cur_wh) {
						cur_wh = connected[rows[whs[cur_wh].y][i+1]];
						break;
					}
				}
			}
		}
	}
}

bitset<12> remaining;
void connect() {
	int count = 0;
	int first_idx = -1;
	for (int i=0; i<wh_c; i++) {
		if (remaining.test(i) == true) {
			count++;
			if (count == 1) {
				first_idx = i;
				remaining.reset(i);
			}
		}
	}

	if (count == 2) {
		int second_idx = find_set(remaining);
		remaining.reset(second_idx);
		pairs.push_back(make_pair(first_idx, second_idx));
		check();
		pairs.pop_back();
		remaining.set(second_idx);
	}
	else {
		for (int i=first_idx+1; i<wh_c; i++) {
			if (remaining.test(i) == true) {
				remaining.reset(i);
				pairs.push_back(make_pair(first_idx, i));
				connect();
				pairs.pop_back();
				remaining.set(i);
			}
		}
	}

	remaining.set(first_idx);
}

int main() {
	ifstream fin("wormhole.in");
	ofstream fout("wormhole.out");

	fin >> wh_c;

	for (int w=0; w<wh_c; w++) {
		fin >> whs[w].x >> whs[w].y;
		rows[whs[w].y].push_back(w);
	}

	for (map<int, vector<int> >::iterator iter = rows.begin(); iter != rows.end(); iter++) {
		if (iter->second.size() > 1) {
			sort(iter->second.begin(), iter->second.end(), comp_x);
		}
	}

	remaining.set();
	connect();

	fout << cycles << endl;

	return 0;
}
