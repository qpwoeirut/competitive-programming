#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

//using ll=long long;
using ll=int;
using pii=pair<int,int>;

constexpr int MN = 300;
constexpr int MK = 8;
constexpr ll INF = 1e9;

int N, K;
ll adj[MN][MN];
pii rem[MN*MN];
int rtime[MN][MN];
ll dp[MK+1][MN];

ll ans[MN*MN];

ll naive_ans[MN*MN];
ll naive_adj[MN][MN];
void naive() {
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            naive_adj[i][j] = adj[i][j];
        }
    }
    for (int i=0; i<N*N; ++i) {
        naive_adj[rem[i].fi][rem[i].se] = INF;

        for (int k=0; k<=K; ++k) {
            for (int n=0; n<N; ++n) {
                dp[k][n] = INF;
            }
        }
        dp[0][0] = 0;
        for (int k=1; k<=K; ++k) {
            for (int v=0; v<N; ++v) {
                for (int u=0; u<N; ++u) {
                    dp[k][v] = min(dp[k][v], dp[k-1][u] + naive_adj[u][v]);
                }
            }
        }
        naive_ans[i] = dp[K][N-1] == INF ? -1 : dp[K][N-1];
    }
}

void solve() {
    for (int i=0; i<=K; ++i) {
        for (int j=0; j<N; ++j) {
            dp[i][j] = INF;
        }
    }
    dp[0][0] = 0;

    bitset<MN> upd, upd1;
    for (int i=N*N-1; i>0; --i) {
        //cerr << "\n\n" << i << endl;
        //for (int k=0; k<=K; ++k) { for (int n=0; n<N; ++n) { cerr << dp[k][n] << ' '; } cerr << endl; }

        for (int k=1; k<=K; ++k) {
            if (dp[k][rem[i].se] > dp[k-1][rem[i].fi] + adj[rem[i].fi][rem[i].se]) {
                dp[k][rem[i].se] = dp[k-1][rem[i].fi] + adj[rem[i].fi][rem[i].se];
                upd[rem[i].se] = true;
            }

            if (k == K) continue;

            for (int u=0; u<N; ++u) {
                if (upd[u] == false) continue;

                for (int v=0; v<N; ++v) {
                    if (dp[k+1][v] > dp[k][u] + adj[u][v] && rtime[u][v] > i) {
                        dp[k+1][v] = dp[k][u] + adj[u][v];
                        upd1[v] = true;
                    }
                }
            }
            swap(upd, upd1);
            upd1.reset();
        }

        ans[i-1] = dp[K][N-1];
    }
    ans[N*N-1] = INF;

    for (int i=0; i<N*N; ++i) {
        ans[i] = ans[i] == INF ? -1 : ans[i];
    }
}

void test() {
    mt19937 rng(8);
    for (N=1; N<=10; ++N) {
        for (K=1; K<=3; ++K) {
            cerr << N << ' ' << K << endl;
            for (int t=0; t<100000; ++t) {
                for (int i=0; i<N; ++i) {
                    for (int j=0; j<N; ++j) {
                        adj[i][j] = 1 + (rng() % 1000);
                    }
                }
                for (int i=0; i<N*N; ++i) {
                    rem[i] = pii(i / N, i % N);
                }
                shuffle(rem, rem+N*N, rng);
                for (int i=0; i<N*N; ++i) {
                    rtime[rem[i].fi][rem[i].se] = i;
                }

                solve();
                naive();
                for (int i=0; i<N*N; ++i) {
                    if (ans[i] != naive_ans[i]) {
                        cout << N << ' ' << K << endl;
                        for (int u=0; u<N; ++u) {
                            for (int v=0; v<N; ++v) {
                                cout << adj[u][v] << ' ';
                            } cout << endl;
                        }
                        for (int a=0; a<N*N; ++a) {
                            cout << rem[a].fi << ' ' << rem[a].se << endl;
                        }
                        cout << endl;
                        for (int a=0; a<N*N; ++a) {
                            cout << ans[a] << ' ' << naive_ans[a] << endl;
                        }
                        assert(0);
                    }
                }
            }
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    //test(); return 0;

    cin >> N >> K;
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            cin >> adj[i][j];
        }
    }

    for (int i=0; i<N*N; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        rem[i] = pii(u, v);
        rtime[u][v] = i;
    }

    solve();
    for (int i=0; i<N*N; ++i) {
        cout << ans[i] << '\n';
    }
}
/*
2 2
1 2
8 4
1 1
1 2
2 2
2 1
*/
