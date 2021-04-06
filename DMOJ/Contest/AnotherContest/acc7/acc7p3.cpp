//acc7p3.cpp created at 04/04/21 12:22:24

#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

typedef pair<int,int> pii;

const int MN = 100005;

int N, M;
int A[MN];

int par[MN], sz[MN];
int root(const int u) {
    return u == par[u] ? u : par[u] = root(par[u]);
}
bool join(const int u, const int v) {
    int ru = root(u);
    int rv = root(v);
    if (ru == rv) return false;

    if (sz[ru] < sz[rv]) swap(ru, rv);

    par[rv] = par[u] = par[v] = ru;
    sz[ru] += sz[rv];

    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }

    for (int i=0; i<N; ++i) {
        par[i] = i;
        sz[i] = 1;
    }

    for (int i=0; i<M; ++i) {
        int x, y;
        cin >> x >> y;
        --x; --y;

        join(x, y);
    }

    priority_queue<pii, vector<pii>, greater<pii>> pq;
    for (int i=0; i+1<N; ++i) {
        pq.emplace(A[i+1] - A[i], i);
    }

    int ans = 0;
    while (pq.size() > 0) {
        const pii p = pq.top(); pq.pop();

        if (join(p.se, p.se + 1)) ans += p.fi;
    }

    cout << ans << '\n';
}

