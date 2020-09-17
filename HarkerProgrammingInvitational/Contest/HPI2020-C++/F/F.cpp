#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

typedef pair<int,int> pii;

int chr[12] = {1, 0, -1, 0, 1, 1, -1, -1, 2, 0, -2, 0};
int chc[12] = {0, 1, 0, -1, 1, -1, 1, -1, 0, 2, 0, -2};

int N;
int grid[40][40];
bool v[40][40];

struct Item {
	int r, c;
	int dist;

	Item(int a, int b, int d) {
		r = a;
		c = b;
		dist = d;
	}

	bool valid() {
		return 0 <= r && r < N && 0 <= c && c < N && grid[r][c] != 1 && v[r][c] == false;
	}
};

struct comp {
	inline const bool operator() (const Item& a, const Item& b) {
		return a.dist > b.dist;
	}
};

int bfs(int lvl, int sr, int sc, int er, int ec) {
	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
			v[i][j] = false;
		}
	}
	priority_queue<Item, vector<Item>, comp> pq;
	pq.push(Item(sr, sc, 0));
	v[0][0] = true;

	while (pq.size() > 0) {
		Item cur = pq.top();

		cout << cur.r << " " << cur.c << " " << cur.dist << endl;
		pq.pop();

		if (cur.r == er && cur.c == ec) {
			return cur.dist;
		}

		for (int i=0; i<lvl * 4; i++) {
			Item nxt(cur.r + chr[i], cur.c + chc[i], cur.dist + 1);
			if (!nxt.valid()) continue;
			v[nxt.r][nxt.c] = true;
			pq.push(nxt);
		}
	}

	return 1001001001;
}

bool used[4];
int dist[4][4][3];
int ans(int ct, int prev) {
	if (ct == 3) {
		return 0;
	}

	int ret = 1001001001;
	for (int i=0; i<4; i++) {
		if (!used[i]) {
			used[i] = true;
			ret = min(ret, dist[prev][i][ct] + ans(ct+1, i));
			used[i] = false;
		}
	}

	return ret;
}

int main() {
	cin >> N;

	vector<pii> comps;
	comps.push_back(pii(0, 0));
	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
			cin >> grid[i][j];
			v[i][j] = false;
			if (grid[i][j] == 2) {
				comps.push_back(pii(i, j));
			}
		}
	}

	for (int i=0; i<4; i++) {
		for (int j=0; j<4; j++) {
			for (int k=0; k<3; k++) {
				dist[i][j][k] = bfs(k, comps[i].first, comps[i].second, comps[j].first, comps[j].second);
				cout << dist[i][j][k] << " ";
			}
			cout << endl;
		}
		cout << endl << endl;
	}

	int best = ans(0, 0);

	cout << best << endl;

	return 0;
}
