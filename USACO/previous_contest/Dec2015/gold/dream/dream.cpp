/*
 * dream.cpp
 *
 *  Created on: Feb 28, 2019
 *      Author: Stanley
 */

#include <fstream>
#include <queue>
#include <iostream>
using namespace std;

struct Item {
	int y, x, dir;
	int dist;
	bool smell;
};

int sz_y, sz_x;
bool visited[1000][1000][4];
int grid[1000][1000];
bool valid(const int& x, const int& y, const bool& smell, const int& dir) {
	if (grid[x][y] == 0 || (grid[x][y] == 3 && smell == false) ||
		x < 0 || x >= sz_x || y < 0 || y >= sz_y) {
			return false;
	}
	return true;
}

int main() {
	ifstream fin("dream.in");
	ofstream fout("dream.out");

	Item start;
	start.y = 0;
	start.x = 0;
	start.dir = -1;
	start.dist = 0;
	start.smell = false;

	queue<Item> q;
	q.push(start);
	visited[0][0][0] = true;
	visited[0][0][1] = true;
	visited[0][0][2] = true;
	visited[0][0][3] = true;
	fin >> sz_y >> sz_x;

	for (int i=0; i<sz_y; i++) {
		for (int j=0; j<sz_x; j++) {
			fin >> grid[i][j];
		}
	}

	int ch_x[4] = {1,  0, -1,  0};
	int ch_y[4] = {0,  1,  0, -1};

	Item cur, next;
	while (q.size() > 0) {
		cur = q.front();
		cout << "cur x,y,dir,dist,smell: " << cur.x << " " << cur.y << " " << cur.dir << " " << cur.dist << " " << cur.smell << endl;
		q.pop();

		if (cur.y == sz_x-1 && cur.x == sz_y-1) {
			fout << cur.dist << endl;
			cout << cur.dist << endl;
			return 0;
		}

		next.dist = cur.dist + 1;
		if (grid[cur.y][cur.x] == 4 && cur.dir != -1 && valid(cur.y + ch_y[cur.dir], cur.x + ch_x[cur.dir], cur.smell, cur.dir)) {
			next.x = cur.x + ch_x[cur.dir];
			next.y = cur.y + ch_y[cur.dir];
			next.dir = cur.dir;
			next.smell = (grid[next.y][next.x] == 2);
			q.push(next);
			visited[next.y][next.x][next.dir] = true;
			continue;
		}

		for (int i=0; i<4; i++) {
			next.x = cur.x + ch_x[i];
			next.y = cur.y + ch_y[i];
			next.dir = i;

			if (valid(next.y, next.x, cur.smell, next.dir) && visited[next.y][next.x][next.dir] == false) {
				next.smell = (grid[next.y][next.x] == 2 ? true : (grid[next.y][next.x] == 4 ? false : cur.smell));
				q.push(next);
				if (grid[next.y][next.x] != 4) {
					for (int j=0; j<4; j++) {
						visited[next.y][next.x][j] = true;
					}
				}
				else {
					visited[next.y][next.x][i] = true;
				}
			}
		}
	}

	fout << -1 << endl;
	cout << -1 << endl;

	return 0;
}
