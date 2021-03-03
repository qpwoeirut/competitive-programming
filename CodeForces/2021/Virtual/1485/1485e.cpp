//1485e.cpp created at 02/27/21 14:53:16

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MN = 200005;
const ll INIT = 1001001001;

void chmn(ll& a, const ll b) { if (a > b) a = b; }
void chmx(ll& a, const ll b) { if (a < b) a = b; }

ll N, M;
set<int> adj[MN];
ll A[MN];

int depth[MN];
ll dp[MN];

void process(const int u, const int par) {
    if (par != -1) {
        adj[u].erase(par);
    }
    chmx(M, depth[u]);
    for (const int v: adj[u]) {
        depth[v] = depth[u] + 1;
        process(v, u);
    }
}

vector<int> lvl[MN];

void solve() {
    M = 0;
    cin >> N;
    for (int i=0; i<N; ++i) {
        adj[i].clear();
    }
    for (int i=1; i<N; ++i) {
        int v;
        cin >> v;
        --v;
        adj[i].insert(v);
        adj[v].insert(i);
    }

    A[0] = 0;
    for (int i=1; i<N; ++i) {
        cin >> A[i];
    }

    depth[0] = 0;
    process(0, -1);
    ++M;
    for (int i=0; i<M; ++i) {
        lvl[i].clear();
    }

    for (int i=0; i<N; ++i) {
        lvl[depth[i]].push_back(i);
    }

    fill(dp, dp+N, 0);
    for (int i=M-2; i>=0; --i) {
        ll dmx1 = -INIT, dmx2 = -INIT;
        ll mn = INIT, mx = -INIT;
        for (const int b: lvl[i+1]) {
            chmn(mn, A[b]);
            chmx(mx, A[b]);
            chmx(dmx1, dp[b] - A[b]);
            chmx(dmx2, dp[b] + A[b]);
        }
        //cerr << "lvl,mn,mx,d1,d2: " << i << ' ' << mn << ' ' << mx << ' ' << dmx1 << ' ' << dmx2 << endl;
        for (const int u: lvl[i]) {
            for (const int r: adj[u]) {
                chmx(dp[u], dp[r] + max(abs(A[r] - mn), abs(mx - A[r])));
                chmx(dp[u], max(dmx1 + A[r], dmx2 - A[r]));
            }
        }
    }
    //cerr << "\ndp: "; for (int i=0; i<N; ++i) { cerr << dp[i] << ' '; } cerr << endl;

    cout << dp[0] << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int T;
    cin >> T;
    for (int t=1; t<=T; ++t) solve();
}

/*
iterate through all children

no swap
    dp[r] + abs(a[r] - a[b])

swap
    dp[b] + abs(a[r] - a[b]) = dp[b] + max(a[r] - a[b], a[b] - a[r]) = max(dp[b] - a[b] + a[r], dp[b] + a[b] - a[r])
    keep a dmx1 with max dp[b] - a[b]
    keep a dmx2 with max dp[b] + a[b]
*/
