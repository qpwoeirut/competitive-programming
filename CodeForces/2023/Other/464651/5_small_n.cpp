#include <bits/stdc++.h>

#pragma GCC optimize("O3")
#pragma GCC target("avx2")

using namespace std;

using ll=long long;
using pii=pair<int,int>;
using interactor=int (*)(int, const vector<int>&, int);

#ifdef LOCAL
#include "qpwoeirut/debug.h"
#else
#define debug
#define debug1
#define debug2
#define debug3
#endif

namespace Solution {
    const int MN = 30;
    const int TIME = 100;
    const int MX_TIME = 80;
    consteval array<int, TIME + 2> gen_p15() {
        array<int, TIME + 2> arr;
        for (int i=0; i<TIME+2; ++i) {
            arr[i] = i * (int)(sqrt(i) + 1e-6);
        }
        return arr;
    }
    constexpr array<int, TIME + 2> p15 = gen_p15();

    const int TELEPORT = 40;  // assume we never block and then don't block teleportation
    const int BOB_OPTIONS = 5;
    const int OPTS = MN;

    int N, M;
    vector<int> adj[MN];
    int max_pen[TIME];  // for pruning
    int dist[MN][MN];
    int dist_penalty[MN][MN];

    array<int, OPTS> bob_adj[MN][MN];
    array<int, OPTS> bob_tp[MN][MN];

    int cache[MX_TIME][MN][MN];  // [time][alice][bob] = score numerator

    int p4(int x) { return x > 31 ? max_pen[0] : x * x * x * x; }
    int p7(int x) { return x >  7 ? max_pen[0] : x * x * x * x * x * x * x; }
    
    int scores[MN];

    int expectimax(int a, int b, int t) {
        if (t == MX_TIME) return 0;
        if (cache[t][a][b] != -1) return cache[t][a][b];

        for (int target = 0; target < N; ++target) {
            const int move_penalty = p15[100 - t] * dist_penalty[a][target];
            if (move_penalty >= max_pen[t]) continue;

            for (int u=0; u<N; ++u) {
                scores[u] = expectimax(target, u, t + 1);
            }

            for (int mask=0; mask<(1 << N); ++mask) {
                const int block_penalty = (100 - t) * p4(__builtin_popcount(mask));
                if (move_penalty + block_penalty >= max_pen[t]) continue;

                ll adj_escore = 0;  // assume bob moves to adjacent node
                int adj_ct = 0;
                for (int i=0; i<OPTS && adj_ct<BOB_OPTIONS; ++i) {
                    if (bob_adj[a][b][i] == -1) break;
                    if ((mask & (1 << bob_adj[a][b][i])) > 0 && scores[bob_adj[a][b][i]] != -1) {
                        adj_escore += scores[bob_adj[a][b][i]];
                        ++adj_ct;
                    }
                }
                adj_escore = (adj_ct == 0) ? scores[b] : adj_escore / adj_ct;

                ll tp_escore = 0;  // assume bob teleports
                int tp_ct = 0;
                for (int i=0; i<OPTS && tp_ct<BOB_OPTIONS; ++i) {
                    if (bob_tp[a][b][i] == -1) break;
                    if ((mask & (1 << bob_tp[a][b][i])) > 0 && scores[bob_tp[a][b][i]] != -1) {
                        tp_escore += scores[bob_tp[a][b][i]];
                        ++tp_ct;
                    }
                }
                tp_escore = (tp_ct == 0) ? scores[b] : tp_escore / tp_ct;

                const int escore = ((adj_escore * (100 - TELEPORT) + tp_escore * TELEPORT) / 100) - move_penalty - block_penalty;
                cache[t][a][b] = max(cache[t][a][b], escore);

                if (mask == 0) {
                    const int prevent_escore = adj_escore - move_penalty - (100 - t) * p4(adj[a].size() + 1);
                    cache[t][a][b] = max(cache[t][a][b], prevent_escore);
                }
            }
        }

        return cache[t][a][b];
    }

