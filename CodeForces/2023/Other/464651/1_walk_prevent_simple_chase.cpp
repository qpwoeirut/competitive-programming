#include <bits/stdc++.h>

using namespace std;
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
    const int INF = 1001001001;
    const int MK = 5;

    int N, M;
    int dist[MN][MN];
    int cdist[MN];
    vector<int> adj[MN];

    vector<pii> bob_moves_after_prevent(int alice, int bob, int k=MK) {
        vector<pii> moves;
        moves.emplace_back(dist[alice][bob], bob);
        for (int v: adj[bob]) {
            moves.emplace_back(dist[alice][v], v);
        }
        sort(moves.rbegin(), moves.rend());
        while (moves.size() > k) moves.pop_back();

        return moves;
    }

    void solve(int n, int m, const vector<pii>& edges, interactor interact) {
        assert(n <= MN);
        assert(m == edges.size());

        N = n;
        M = m;
        for (int i=0; i<N; ++i) {
            for (int j=0; j<N; ++j) {
                dist[i][j] = INF;
            }
            dist[i][i] = 0;
            adj[i].clear();
        }

        for (const pii& edge: edges) {
            const int a = edge.first, b = edge.second;
            adj[a].push_back(b);
            adj[b].push_back(a);
            dist[a][b] = 1;
            dist[b][a] = 1;
        }

        for (int k=0; k<N; ++k) {
            for (int i=0; i<N; ++i) {
                for (int j=0; j<N; ++j) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }

        set<int> centers;
        int center_dist = INF;
        for (int u=0; u<N; ++u) {
            int mx_dist = *max_element(dist[u], dist[u]+N);
            if (center_dist > mx_dist) {
                center_dist = mx_dist;
                centers.clear();
            }
            if (center_dist == mx_dist) {
                centers.insert(u);
            }
        }
        //debug(N, M, edges); debug2(dist, N, N); debug(centers);

        for (int i=0; i<N; ++i) {
            cdist[i] = INF;
            for (int center: centers) {
                cdist[i] = min(cdist[i], dist[i][center]);
            }
        }

        int alice = 0, bob = N - 1;
        for (int t=1; t<=100; ++t) {
            if (dist[alice][bob] > center_dist) {
                int mn_dist = INF;
                int nxt = -1;
                for (int v: adj[alice]) {
                    if (mn_dist > cdist[v]) {
                        mn_dist = cdist[v];
                        nxt = v;
                    }
                }

                bob = interact(0, vector<int>(), nxt);
                alice = nxt;
            } else {
                int mn_dist = INF;
                int nxt = -1;

                const vector<pii> moves = bob_moves_after_prevent(alice, bob);
                int target = moves.back().second;  // sorted already

                for (int v: adj[alice]) {
                    if (mn_dist > dist[v][target]) {
                        mn_dist = dist[v][target];
                        nxt = v;
                    }
                }

                bob = interact(N+1, vector<int>(), nxt);
                alice = nxt;
            }

            if (alice == bob) {
                return;
            }
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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    vector<pii> edges;
    
    cin >> n >> m;
    for (int i=0; i<m; ++i) {
        int a, b;
        cin >> a >> b;
        edges.emplace_back(a-1, b-1);
    }

    Solution::solve(n, m, edges, interact);
}
