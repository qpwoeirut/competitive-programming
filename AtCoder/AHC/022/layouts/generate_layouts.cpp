#include <bits/stdc++.h>
#include <filesystem>

#pragma GCC optimize("O3,unroll-loops")

using namespace std;

#include "qpwoeirut/debug.h"

using ll=long long;
using pii=pair<int,int>;

const int SIZE = 6;
const int N = SIZE + 1 + SIZE;
const int ITER = 100;

int square(int x) { return x * x; }

int G[N][N];
bitset<N> picked[N];
void fill_grid(const vector<pii>& cells, int vals, const int iterations=10000) {
    for (int r=0; r<N; ++r) {
        for (int c=0; c<N; ++c) {
            G[r][c] = picked[r][c] ? 1000 * (vals & 1) : 500;
            vals >>= picked[r][c];
        }
    }
    for (int i=0; i<iterations; ++i) {
        bool changed = false;
        for (int r=0; r<N; ++r) {
            for (int c=0; c<N; ++c) {
                if (!picked[r][c]) {
                    const int new_val = (G[(r+N-1)%N][c] + G[r][(c+N-1)%N] + G[(r+1)%N][c] + G[r][(c+1)%N] + 2) / 4;
                    if (G[r][c] != new_val) {
                        G[r][c] = new_val;
                        changed = true;
                    }
                }
            }
        }
        if (!changed) {
            //debug(i, iterations);
            break;
        }
    }
}

ll cost(const vector<pii>& cells) {
    ll ret = 0;
    for (int i=0; i < (1 << cells.size()); ++i) {
        fill_grid(cells, i);
        for (int r=0; r<N; ++r) {
            for (int c=0; c<N; ++c) {
                ret += square(G[r][c] - G[(r+1)%N][c]) + square(G[r][c] - G[r][(c+1)%N]);
            }
        }
    }
    int mxd = 0;
    for (const pii& p: cells) {
        ret += (1 << cells.size()) * (100 * (10 + abs(SIZE - p.first) + abs(SIZE - p.second)));
        mxd = max(mxd, max(abs(SIZE - p.first), abs(SIZE - p.second)));
    }
    return ret + mxd;
}

mt19937_64 rng(8);
const int chr[8] = { 0,  1,  0, -1, -1,  1,  1, -1 };
const int chc[8] = { 1,  0, -1,  0,  1,  1, -1, -1 };
void pick_random_change(const vector<pii>& cells, int& idx, int& change) {
    do {
        idx = rng() % cells.size();
        change = rng() % 8;
    } while (picked[(cells[idx].first + N + chr[change]) % N][(cells[idx].second + N + chc[change]) % N]);

    picked[cells[idx].first][cells[idx].second] = false;
    picked[(cells[idx].first + N + chr[change]) % N][(cells[idx].second + N + chc[change]) % N] = true;
}

void generate_layouts(const int n, const int iterations, const int trials, vector<pii>& best_cells) {
    ll best_cost = 1e18;
    for (int t=0; t<trials; ++t) {
        for (int r=0; r<N; ++r) picked[r].reset();
        vector<pii> cells;
        while (cells.size() < n) {
            const int r = rng() % N, c = rng() % N;
            if (!picked[r][c]) {
                picked[r][c] = true;
                cells.emplace_back(r, c);
            }
        }

        ll old_cost = cost(cells);
        const ll mx_rand = (1 << n) * 2000;
        for (int i=iterations-1; i>=0; --i) {
            int idx, change; pick_random_change(cells, idx, change);

            const ll new_cost = cost(cells);
            if (old_cost + (rng() % (1LL + (mx_rand * i / iterations))) <= new_cost) {  // revert change
                picked[cells[idx].first][cells[idx].second] = true;
                picked[(cells[idx].first + N + chr[change]) % N][(cells[idx].second + N + chc[change]) % N] = false;
            } else {  // confirm change
                old_cost = new_cost;
                cells[idx].first = (cells[idx].first + N + chr[change]) % N;
                cells[idx].second = (cells[idx].second + N + chc[change]) % N;

                int mnr = cells[0].first, mxr = cells[0].first;
                int mnc = cells[0].second, mxc = cells[0].second;
                for (const pii& p: cells) {
                    mnr = min(mnr, p.first);
                    mxr = max(mxr, p.first);
                    mnc = min(mnc, p.second);
                    mxc = max(mxc, p.second);
                    picked[p.first][p.second] = false;
                }

                const int shr = (mnr + mxr) / 2 - SIZE;
                const int shc = (mnc + mxc) / 2 - SIZE;
                for (pii& p: cells) {
                    p.first -= shr;
                    p.second -= shc;
                    picked[p.first][p.second] = true;
                }
            }

            if (best_cost > new_cost) {
                best_cost = new_cost;
                best_cells = cells;
            }

            if (i % ITER == 0) {
                cerr << i << " iterations remaining. cost = " << cost(cells) << ". best_cost = " << best_cost << '\n';
                //for (int r=0; r<N; ++r) {
                //    for (int c=0; c<N; ++c) cerr << measure[r][c] << ' ';
                //    cerr << '\n';
                //}
            }
        }
    }
}

int main() {
    vector<pii> best_cells;
    for (int n=1; n<=9; ++n) {
        generate_layouts(n, ITER * n, 10*n, best_cells);

        const string filename = "layout-" + to_string(n) + "-" + to_string(SIZE) + ".txt";
        ofstream fout("layouts/" + filename);
        if (!fout.is_open()) {
            assert(filesystem::create_directory("layouts"));
            fout.open("layouts/" + filename);
        }
        assert(fout.is_open());
        
        for (int r=0; r<N; ++r) picked[r].reset();
        for (const pii& p: best_cells) picked[p.first][p.second] = true;

        for (int r=0; r<N; ++r) {
            for (int c=0; c<N; ++c) fout << picked[r][c];
            fout << '\n';
        }
        fout << '\n' << cost(best_cells) << '\n';
        fout.close();
    }
}