    int find_move(int a, int b, int t, int& move_target, __int128_t& block_mask, int& move_k) {
        int score = -1;
        move_target = 0, block_mask = 0, move_k = 0;
        for (int target = 0; target < N; ++target) {
            const int move_penalty = p15[100 - t] * dist_penalty[a][target];
            if (move_penalty >= max_pen[t]) continue;

            for (int u=0; u<N; ++u) {
                scores[u] = expectimax(target, u, t + 1);
            }

            for (int mask=0; mask<(1 << N); ++mask) {
                const int block_penalty = (100 - t) * p4(__builtin_popcount(mask));
                if (move_penalty + block_penalty >= max_pen[t]) continue;

                ll adj_escore = 0;  // assume bob moves to adjacent node
                int adj_ct = 0;
                for (int i=0; i<OPTS && adj_ct<BOB_OPTIONS; ++i) {
                    if (bob_adj[a][b][i] == -1) break;
                    if ((mask & (1 << bob_adj[a][b][i])) > 0 && scores[bob_adj[a][b][i]] != -1) {
                        adj_escore += scores[bob_adj[a][b][i]];
                        ++adj_ct;
                    }
                }
                adj_escore = (adj_ct == 0) ? scores[b] : adj_escore / adj_ct;

                ll tp_escore = 0;  // assume bob teleports
                int tp_ct = 0;
                for (int i=0; i<OPTS && tp_ct<BOB_OPTIONS; ++i) {
                    if (bob_tp[a][b][i] == -1) break;
                    if ((mask & (1 << bob_tp[a][b][i])) > 0 && scores[bob_tp[a][b][i]] != -1) {
                        tp_escore += scores[bob_tp[a][b][i]];
                        ++tp_ct;
                    }
                }
                tp_escore = (tp_ct == 0) ? scores[b] : tp_escore / tp_ct;

                const int escore = ((adj_escore * (100 - TELEPORT) + tp_escore * TELEPORT) / 100) - move_penalty - block_penalty;
                if (cache[t][a][b] < escore) {
                    cache[t][a][b] = escore;
                    move_target = target;
                    block_mask = mask;
                    move_k = __builtin_popcount(mask);
                }

                if (mask == 0) {
                    const int prevent_escore = adj_escore - move_penalty - (100 - t) * p4(adj[a].size() + 1);
                    if (cache[t][a][b] < prevent_escore) {
                        cache[t][a][b] = prevent_escore;
                        move_target = target;
                        block_mask = mask;
                        move_k = N+1;
                    }
                }
            }
            //debug(a, b, t, target, escore, prevent_escore, bob_adj[a][b], bob_tp[a][b]);
        }
        return score;
    }

