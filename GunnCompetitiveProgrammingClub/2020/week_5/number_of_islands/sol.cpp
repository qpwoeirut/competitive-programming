#include <bits/stdc++.h>

using namespace std;

const int MN = 1001;
const int chr[4] = {1, 0, -1, 0};
const int chc[4] = {0, 1, 0, -1};

int N, M;
string grid[MN];

bool visited[MN][MN];

void dfs(int r, int c) {
    if (r < 0 || r >= N || c < 0 || c >= M || visited[r][c] || grid[r][c] == 'W') return;
    visited[r][c] = true;
    for (int i=0; i<4; ++i) {
        dfs(r + chr[i], c + chc[i]);
    }
}

int main() {
    //cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M;
    for (int i=0; i<N; ++i) {
        cin >> grid[i];
    }

    int islands = 0;
    for (int r=0; r<N; ++r) {
        for (int c=0; c<M; ++c) {
            if (!visited[r][c] && grid[r][c] == 'L') {
                dfs(r, c);
                ++islands;
            }
        }
    }

    cout << islands << endl;
}

