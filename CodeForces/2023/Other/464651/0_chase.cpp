#include <bits/stdc++.h>

using namespace std;
using ll=long long;
using pll=pair<ll,ll>;
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

ll ipow(ll a, ll b) {
    ll r = 1;
    while (b --> 0) r *= a;
    return r;
}

namespace Solution {
    const int MN = 100;
    const ll INF = 1e17;
    const int MK = 5;

    int N, M;
    ll dist[MN][MN];
    vector<int> adj[MN];

    vector<pll> bob_adj_moves(int alice, int bob, int k=MK) {
        vector<pll> moves;
        moves.emplace_back(dist[alice][bob], bob);
        for (int v: adj[bob]) {
            moves.emplace_back(dist[alice][v], v);
        }
        sort(moves.rbegin(), moves.rend());
        while (moves.size() > k) moves.pop_back();

        return moves;
    }

    ll node_score(int node, const vector<pll>& moves) {
        ll score = 0;
        for (const pll& move: moves) score += ipow(100 - dist[node][move.second], 6);
        return score;
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

        int alice = 0, bob = N - 1;
        for (int t=1; t<=100; ++t) {
            const vector<pll> moves = bob_adj_moves(alice, bob);

            ll mx_score = node_score(alice, moves);
            int nxt = alice;
            for (int v: adj[alice]) {
                ll score = node_score(v, moves);
                if (mx_score < score) {
                    mx_score = score;
                    nxt = v;
                }
            }

            bob = interact(0, vector<int>(), nxt);
            alice = nxt;

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