    int alice, bob;
    void solve(int _n, int _m, const vector<pii>& edges, interactor interact) {
        N = _n;
        M = _m;
        if (N > MN) {
            for (int t=0; t<TIME; ++t) {
                bob = interact(0, vector<int>(), alice);
                if (alice == bob) return;
            }
            return;
        }

        alice = 0;
        bob = N - 1;

        for (int t=0; t<TIME; ++t) {
            max_pen[t] = N * N * p15[100 - t];  // use N^2 instead of N^1.5 since the sqrts are floored
        }
        for (int a=0; a<N; ++a) {
            for (int b=0; b<N; ++b) {
                dist[a][b] = max_pen[0];
                for (int t=0; t<MX_TIME; ++t) {
                    cache[t][a][b] = a == b ? N*N*N * p15[101 - t] : -1;
                    // use 101 - t since this is the end of the previous turn
                }
            }
            adj[a].clear();
            dist[a][a] = 0;
        }
        for (const pii& edge: edges) {
            adj[edge.first].push_back(edge.second);
            adj[edge.second].push_back(edge.first);
            dist[edge.first][edge.second] = dist[edge.second][edge.first] = 1;
        }

        for (int k=0; k<N; ++k) {
            for (int i=0; i<N; ++i) {
                for (int j=0; j<N; ++j) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
        for (int i=0; i<N; ++i) {
            for (int j=0; j<N; ++j) {
                dist_penalty[i][j] = p7(max(0, dist[i][j] - 1));
            }
        }

        vector<pii> pos;
        for (int a=0; a<N; ++a) {
            for (int b=0; b<N; ++b) {
                pos.clear();
                pos.emplace_back(dist[a][b], b);
                for (int u: adj[b]) {
                    pos.emplace_back(dist[a][u], u);
                }
                sort(pos.rbegin(), pos.rend());
                while (pos.size() > OPTS) pos.pop_back();

                bob_adj[a][b].fill(-1);
                for (int i=0; i<pos.size(); ++i) bob_adj[a][b][i] = pos[i].second;


                pos.clear();
                for (int u=0; u<N; ++u) {
                    pos.emplace_back(dist[a][u], u);
                }
                sort(pos.rbegin(), pos.rend());
                while (pos.size() > OPTS) pos.pop_back();

                bob_tp[a][b].fill(-1);
                for (int i=0; i<pos.size(); ++i) bob_tp[a][b][i] = pos[i].second;
            }
        }

        int target, k;
        __int128_t block_mask;
        for (int t=0; t<MX_TIME; ++t) {
            //debug(alice, bob, t);
            const int escore = find_move(alice, bob, t, target, block_mask, k);
            vector<int> blocks;
            for (int i=0; i<N; ++i) {
                if ((block_mask >> i) & 1) blocks.push_back(i);
            }

            bob = interact(k, blocks, target);
            alice = target;

            if (alice == bob) return;
        }
        for (int t=MX_TIME; t<TIME; ++t) {
            bob = interact(0, vector<int>(), alice);
            alice = target;

            if (alice == bob) return;
        }
    }
};

int interact(int k, const vector<int>& blocks, int move) {
    cout << k << '\n';
    if (!blocks.empty()) {
        assert(k == blocks.size());
        for (int i=0; i<blocks.size(); ++i) {
            if (i) cout << ' ';
            cout << blocks[i] + 1;
        }
        cout << '\n';
    }
    cout << move + 1 << '\n';
    cout.flush();

    int bob;
    cin >> bob;
    return bob-1;
}

#ifndef USING_TESTER
int main() {
    cin.tie(0)->sync_with_stdio(0);

    int N, M;
    cin >> N >> M;

    vector<pii> edges(M);
    for (int i=0; i<M; ++i) {
        cin >> edges[i].first >> edges[i].second; --edges[i].first; --edges[i].second;
    }

    Solution::solve(N, M, edges, interact);
}
#endif

/*
TESTS = 1000. max_n = 10. sparse = false
scores    mean, stddev, stderr, min, q1, med, q3, max: 14.094000, 5.167510, 0.163411, -7.000000, 14.000000, 16.000000, 17.000000, 20.000000
nn scores mean, stddev, stderr, min, q1, med, q3, max: 14.108000, 5.122923, 0.162001, 0.000000, 14.000000, 16.000000, 17.000000, 20.000000
times     mean, stddev, stderr, min, q1, med, q3, max: 16.540000, 25.293643, 0.799855, 1.000000, 3.000000, 6.000000, 17.000000, 100.000000
nn times  mean, stddev, stderr, min, q1, med, q3, max: 10.135000, 13.714692, 0.433697, 0.000000, 2.000000, 5.000000, 12.000000, 81.000000
penalties mean, stddev, stderr, min, q1, med, q3, max: 577.994000, 1306.853163, 41.326326, 0.000000, 0.000000, 0.000000, 720.000000, 14064.000000

TESTS = 1000. max_n = 10. sparse = true
scores    mean, stddev, stderr, min, q1, med, q3, max: 13.026000, 5.927168, 0.187434, -11.000000, 11.000000, 16.000000, 17.000000, 20.000000
nn scores mean, stddev, stderr, min, q1, med, q3, max: 13.086000, 5.758003, 0.182084, 0.000000, 11.000000, 16.000000, 17.000000, 20.000000
times     mean, stddev, stderr, min, q1, med, q3, max: 18.943000, 27.957821, 0.884104, 1.000000, 3.000000, 6.000000, 20.000000, 100.000000
nn times  mean, stddev, stderr, min, q1, med, q3, max: 9.815000, 13.673945, 0.432408, 0.000000, 2.000000, 4.000000, 11.000000, 81.000000
penalties mean, stddev, stderr, min, q1, med, q3, max: 1238.992000, 2325.063868, 73.524975, 0.000000, 0.000000, 100.000000, 1891.000000, 21801.000000
*/
