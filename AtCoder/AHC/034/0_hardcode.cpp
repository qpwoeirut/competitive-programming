#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,tune=native")

using namespace std;

using pii = pair<int, int>;

const char DIRS[4] = {'R', 'D', 'L', 'U'};
const int RIGHT = 0;
const int DOWN = 1;
const int LEFT = 2;
const int UP = 3;
const int chr[4] = {0, 1, 0, -1};
const int chc[4] = {1, 0, -1, 0};

const int N = 20;
int A[N][N];

const int MOVE_COST = 100;

int path(const int base, vector<pii>& ops) {
    int to_fix = base;

    int soil = 0;
    int cost = 0;
    for (int i=0; i<2*N && to_fix > 0; ++i) {
        const int r = i < N ? i : 2*N - i - 1;
        if (i % N > 0) {
            cost += MOVE_COST + soil;
            ops.emplace_back(0, i < N ? DOWN : UP);
        }
        for (int j=0; j<N && to_fix > 0; ++j) {
            const int c = i % 2 == 0 ? j : N - j - 1;
            if (j > 0) {
                cost += MOVE_COST + soil;
                ops.emplace_back(0, i % 2 == 0 ? RIGHT : LEFT);
            }
            const int moved = A[r][c] >= 0 ? A[r][c] : -min(soil, -A[r][c]);
            if (moved != 0) {
                A[r][c] -= moved;
                soil += moved;

                to_fix -= abs(moved);
                cost += abs(moved);
                ops.emplace_back(moved, 0);
            }
        }
    }
    cerr << base << ' ' << cost << endl;
    return round(1e9 * base / cost);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int _N;
    cin >> _N;
    assert(N == _N);
    
    int base = 0;
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            cin >> A[i][j];
            base += abs(A[i][j]);
        }
    }

    vector<pii> ops;
    const int score = path(base, ops);
    cerr << "Score: " << score << endl;
    cout << showpos;
    for (const pii& p: ops) {
        if (p.first == 0) cout << DIRS[p.second] << '\n';
        else cout << p.first << '\n';
    }
}
