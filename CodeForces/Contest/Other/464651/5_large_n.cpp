#include <bits/stdc++.h>

#pragma GCC optimize("O3")
#pragma GCC optimize("avx2")

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
    const int MN = 100;
    const int TIME = 100;
    const int MX_TIME = 80;
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

    const int OPTS = BOB_OPTIONS;
    const int MX_BLOCKS = 3;

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

    int expectimax(int a, int b, int t) {
        if (t == MX_TIME) return 0;
        if (cache[t][a][b] != -1) return cache[t][a][b];
        
        int score = 0;
        int scores[BOB_OPTIONS];
        for (int target = 0; target < N; ++target) {
            const int move_penalty = p15[100 - t] * dist_penalty[a][target];
            if (move_penalty >= max_pen[t]) continue;

            ll adj_escore = 0;  // assume bob moves to adjacent node
            int adj_ct = 0;
            fill(scores, scores+BOB_OPTIONS, -1);
            for (; adj_ct<BOB_OPTIONS && bob_adj[a][b][adj_ct] != -1; ++adj_ct) {
                scores[adj_ct] = expectimax(target, bob_adj[a][b][adj_ct], t + 1);
                adj_escore += scores[adj_ct];
            }
            adj_escore /= adj_ct;

            ll tp_escore = 0;  // assume bob teleports
            int tp_ct = 0;
            for (; tp_ct<BOB_OPTIONS && bob_tp[a][b][tp_ct] != -1; ++tp_ct) {
                tp_escore += expectimax(target, bob_tp[a][b][tp_ct], t + 1);
            }
            tp_escore /= tp_ct;

            if (adj_ct <= MX_BLOCKS) {
                for (int mask=1; mask<(1 << adj_ct); ++mask) {
                    const int block_penalty = (100 - t) * p4(__builtin_popcount(mask));
                    if (move_penalty + block_penalty >= max_pen[t]) continue;

                    ll new_adj_escore = 0;
                    int new_adj_ct = 0;
                    for (int i=0; i<adj_ct; ++i) {
                        if ((mask & (1 << i)) == 0) {
                            new_adj_escore += scores[i];
                            ++new_adj_ct;
                        }

                        new_adj_escore += ((mask >> i) & 1) * scores[i];
                        new_adj_ct += (mask >> i) & 1;
                    }
                    new_adj_escore = (new_adj_ct == 0) ? expectimax(target, b, t+1) : new_adj_escore / new_adj_ct;

                    // assume bob_adj and bob_tp don't overlap
                    const int escore = ((new_adj_escore * (100 - TELEPORT) + tp_escore * TELEPORT) / 100) - move_penalty - block_penalty;
                    score = max(score, escore);
                }
            }

            const int escore = ((adj_escore * (100 - TELEPORT) + tp_escore * TELEPORT) / 100) - move_penalty;
            const int prevent_escore = adj_escore - move_penalty - (100 - t) * p4(adj[a].size() + 1);
            score = max(score, max(escore, prevent_escore));
        }

        return cache[t][a][b] = score;
    }

    int find_move(int a, int b, int t, int& move_target, __int128_t& block_mask, int& move_k) {
        int score = -1;
        int scores[BOB_OPTIONS];
        move_target = 0, block_mask = 0, move_k = 0;
        for (int target = 0; target < N; ++target) {
            const int move_penalty = p15[100 - t] * dist_penalty[a][target];
            if (move_penalty >= max_pen[t]) continue;

            ll adj_escore = 0;  // assume bob moves to adjacent node
            int adj_ct = 0;
            fill(scores, scores+BOB_OPTIONS, -1);
            for (; adj_ct<BOB_OPTIONS && bob_adj[a][b][adj_ct] != -1; ++adj_ct) {
                scores[adj_ct] = expectimax(target, bob_adj[a][b][adj_ct], t + 1);
                adj_escore += scores[adj_ct];
            }
            adj_escore /= adj_ct;

            ll tp_escore = 0;  // assume bob teleports
            int tp_ct = 0;
            for (; tp_ct<BOB_OPTIONS && bob_tp[a][b][tp_ct] != -1; ++tp_ct) {
                tp_escore += expectimax(target, bob_tp[a][b][tp_ct], t + 1);
            }
            tp_escore /= tp_ct;

            if (adj_ct <= MX_BLOCKS) {
                for (int mask=1; mask<(1 << adj_ct); ++mask) {
                    const int block_penalty = (100 - t) * p4(__builtin_popcount(mask));
                    if (move_penalty + block_penalty >= max_pen[t]) continue;

                    ll new_adj_escore = 0;
                    int new_adj_ct = 0;
                    for (int i=0; i<adj_ct; ++i) {
                        if ((mask & (1 << i)) == 0) {
                            new_adj_escore += scores[i];
                            ++new_adj_ct;
                        }
                    }
                    new_adj_escore = (new_adj_ct == 0) ? expectimax(target, b, t+1) : new_adj_escore / new_adj_ct;

                    // assume bob_adj and bob_tp don't overlap
                    const int escore = ((new_adj_escore * (100 - TELEPORT) + tp_escore * TELEPORT) / 100) - move_penalty - block_penalty;
                    if (score < escore) {
                        score = escore;
                        move_target = target;
                        block_mask = 0; for (int i=0; i<adj_ct; ++i) if (mask & (1 << i)) block_mask |= __int128(1) << bob_adj[a][b][i];
                        move_k = __builtin_popcount(mask);
                    }
                }
            }

            const int escore = ((adj_escore * (100 - TELEPORT) + tp_escore * TELEPORT) / 100) - move_penalty;
            if (score < escore) {
                score = escore;
                move_target = target;
                block_mask = 0;
                move_k = 0;
            }

            const int prevent_escore = adj_escore - move_penalty - (100 - t) * p4(adj[a].size() + 1);
            if (score < prevent_escore) {
                score = escore;
                move_target = target;
                block_mask = 0;
                move_k = N+1;
            }
            //debug(a, b, t, target, escore, prevent_escore, bob_adj[a][b], bob_tp[a][b]);
        }
        return cache[t][a][b] = score;
    }

    int alice, bob;
    void solve(int _n, int _m, const vector<pii>& edges, interactor interact) {
        N = _n;
        M = _m;
        //debug(N, M);

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
TESTS = 1000. n = [11,100]. sparse = false
scores    mean, stddev, stderr, min, q1, med, q3, max: 15.056000, 7.117223, 0.225066, -85.000000, 15.000000, 16.000000, 17.000000, 20.000000
nn scores mean, stddev, stderr, min, q1, med, q3, max: 15.568000, 3.632819, 0.114880, 0.000000, 15.000000, 16.000000, 17.000000, 20.000000
times     mean, stddev, stderr, min, q1, med, q3, max: 6.587000, 5.995534, 0.189595, 1.000000, 2.000000, 5.000000, 9.000000, 49.000000
nn times  mean, stddev, stderr, min, q1, med, q3, max: 6.334000, 5.969962, 0.188787, 0.000000, 2.000000, 5.000000, 9.000000, 49.000000
penalties mean, stddev, stderr, min, q1, med, q3, max: 29803.070000, 219082.235629, 6927.988595, 0.000000, 1000.000000, 3646.000000, 7876.000000, 4419109.000000
TESTS = 1000. n = [11,100]. sparse = true
scores    mean, stddev, stderr, min, q1, med, q3, max: -6476.694000, 78859.352766, 2493.751695, -2141770.000000, -42.000000, -2.000000, 12.000000, 19.000000
nn scores mean, stddev, stderr, min, q1, med, q3, max: 5.218000, 6.986163, 0.220922, 0.000000, 0.000000, 0.000000, 12.000000, 19.000000
times     mean, stddev, stderr, min, q1, med, q3, max: 6.376000, 11.334312, 0.358422, 1.000000, 2.000000, 3.000000, 7.000000, 100.000000
nn times  mean, stddev, stderr, min, q1, med, q3, max: 0.990000, 1.719855, 0.054387, 0.000000, 0.000000, 0.000000, 1.000000, 14.000000
penalties mean, stddev, stderr, min, q1, med, q3, max: 880594711.793000, 21371465918.194656, 675825092.381569, 100.000000, 128000.000000, 356175.000000, 2079553.000000, 671630616374.000000
*/

