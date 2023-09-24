#include <bits/stdc++.h>

using namespace std;

#pragma GCC optimize("O3")

using pii=pair<int,int>;
#define fi first
#define se second

const int N = 50;
const int M = 100;
int G[N + 2][N + 2];
set<pii> pos[M + 1];

int ct[M + 1][M + 1];
int rank_of[M + 1];
vector<int> rnk[N];

void bfs_rank() {
    fill(rank_of, rank_of + M + 1, -1);
    for (int i = 0; i < N; ++i) rnk[i].clear();

    int q[M + 1];
    int q1 = 0;
    q[q1++] = 0;
    rank_of[0] = 0;
    rnk[0].push_back(0);

    for (int q0 = 0; q0 < q1; ++q0) {
        for (int i = 1; i <= M; ++i) {
            if (ct[i][q[q0]] > 0 && rank_of[i] == -1) {
                rank_of[i] = rank_of[q[q0]] + 1;
                rnk[rank_of[i]].push_back(i);
                q[q1++] = i;
            }
        }
    }
}

bitset<N + 2> visited[N + 2];
pii q[N * N];
bool check_connected(const int color, const int row, const int col) {
    if (pos[color].size() <= 1) return false;

    for (int r = 0; r <= N + 1; ++r) visited[r].reset();

    auto it = pos[color].begin();
    if (it->fi == row && it->se == col) ++it;

    int q1 = 0;
    q[q1++] = *it;
    visited[it->fi][it->se] = true;
    int visited_count = 1;
    for (int q0 = 0; q0 < q1; ++q0) {
        //cerr << "q0, q1: " << q0 << ' ' << q1 << endl;
        if (1 < q[q0].fi && q[q0].fi <= N && 1 <= q[q0].se && q[q0].se <= N && !visited[q[q0].fi - 1][q[q0].se] && G[q[q0].fi - 1][q[q0].se] == color) {
            visited[q[q0].fi - 1][q[q0].se] = true;
            q[q1++] = pii(q[q0].fi - 1, q[q0].se);
            ++visited_count;
        }
        if (1 <= q[q0].fi && q[q0].fi <= N && 1 < q[q0].se && q[q0].se <= N && !visited[q[q0].fi][q[q0].se - 1] && G[q[q0].fi][q[q0].se - 1] == color) {
            visited[q[q0].fi][q[q0].se - 1] = true;
            q[q1++] = pii(q[q0].fi, q[q0].se - 1);
            ++visited_count;
        }
        if (1 <= q[q0].fi && q[q0].fi <= N && 1 <= q[q0].se && q[q0].se < N && !visited[q[q0].fi][q[q0].se + 1] && G[q[q0].fi][q[q0].se + 1] == color) {
            visited[q[q0].fi][q[q0].se + 1] = true;
            q[q1++] = pii(q[q0].fi, q[q0].se + 1);
            ++visited_count;
        }
        if (1 <= q[q0].fi && q[q0].fi < N && 1 <= q[q0].se && q[q0].se <= N && !visited[q[q0].fi + 1][q[q0].se] && G[q[q0].fi + 1][q[q0].se] == color) {
            visited[q[q0].fi + 1][q[q0].se] = true;
            q[q1++] = pii(q[q0].fi + 1, q[q0].se);
            ++visited_count;
        }
    }

    //cerr << color << ' ' << row << ' ' << col << ' ' << visited_count << ' ' << pos[color].size() << endl;
    return visited_count + 1 == pos[color].size();
}

bool try_change_to(const int row, const int col, const int a, const int b, const int c, const int d) {
    //cerr << "row, col, a, b, c, d: " << row << ' ' << col << ' ' << a << ' ' << b << ' ' << c << ' ' << d << endl;
    const int color = G[row][col];

    const bool ab = ct[a][b] > 0, ac = ct[a][c] > 0, ad = ct[a][d] > 0;
    const bool col_b = ct[color][b] > 0, col_c = ct[color][c] > 0, col_d = ct[color][d] > 0;

    G[row][col] = a;

    --ct[color][a]; --ct[color][b]; --ct[color][c]; --ct[color][d];
    --ct[a][color]; --ct[b][color]; --ct[c][color]; --ct[d][color];

    ++ct[a][a]; ++ct[a][b]; ++ct[a][c]; ++ct[a][d];
    ++ct[a][a]; ++ct[b][a]; ++ct[c][a]; ++ct[d][a];
    if ((ct[a][b] > 0) == ab && (ct[a][c] > 0) == ac && (ct[a][d] > 0) == ad && (ct[color][b] > 0) == col_b && (ct[color][c] > 0) == col_c && (ct[color][d] > 0) == col_d) {
        if (check_connected(color, row, col)) {
            pos[color].erase(pii(row, col));
            pos[a].emplace(row, col);
            return true;
        }
    }
    ++ct[color][a]; ++ct[color][b]; ++ct[color][c]; ++ct[color][d];
    ++ct[a][color]; ++ct[b][color]; ++ct[c][color]; ++ct[d][color];

    --ct[a][a]; --ct[a][b]; --ct[a][c]; --ct[a][d];
    --ct[a][a]; --ct[b][a]; --ct[c][a]; --ct[d][a];

    G[row][col] = color;

    return false;
}

