#include <bits/stdc++.h>

using namespace std;

using ll=long long;

const int MN = 200005;

int N;
set<int> adj[MN], adj_cpy[MN];
ll brute_ans[MN];

void brute() {
    for (int u=0; u<N; ++u) {
        adj_cpy[u] = adj[u];
        adj_cpy[u].insert(u);
    }

    for (int i=0; i<N; ++i) {
        brute_ans[i] = 0;
        for (int u=i; u<N; ++u) {
            ll m = adj_cpy[u].size();
            brute_ans[i] += (m - 1) * (m - 2);
        }

        for (const int u: adj_cpy[i]) {
            for (const int v: adj_cpy[i]) {
                adj_cpy[u].insert(v);
            }
        }
        for (const int u: adj_cpy[i]) {
            if (u == i) continue;
            adj_cpy[u].erase(i);
        }
        adj_cpy[i].clear();

        //for (int u=0; u<N; ++u) {
        //    cout << u << ": ";
        //    for (int x: adj_cpy[u]) cout << x << ' ';
        //    cout << endl;
        //}
    }
}

ll ans[MN];
int par[MN];
int sz[MN];
int neighbors[MN];
int root(const int u) {
    return par[u] == u ? u : par[u] = root(par[u]);
}
void join(const int u, const int v) {
    int ru = root(u), rv = root(v);
    if (ru == rv) return;
    if (sz[ru] < sz[rv]) swap(ru, rv);

    sz[ru] += sz[rv];
    neighbors[ru] += neighbors[rv] - 2;  // one node is already counted, other node no longer exists
    par[u] = par[v] = par[ru] = par[rv] = ru;
}


void solve() {
    for (int u=0; u<N; ++u) {
        par[u] = u;
        sz[u] = 1;
        neighbors[u] = adj[u].size();
    }

    for (int i=0; i<N; ++i) {
        ans[i] = 0;
        for (int u=i; u<N; ++u) {
            ll nsum = 0;
            for (int v: adj[u]) {
                if (v < i) nsum += neighbors[root(v)] - 1;
                else ++nsum;
                //cerr << i << ' ' << u << ' ' << v << ' ' << nsum << endl;
            }
            ans[i] += nsum * (nsum - 1);
        }

        for (const int u: adj[i]) {
            if (root(u) < i) {
                join(u, i);
            }
        }
        //for (int j=0; j<N; ++j) cerr << j << ' ' << root(j) << ' ' << neighbors[root(j)] << endl;
    }
}

void test() {
    mt19937 rng(8);
    int mapping[MN];
    for (N=2; N<=20; ++N) {
        cout << N << endl;
        for (int t=0; t<10000; ++t) {
            for (int i=0; i<N; ++i) {
                adj[i].clear();
                mapping[i] = i;
            }
            shuffle(mapping, mapping+N, rng);
            for (int i=1; i<N; ++i) {
                int u = rng() % i;
                adj[mapping[u]].insert(mapping[i]);
                adj[mapping[i]].insert(mapping[u]);
            }

            solve();
            brute();

            for (int i=0; i<N; ++i) {
                if (ans[i] != brute_ans[i]) {
                    cout << N << endl;
                    for (int u=0; u<N; ++u) {
                        for (int v: adj[u]) {
                            if (u < v) cout << u+1 << ' ' << v+1 << endl;
                        }
                    }
                    assert(0);
                }
            }
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    //test(); return 0;

    cin >> N;
    for (int i=0; i<N-1; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;

        adj[u].insert(v);
        adj[v].insert(u);
    }

    solve();
    for (int i=0; i<N; ++i) {
        cout << ans[i] << '\n';
    }
}
/*
4
1 2
2 3
2 4
*/
