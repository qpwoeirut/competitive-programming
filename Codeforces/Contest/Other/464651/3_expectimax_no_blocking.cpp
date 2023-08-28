#include <bits/stdc++.h>

#pragma GCC optimize("O3")

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
    consteval array<int, TIME + 1> gen_p15() {
        array<int, MN + 1> arr;
        for (int i=0; i<=MN; ++i) {
            arr[i] = i * (int)(sqrt(i) + 1e-6);
        }
        return arr;
    }
    constexpr array<int, TIME + 1> p15 = gen_p15();

    const int TELEPORT = 40;  // assume we never block and then don't block teleportation
    const int BOB_OPTIONS = 5;

    int N, M;
    vector<int> adj[MN];
    int max_pen[MN];  // for pruning
    int dist[MN][MN];
    int dist_penalty[MN][MN];

    array<int, BOB_OPTIONS> bob_adj[MN][MN];
    array<int, BOB_OPTIONS> bob_tp[MN][MN];

    int cache[MN][MN][TIME];  // [alice][bob][time] = score numerator

    int p4(int x) { return x > 31 ? max_pen[0] : x * x * x * x; }
    int p7(int x) { return x >  7 ? max_pen[0] : x * x * x * x * x * x * x; }

    int expectimax(int a, int b, int t) {
        if (t == TIME) return 0;
        if (cache[a][b][t] != -1) return cache[a][b][t];

        for (int target = 0; target < N; ++target) {
            if (p15[100 - t] * dist_penalty[a][target] >= max_pen[t]) continue;


            ll adj_escore = 0;
            int ct = 0;
            for (ct=0; ct<BOB_OPTIONS; ++ct) {
                if (bob_adj[a][b][ct] == -1) break;
                adj_escore += expectimax(target, bob_adj[a][b][ct], t + 1);
            }
            adj_escore /= ct;


            ll tp_escore = 0;
            for (ct=0; ct<BOB_OPTIONS; ++ct) {
                if (bob_tp[a][b][ct] == -1) break;
                tp_escore += expectimax(target, bob_tp[a][b][ct], t + 1);
            }
            tp_escore /= ct;


            const int move_penalty = p15[100 - t] * dist_penalty[a][target];
            const int escore = ((adj_escore * (100 - TELEPORT) + tp_escore * TELEPORT) / 100) - move_penalty;
            const int prevent_escore = adj_escore - move_penalty - (100 - t) * p4(adj[a].size() + 1);
            cache[a][b][t] = max(cache[a][b][t], max(escore, prevent_escore));
        }

        //debug(a, b, t, cache[a][b][t]);
        return cache[a][b][t];
    }

    int find_move(int a, int b, int t, int& move_target, int& move_k) {
        int score = -1;
        move_target = 0, move_k = 0;
        for (int target = 0; target < N; ++target) {
            if (p15[100 - t] * dist_penalty[a][target] >= max_pen[t]) continue;


            ll adj_escore = 0;
            int ct = 0;
            for (ct=0; ct<BOB_OPTIONS; ++ct) {
                if (bob_adj[a][b][ct] == -1) break;
                adj_escore += expectimax(target, bob_adj[a][b][ct], t + 1);
            }
            adj_escore /= ct;


            ll tp_escore = 0;
            for (const int b_tp: bob_tp[a][b]) {
                if (b_tp == -1) break;
                tp_escore += expectimax(target, b_tp, t + 1);
            }
            tp_escore /= bob_tp[a][b].size();


            const int move_penalty = p15[100 - t] * dist_penalty[a][target];
            const int escore = ((adj_escore * (100 - TELEPORT) + tp_escore * TELEPORT) / 100) - move_penalty;
            if (score < escore) {
                score = escore;
                move_target = target;
                move_k = 0;
            }

            const int prevent_escore = adj_escore - move_penalty - (100 - t) * p4(adj[a].size() + 1);
            if (score < prevent_escore) {
                score = escore;
                move_target = target;
                move_k = N+1;
            }

            //debug(a, b, t, target, escore, prevent_escore, bob_adj[a][b], bob_tp[a][b]);
        }
        return score;
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
                for (int t=0; t<TIME; ++t) {
                    cache[a][b][t] = a == b ? N*N*N * p15[101 - t] : -1;
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
                while (pos.size() > BOB_OPTIONS) pos.pop_back();

                bob_adj[a][b].fill(-1);
                for (int i=0; i<pos.size(); ++i) bob_adj[a][b][i] = pos[i].second;


                pos.clear();
                for (int u=0; u<N; ++u) {
                    pos.emplace_back(dist[a][u], u);
                }
                sort(pos.rbegin(), pos.rend());
                while (pos.size() > BOB_OPTIONS) pos.pop_back();

                bob_tp[a][b].fill(-1);
                for (int i=0; i<pos.size(); ++i) bob_tp[a][b][i] = pos[i].second;
            }
        }

        int target, k;
        for (int t=0; t<TIME; ++t) {
            //debug(alice, bob, t);
            const int escore = find_move(alice, bob, t, target, k);
            bob = interact(k, vector<int>(), target);
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
            cout << blocks[i];
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
Without RNG
1000
scores    mean, stddev, stderr, min, q1, med, q3, max: -1.083000, 67.728473, 2.141762, -1188.000000, 14.000000, 16.000000, 17.000000, 20.000000
nn scores mean, stddev, stderr, min, q1, med, q3, max: 13.666000, 6.246314, 0.197526, 0.000000, 14.000000, 16.000000, 17.000000, 20.000000
times     mean, stddev, stderr, min, q1, med, q3, max: 7.053000, 8.569025, 0.270976, 1.000000, 2.000000, 4.000000, 9.000000, 96.000000
nn times  mean, stddev, stderr, min, q1, med, q3, max: 4.898000, 5.483575, 0.173406, 0.000000, 1.000000, 3.000000, 7.000000, 36.000000
penalties mean, stddev, stderr, min, q1, med, q3, max: 406444.661000, 1697916.427798, 53692.831885, 0.000000, 1000.000000, 3646.000000, 11881.000000, 19929787.000000

With RNG
1000
scores    mean, stddev, stderr, min, q1, med, q3, max: -0.113000, 61.247663, 1.936821, -772.000000, 14.000000, 16.000000, 17.000000, 20.000000
nn scores mean, stddev, stderr, min, q1, med, q3, max: 13.718000, 6.201490, 0.196108, 0.000000, 14.000000, 16.000000, 17.000000, 20.000000
times     mean, stddev, stderr, min, q1, med, q3, max: 7.259000, 8.970503, 0.283672, 1.000000, 2.000000, 5.000000, 9.000000, 89.000000
nn times  mean, stddev, stderr, min, q1, med, q3, max: 4.883000, 5.161522, 0.163222, 0.000000, 1.000000, 3.000000, 7.000000, 42.000000
penalties mean, stddev, stderr, min, q1, med, q3, max: 399599.259000, 1578945.884630, 49930.652976, 0.000000, 1737.000000, 3646.000000, 11098.000000, 19887417.000000
*/

