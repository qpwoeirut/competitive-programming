#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

typedef pair<int,int> pii;

const int MN = 22;
const int MOD = 1e9 + 7;

int N, K, S;
int M;
int A[MN];
int sender[MN], receiver[MN];
int G[MN][MN];
pii edge[MN * MN];
set<int> adj[MN];

inline void add(int& a, const int b) {
    a += b;
    if (a >= MOD) a -= MOD;
}

// dp[edges_mask][current_node][current_sender/receiver_pair]
int dp[1 << 16][MN][MN >> 1];
int count_ways() {
    //cerr << "receiver:"; for (int i=0; i<S; ++i) { cerr << ' ' << receiver[i]; } cerr << endl;
    for (int msk=0; msk<(1 << M); ++msk) {
        for (int u=0; u<N; ++u) {
            for (int i=0; i<S; ++i) {
                dp[msk][u][i] = 0;
            }
        }
    }
    dp[0][sender[0]][0] = 1;
    for (int i=0; i<S; ++i) {
        for (int msk=0; msk<(1 << M); ++msk) {
            for (int u=0; u<N; ++u) {
                if (dp[msk][u][i] == 0) continue;
                if (i+1 < S && receiver[i] == u) {
                    add(dp[msk][sender[i+1]][i+1], dp[msk][u][i]);
                }
                for (const int j: adj[u]) {
                    if ((msk >> j) & 1) continue;

                    add(dp[msk | (1 << j)][edge[j].se][i], dp[msk][u][i]);
                }
                //cerr << bitset<9>(msk).to_string() << ' ' << u << ' ' << i << ' ' << dp[msk][u][i] << endl;
            }
        }
    }

    return dp[(1 << M) - 1][receiver[S-1]][S-1];
}

void solve() {
    cin >> N >> K;
    M = 0;
    S = 0;
    int s_idx = 0, r_idx = 0;
    for (int i=0; i<N; ++i) {
        char c;
        cin >> c;
        if (c == 'S') {
            A[i] = 1;
            sender[s_idx++] = i;
            ++S;
        } else if (c == 'R') {
            A[i] = -1;
            receiver[r_idx++] = i;
        }
    }
    assert(S == s_idx);
    assert(S == r_idx);

    for (int i=0; i<N; ++i) {
        adj[i].clear();
    }

    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            char c;
            cin >> c;
            G[i][j] = c == '1';

            if (G[i][j]) {
                adj[i].insert(M);
                edge[M++] = pii(i, j);
            }
        }
    }

    //for (int i=0; i<M; ++i) { cerr << edge[i].fi << ' ' << edge[i].se << '\n'; } cerr << endl;

    int ans = 0;
    do {
        ans += count_ways();
        if (ans >= MOD) ans -= MOD;
    } while (next_permutation(receiver, receiver+S));

    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int T;
    cin >> T;

    while (T-- > 0) {
        solve();
    }
}