bool try_change(const int row, const int col, const bool allow_size_check) {
    //cerr << "row, col: " << row << ' ' << col << endl;
    const int a = G[row - 1][col], b = G[row][col - 1], c = G[row][col + 1], d = G[row + 1][col];
    const int color = G[row][col];
    if (a != color && b != color && c != color && d != color) return false;
    
    if ((rank_of[a] < rank_of[color] || (allow_size_check && rank_of[a] == rank_of[color] && pos[a].size() < pos[color].size())) && try_change_to(row, col, a, b, c, d)) return true;
    if ((rank_of[b] < rank_of[color] || (allow_size_check && rank_of[b] == rank_of[color] && pos[b].size() < pos[color].size())) && try_change_to(row, col, b, a, c, d)) return true;
    if ((rank_of[c] < rank_of[color] || (allow_size_check && rank_of[c] == rank_of[color] && pos[c].size() < pos[color].size())) && try_change_to(row, col, c, a, b, d)) return true;
    if ((rank_of[d] < rank_of[color] || (allow_size_check && rank_of[d] == rank_of[color] && pos[d].size() < pos[color].size())) && try_change_to(row, col, d, a, b, c)) return true;
    return false;
}

mt19937 rng(8);
bool try_random_change(const int row, const int col, const bool allow_zero) {
    int arr[4] = { G[row - 1][col], G[row][col - 1], G[row][col + 1], G[row + 1][col] };
    shuffle(arr, arr + 4, rng);
    const int a = arr[0], b = arr[1], c = arr[2], d = arr[3];

    const int color = G[row][col];
    if (a != color && b != color && c != color && d != color) return false;
    
    if ((a != 0 || allow_zero) && a != color && try_change_to(row, col, a, b, c, d)) return true;
    if ((b != 0 || allow_zero) && b != color && try_change_to(row, col, b, a, c, d)) return true;
    if ((c != 0 || allow_zero) && c != color && try_change_to(row, col, c, a, b, d)) return true;
    if ((d != 0 || allow_zero) && d != color && try_change_to(row, col, d, a, b, c)) return true;
    return false;
}

int current_score() {
    int s = 0;
    for (int r = 1; r <= N; ++r) {
        for (int c = 1; c <= N; ++c) {
            s += G[r][c] == 0;
        }
    }
    return s;
}

const int COUNTDOWN = 3;

int best[N + 2][N + 2];
const auto END_TIME = chrono::high_resolution_clock::now() + 1950ms;
void solve() {
    for (int r = 0; r <= N; ++r) {
        for (int c = 0; c <= N; ++c) {
            ++ct[G[r][c]][G[r][c + 1]];
            ++ct[G[r][c]][G[r + 1][c]];
            ++ct[G[r][c + 1]][G[r][c]];
            ++ct[G[r + 1][c]][G[r][c]];

            ++ct[G[r][c]][G[r][c]];

            pos[G[r][c]].emplace(r, c);
        }
    }

    bfs_rank();

    int best_score = 0;
    int countdown = COUNTDOWN;
    int rounds = 0;
    while (chrono::high_resolution_clock::now() < END_TIME) {
        for (int rk = 1; rk < N; ++rk) {
            for (const int color: rnk[rk]) {
                bool color_change = true;
                while (color_change) {
                    color_change = false;
                    for (const pii& p: pos[color]) {
                        if (try_change(p.fi, p.se, rounds < 3)) {
                            color_change = true;
                            break;
                        }
                    }
                }
            }
        }

        const int score = current_score();
        if (best_score < score) {
            best_score = score;
            for (int r = 1; r <= N; ++r) {
                for (int c = 1; c <= N; ++c) {
                    best[r][c] = G[r][c];
                }
            }
            countdown = COUNTDOWN;
            rounds = 0;
        } else --countdown;

        if (countdown <= 0) {
            ++rounds;
            countdown = COUNTDOWN;

            for (int n = 0; n < rounds; ++n) {
                for (int r = 1; r <= N; ++r) {
                    for (int c = 1; c <= N; ++c) {
                        try_random_change(r, c, rounds >= 6);
                    }
                }
            }
        }

        //for (int r = 1; r <= N; ++r) { for (int c = 1; c <= N; ++c) { if (c > 1) { cout << ' '; } cout << G[r][c]; } cout << '\n'; }
    }
    for (int r = 1; r <= N; ++r) {
        for (int c = 1; c <= N; ++c) {
            if (c > 1) cout << ' ';
            cout << best[r][c];
        }
        cout << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;
    assert(n == N);
    assert(m == M);

    for (int r = 0; r <= N + 1; ++r) {
        for (int c = 0; c <= N + 1; ++c) {
            G[r][c] = 0;
        }
    }
    for (int r = 1; r <= N; ++r) {
        for (int c = 1; c <= N; ++c) {
            cin >> G[r][c];
        }
    }

    solve();
}
