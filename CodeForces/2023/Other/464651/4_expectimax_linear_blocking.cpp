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
    const int MX_TIME = 50;
    consteval array<int, TIME + 1> gen_p15() {
        array<int, TIME + 1> arr;
        for (int i=0; i<=TIME; ++i) {
            arr[i] = i * (int)(sqrt(i) + 1e-6);
        }
        return arr;
    }
    constexpr array<int, TIME + 1> p15 = gen_p15();

    const int TELEPORT = 40;  // assume we never block and then don't block teleportation
    const int BOB_OPTIONS = 5;
    const int OPTS = 8;

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
    
    int scores[OPTS];

    int expectimax(int a, int b, int t) {
        if (t == MX_TIME) return 0;
        if (cache[t][a][b] != -1) return cache[t][a][b];

        for (int target = 0; target < N; ++target) {
            if (p15[100 - t] * dist_penalty[a][target] >= max_pen[t]) continue;

            for (int i=0; i<OPTS; ++i) {
                scores[i] = bob_adj[a][b][i] == -1 ? -1 : expectimax(target, bob_adj[a][b][i], t + 1);
            }

            ll adj_escore = 0;  // assume bob moves to adjacent node
            int adj_ct = 0;
            for (; adj_ct<BOB_OPTIONS && scores[adj_ct] != -1; ++adj_ct) {
                adj_escore += scores[adj_ct];
            }
            adj_escore /= adj_ct;

            ll tp_escore = 0;  // assume bob teleports
            int tp_ct = 0;
            for (; tp_ct<BOB_OPTIONS; ++tp_ct) {
                if (bob_tp[a][b][tp_ct] == -1) break;
                tp_escore += expectimax(target, bob_tp[a][b][tp_ct], t + 1);
            }
            tp_escore /= tp_ct;

            ll block_escore = adj_escore;
            int block_ct = adj_ct;
            int best_block_escore = 0;  // assume bob moves to adjacent node; blocking penalty is included
            for (int i=adj_ct, j=0; i<OPTS && j+1<adj_ct; ++i, ++j) {
                block_escore += (scores[i] != -1 ? scores[i] : 0) - scores[j];
                block_ct -= scores[i] == -1;
                best_block_escore = max(best_block_escore, (int)((block_escore / block_ct * (100 - TELEPORT) + tp_escore * TELEPORT) / 100 - (100 - t) * p4(j + 1)));
            }

            const int move_penalty = p15[100 - t] * dist_penalty[a][target];
            const int escore = ((adj_escore * (100 - TELEPORT) + tp_escore * TELEPORT) / 100) - move_penalty;
            const int prevent_escore = adj_escore - move_penalty - (100 - t) * p4(adj[a].size() + 1);
            cache[t][a][b] = max(cache[t][a][b], max(escore, max(prevent_escore, best_block_escore)));
        }

        return cache[t][a][b];
    }

    int find_move(int a, int b, int t, int& move_target, __int128_t& block_mask, int& move_k) {
        int score = -1;
        move_target = 0, block_mask = 0, move_k = 0;
        for (int target = 0; target < N; ++target) {
            if (p15[100 - t] * dist_penalty[a][target] >= max_pen[t]) continue;

            for (int i=0; i<OPTS; ++i) {
                scores[i] = bob_adj[a][b][i] == -1 ? -1 : expectimax(target, bob_adj[a][b][i], t + 1);
            }

            ll adj_escore = 0;  // assume bob moves to adjacent node
            int adj_ct = 0;
            for (; adj_ct<BOB_OPTIONS && scores[adj_ct] != -1; ++adj_ct) {
                adj_escore += scores[adj_ct];
            }
            adj_escore /= adj_ct;

            ll tp_escore = 0;  // assume bob teleports
            int tp_ct = 0;
            for (; tp_ct<BOB_OPTIONS; ++tp_ct) {
                if (bob_tp[a][b][tp_ct] == -1) break;
                tp_escore += expectimax(target, bob_tp[a][b][tp_ct], t + 1);
            }
            tp_escore /= tp_ct;

            ll block_escore = adj_escore;  // assume bob moves to adjacent node; blocking penalty is included
            int block_ct = adj_ct;
            __int128_t mask = 0;
            for (int i=adj_ct, j=0; i<OPTS && j+1<adj_ct; ++i, ++j) {
                block_escore += (scores[i] != -1 ? scores[i] : 0) - scores[j];
                block_ct -= scores[i] == -1;

                mask |= __int128_t(1) << bob_adj[a][b][j];

                const int sc = (block_escore / block_ct * (100 - TELEPORT) + tp_escore * TELEPORT) / 100 - (100 - t) * p4(j + 1);
                if (score < sc) {
                    score = sc;
                    move_target = target;
                    block_mask = mask;
                    move_k = j + 1;
                }
            }


            const int move_penalty = p15[100 - t] * dist_penalty[a][target];
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

            cache[t][a][b] = score;

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
scores    mean, stddev, stderr, min, q1, med, q3, max: -1327.574000, 27697.308615, 875.865803, -790265.000000, 15.000000, 16.000000, 17.000000, 20.000000
nn scores mean, stddev, stderr, min, q1, med, q3, max: 14.145000, 5.670800, 0.179326, 0.000000, 15.000000, 16.000000, 17.000000, 20.000000
times     mean, stddev, stderr, min, q1, med, q3, max: 6.918000, 9.076964, 0.287039, 1.000000, 2.000000, 5.000000, 9.000000, 100.000000
nn times  mean, stddev, stderr, min, q1, med, q3, max: 5.344000, 5.687501, 0.179855, 0.000000, 1.000000, 4.000000, 7.000000, 44.000000
penalties mean, stddev, stderr, min, q1, med, q3, max: 47291818.675000, 719740036.574112, 22760178.387871, 0.000000, 1891.000000, 4510.000000, 10864.000000, 18989251949.000000
*/
