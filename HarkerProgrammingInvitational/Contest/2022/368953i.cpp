#include <bits/stdc++.h>

using namespace std;

using pii=pair<int,int>;
using ll=long long;

#define fi first
#define se second

const int MN = 50004;
const int INIT = 1001001001;
const int MOD = 1e9 + 7;

struct Edge {
    int u, v;
    int cost;

    const bool operator<(const Edge& o) const {
        return cost < o.cost;
    }
};

int N, M, Q;
Edge A[MN];

int par[MN];
set<int> members[MN];

vector<pii> queries[MN];
int ans[MN];

int root(const int u) {
    return u == par[u] ? u : par[u] = root(par[u]);
}
void join(const int u, const int v, const int cost) {
    int ru = root(u), rv = root(v);
    if (members[ru].size() < members[rv].size()) swap(ru, rv);

    par[rv] = par[v] = ru;
    for (const int x: members[rv]) {
        for (const pii& q: queries[x]) {
            if (root(q.fi) == ru) {
                ans[q.se] = min(ans[q.se], cost);
            }
        }
    }
    members[ru].insert(members[rv].begin(), members[rv].end());
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M >> Q;
    for (int i=0; i<M; ++i) {
        cin >> A[i].u >> A[i].v >> A[i].cost;
        --A[i].u; --A[i].v;
    }
    for (int i=0; i<Q; ++i) {
        int d, e;
        cin >> d >> e;
        --d; --e;
        queries[d].emplace_back(e, i);
        queries[e].emplace_back(d, i);

        ans[i] = INIT;
    }

    for (int i=0; i<N; ++i) {
        par[i] = i;
        members[i].insert(i);
    }

    sort(A, A+M);
    for (int i=0; i<M; ++i) {
        join(A[i].u, A[i].v, A[i].cost);
        //for (int j=0; j<N; ++j) { cerr << par[j] << ' '; } cerr << endl;
    }

    for (int i=0; i<Q; ++i) {
        cout << (ans[i] == INIT ? -1 : ans[i]) << '\n';
    }
}
