#include <iostream>
#include <algorithm>
#include <deque>

using namespace std;

int chr[8] = {1, 0, -1, 0, 1, 1, -1, -1};
int chc[8] = {0, 1, 0, -1, -1, 1, 1, -1};

int N, M;

struct Item {
	int r, c;
	int dist;

	Item(int _r, int _c, int d) {
		r = _r;
		c = _c;
		dist = d;
	}

	bool valid() {
		return 0 <= r && r < N && 0 <= c && c < M;
	}
};

int main() {
	cin >> N >> M;

	char grid[50][50];
	bool v[50][50];
	for (int i=0; i<N; i++) {
		for (int j=0; j<M; j++) {
			cin >> grid[i][j];
			v[i][j] = false;
		}
	}

	deque<Item> q;
	for (int i=0; i<N; i++) {
		if (grid[i][0] == '.') {
			q.push_front(Item(i, 0, 0));
			v[i][0] = true;
		}
		if (grid[i][M-1] == '.') {
			q.push_front(Item(i, M-1, 0));
			v[i][M-1] = true;
		}
	}
	for (int i=0; i<M; i++) {
		if (grid[0][i] == '.') {
			q.push_front(Item(0, i, 0));
			v[0][i] = true;
		}
		if (grid[N-1][i] == '.') {
			q.push_front(Item(N-1, i, 0));
			v[N-1][i] = true;
		}
	}
	if (q.empty()) {
		q.push_front(Item(0, 0, 1));
		v[0][0] = true;
	}

	int ans = 0;
	while (q.size() > 0) {
		Item cur = q.front();
		q.pop_front();

//		cout << cur.r << " " << cur.c << " " << cur.dist << endl;
		ans = max(ans, cur.dist);

		for (int i=0; i<8; i++) {
			Item nxt(cur.r + chr[i], cur.c + chc[i], cur.dist);
			if (!nxt.valid() || v[nxt.r][nxt.c]) continue;
			v[nxt.r][nxt.c] = true;

			if (grid[nxt.r][nxt.c] == '*' && grid[cur.r][cur.c] == '.') {
				nxt.dist++;
				q.push_back(nxt);
			}
			else {
				q.push_front(nxt);
			}
		}
	}

	cout << ans << endl;

	return 0;
}
