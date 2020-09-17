/*
 ID: zhongbr1
 TASK: castle
 LANG: C++11
 */

#include <fstream>
#include <algorithm>
#include <set>

using namespace std;

int cols, rows;
bool wall[50][50][4];
int room_sz[2500];
int room[50][50];
set<int> adj_rooms[2500];

int cur_room = 0;
int ch_r[4] = { 0, -1, 0, 1 };
int ch_c[4] = { -1, 0, 1, 0 };
int next_r, next_c;
void dfs(int row, int col) {
	for (int i = 0; i < 4; i++) {
		next_r = row + ch_r[i];
		next_c = col + ch_c[i];
		if (next_r < 0 || next_r >= rows || next_c < 0 || next_c >= cols) {
			continue;
		}
		if (room[next_r][next_c] == -1 && wall[row][col][i] == false) {
			room[next_r][next_c] = cur_room;
			room_sz[cur_room]++;
			dfs(next_r, next_c);
		}
		else if (room[next_r][next_c] != -1 && room[next_r][next_c] != cur_room) {
			adj_rooms[cur_room].insert(room[next_r][next_c]);
			adj_rooms[room[next_r][next_c]].insert(cur_room);
		}
	}
}
pair<char, pair<int, int> > find_optimal_wall(int rm1, int rm2) {
	int rm_r, rm_c;
	char dir;
	int o[4] = { 0, 3, 1, 2 };
	for (int j = 0; j < cols; j++) {
		for (int i = rows - 1; i >= 0; i--) {
			if (room[i][j] == rm1) {
				for (int k = 0; k < 4; k++) {
					if (i + ch_r[o[k]] < 0 || i + ch_r[o[k]] >= rows || j + ch_c[o[k]] < 0 || j + ch_c[o[k]] >= cols) {
						continue;
					}
					if (room[i + ch_r[o[k]]][j + ch_c[o[k]]] == rm2) {
						if (o[k] == 0 || o[k] == 2) {
							rm_r = i;
							rm_c = min(j, j + ch_c[o[k]]);
							dir = 'E';
						}
						else {
							rm_r = max(i, i + ch_r[o[k]]);
							rm_c = j;
							dir = 'N';
						}
						j = 51;
						i = -1;
						break;
					}
				}
			}
		}
	}
	rm_r++;
	rm_c++;

	return make_pair(dir, make_pair(rm_r, rm_c));
}

bool comp_wall(const pair<char, pair<int, int> >& a,
		const pair<char, pair<int, int> >& b) {
	if (a.second.second != b.second.second) {
		return a.second.second > b.second.second;
	}
	if (a.second.first != b.second.first) {
		return a.second.first < b.second.first;
	}
	if (a.first == 'N') {
		return false;
	}
	else if (b.first == 'N') {
		return true;
	}
	return false;
}

int main() {
	ifstream fin("castle.in");
	ofstream fout("castle.out");

	fin >> cols >> rows;

	int tmp;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			fin >> tmp;
			room[i][j] = -1;
			for (int k = 0; k < 4; k++) {
				if (tmp & 1) {
					wall[i][j][k] = true;
				}
				else {
					wall[i][j][k] = false;
				}
				tmp >>= 1;
			}
		}
	}

	int largest = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (room[i][j] == -1) {
				room[i][j] = cur_room;
				room_sz[cur_room] = 1;
				dfs(i, j);
				largest = max(largest, room_sz[cur_room]);
				cur_room++;
			}
		}
	}

	int combined = 0;
	pair<char, pair<int, int> > optimal_wall;
	for (int i = 0; i < cur_room; i++) {
		for (set<int>::iterator it = adj_rooms[i].begin(); it != adj_rooms[i].end(); it++) {
			if (combined < room_sz[i] + room_sz[*it]) {
				combined = room_sz[i] + room_sz[*it];
				optimal_wall = find_optimal_wall(i, *it);
			}
			else if (combined == room_sz[i] + room_sz[*it]) {
				optimal_wall = max(optimal_wall, find_optimal_wall(i, *it), comp_wall);
			}
		}
	}

	fout << cur_room << endl;
	fout << largest << endl;
	fout << combined << endl;
	fout << optimal_wall.second.first << " " << optimal_wall.second.second << " " << optimal_wall.first << endl;

	return 0;
}
