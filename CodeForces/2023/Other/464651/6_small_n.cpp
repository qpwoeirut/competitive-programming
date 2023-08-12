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
    const int MN = 10;
    const int TIME = 100;
    const ll INIT = 1e12;

    const int MX_TIME = 100;
    consteval array<int, TIME + 2> gen_p15() {
        array<int, TIME + 2> arr;
        for (int i=0; i<TIME+2; ++i) {
            arr[i] = i * (int)(sqrt(i) + 1e-6);
        }
        return arr;
    }
    constexpr const array<int, TIME + 2> p15 = gen_p15();

    const int TELEPORT = 40;  // assume we never block and then don't block teleportation
    const int BOB_OPTIONS = 5;
    const int OPTS = MN;

    ll N, M;
    vector<int> adj[MN];
    ll dist[MN][MN];
    ll dist_penalty[MN][MN];

    array<int, OPTS> bob_adj[MN][MN];
    array<int, OPTS> bob_tp[MN][MN];

    ll cache[MX_TIME][MN][MN];  // [time][alice][bob] = score numerator

    ll p4(int x) { return x > 31 ? INIT : x * x * x * x; }
    ll p7(int x) { return x >  7 ? INIT : x * x * x * x * x * x * x; }

    ll expectimax(int a, int b, int t) {
        if (t == MX_TIME) return 0;
        if (cache[t][a][b] != -1) return cache[t][a][b];

        const ll MX_SCORE = N * N * N * p15[100 - t];

        ll score = 0;
        ll scores[MN];
        for (int target = 0; target < N; ++target) {
            const ll move_penalty = p15[100 - t] * dist_penalty[a][target] * p15[N];
            if (move_penalty >= MX_SCORE) continue;

            for (int u=0; u<N; ++u) {
                scores[u] = expectimax(target, u, t + 1);
            }

            for (int mask=0; mask<(1 << N); ++mask) {
                const ll block_penalty = (100 - t) * p4(__builtin_popcount(mask)) * p15[N];
                if (move_penalty + block_penalty >= MX_SCORE) continue;

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

                const ll escore = ((adj_escore * (100 - TELEPORT) + tp_escore * TELEPORT) / 100) - move_penalty - block_penalty;
                score = max(score, escore);

                if (mask == 0) {
                    const ll prevent_escore = adj_escore - move_penalty - (100 - t) * p4(adj[a].size() + 1) * p15[N];
                    score = max(score, prevent_escore);
                }
            }
        }
        return cache[t][a][b] = score;
    }

    ll find_move(int a, int b, int t, int& move_target, __int128_t& block_mask, int& move_k) {
        const ll MX_SCORE = N * N * N * p15[100 - t];

        ll score = -1;
        ll scores[MN];
        move_target = 0, block_mask = 0, move_k = 0;
        for (int target = 0; target < N; ++target) {
            const ll move_penalty = p15[100 - t] * dist_penalty[a][target] * p15[N];
            if (move_penalty >= MX_SCORE) continue;

            for (int u=0; u<N; ++u) {
                scores[u] = expectimax(target, u, t + 1);
            }

            for (int mask=0; mask<(1 << N); ++mask) {
                const ll block_penalty = (100 - t) * p4(__builtin_popcount(mask)) * p15[N];
                if (move_penalty + block_penalty >= MX_SCORE) continue;

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

                const ll escore = ((adj_escore * (100 - TELEPORT) + tp_escore * TELEPORT) / 100) - move_penalty - block_penalty;
                if (score < escore) {
                    score = escore;
                    move_target = target;
                    block_mask = mask;
                    move_k = __builtin_popcount(mask);
                }

                if (mask == 0) {
                    const ll prevent_escore = adj_escore - move_penalty - (100 - t) * p4(adj[a].size() + 1) * p15[N];
                    if (score < prevent_escore) {
                        score = prevent_escore;
                        move_target = target;
                        block_mask = mask;
                        move_k = N+1;
                    }
                }
            }
            //debug(a, b, t, target, escore, prevent_escore, bob_adj[a][b], bob_tp[a][b]);
        }
        return cache[t][a][b] = score;
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

        for (int a=0; a<N; ++a) {
            for (int b=0; b<N; ++b) {
                dist[a][b] = INIT;
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
                dist_penalty[i][j] = p7(max(0LL, dist[i][j] - 1));
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
            const ll escore = find_move(alice, bob, t, target, block_mask, k);
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
TESTS = 1000. n = [2,10]. sparse = false
scores    mean, stddev, stderr, min, q1, med, q3, max: 13.759000, 5.542645, 0.175274, -1.000000, 12.000000, 16.000000, 17.000000, 20.000000
nn scores mean, stddev, stderr, min, q1, med, q3, max: 13.761000, 5.537498, 0.175111, 0.000000, 12.000000, 16.000000, 17.000000, 20.000000
times     mean, stddev, stderr, min, q1, med, q3, max: 19.408000, 28.746053, 0.909030, 1.000000, 3.000000, 7.000000, 20.000000, 100.000000
nn times  mean, stddev, stderr, min, q1, med, q3, max: 10.036000, 13.277903, 0.419884, 0.000000, 2.000000, 5.000000, 12.000000, 82.000000
penalties mean, stddev, stderr, min, q1, med, q3, max: 148176.897000, 4669420.736508, 147660.048810, 0.000000, 0.000000, 0.000000, 185.000000, 147734375.000000
TESTS = 1000. n = [2,10]. sparse = true
scores    mean, stddev, stderr, min, q1, med, q3, max: -2093.313000, 22753.001132, 719.513072, -392133.000000, 12.000000, 16.000000, 17.000000, 20.000000
nn scores mean, stddev, stderr, min, q1, med, q3, max: 13.610000, 5.914550, 0.187034, 0.000000, 12.000000, 16.000000, 17.000000, 20.000000
times     mean, stddev, stderr, min, q1, med, q3, max: 18.744000, 28.483056, 0.900713, 1.000000, 3.000000, 5.000000, 20.000000, 100.000000
nn times  mean, stddev, stderr, min, q1, med, q3, max: 9.510000, 13.856042, 0.438167, 0.000000, 2.000000, 4.000000, 11.000000, 83.000000
penalties mean, stddev, stderr, min, q1, med, q3, max: 6996522.070000, 65015319.643113, 2055964.928761, 0.000000, 0.000000, 0.000000, 1816.000000, 1557345413.000000

OLD:
TESTS = 1000. n = [2,10]. sparse = false
scores    mean, stddev, stderr, min, q1, med, q3, max: 14.128000, 5.178187, 0.163749, -1.000000, 14.000000, 16.000000, 17.000000, 20.000000
nn scores mean, stddev, stderr, min, q1, med, q3, max: 14.129000, 5.175361, 0.163659, 0.000000, 14.000000, 16.000000, 17.000000, 20.000000
times     mean, stddev, stderr, min, q1, med, q3, max: 17.362000, 26.467356, 0.836971, 1.000000, 3.000000, 6.000000, 17.000000, 100.000000
nn times  mean, stddev, stderr, min, q1, med, q3, max: 9.888000, 12.932573, 0.408964, 0.000000, 2.000000, 5.000000, 12.000000, 75.000000
penalties mean, stddev, stderr, min, q1, med, q3, max: 461.705000, 817.570545, 25.853851, 0.000000, 0.000000, 0.000000, 368.000000, 3430.000000
TESTS = 1000. n = [2,10]. sparse = true
scores    mean, stddev, stderr, min, q1, med, q3, max: -1746.843000, 22451.958908, 709.993281, -392131.000000, 11.000000, 16.000000, 17.000000, 20.000000
nn scores mean, stddev, stderr, min, q1, med, q3, max: 13.389000, 6.159844, 0.194791, 0.000000, 11.000000, 16.000000, 17.000000, 20.000000
times     mean, stddev, stderr, min, q1, med, q3, max: 19.874000, 29.565624, 0.934947, 1.000000, 2.000000, 5.000000, 21.000000, 100.000000
nn times  mean, stddev, stderr, min, q1, med, q3, max: 10.276000, 15.600443, 0.493329, 0.000000, 2.000000, 3.000000, 11.000000, 85.000000
penalties mean, stddev, stderr, min, q1, med, q3, max: 8054229.572000, 83612554.773451, 2644061.140697, 0.000000, 0.000000, 0.000000, 1000.000000, 1698994831.000000
*/
