#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

typedef pair<int,int> pii;

const int MN = 100005;
const int LG = 20;

int N, Q;
int A[MN];
set<int> adj[MN];

int ans[MN];
int anc[LG][MN];

pii mark[MN];
int cur_mark = 1;
void dfs(const int node, const int par) {
    mark[node].fi = cur_mark++;
    ans[node] ^= A[node];
    for (const int child: adj[node]) {
        if (child == par) continue;
        ans[child] = ans[node];
        anc[0][child] = node;
        dfs(child, node);
    }
    mark[node].se = cur_mark;
}

bool is_anc(int a, int b) {
    return mark[a].fi <= mark[b].fi && mark[b].se <= mark[a].se;
}

int lca(int u, int v) {
    if (is_anc(u, v)) return u;
    if (is_anc(v, u)) return v;

    for (int i=LG-1; i>=0; --i) {
        if (anc[i][u] == -1) continue;
        if (!is_anc(anc[i][u], v)) {
            u = anc[i][u];
        }
    }
    return anc[0][u];
}

int BIT[MN];
void upd(int idx, int val) {
    for (; idx<=N; idx+=(idx&-idx)) BIT[idx] ^= val;
}
int query(int idx) {
    int ret = 0;
    for (; idx>0; idx-=(idx&-idx)) ret ^= BIT[idx];
    return ret;
}

int main() {
    freopen("cowland.in", "r", stdin);
    freopen("cowland.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> Q;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }

    for (int i=0; i<N-1; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        adj[u].insert(v);
        adj[v].insert(u);
    }

    for (int i=0; i<LG; ++i) {
        for (int j=0; j<N; ++j) {
            anc[i][j] = -1;
        }
    }

    dfs(0, -1);

    for (int i=1; i<LG; ++i) {
        for (int j=0; j<N; ++j) {
            if (anc[i-1][j] == -1) continue;
            anc[i][j] = anc[i-1][anc[i-1][j]];
        }
    }

    for (int i=0; i<Q; ++i) {
        int t, x, y;
        cin >> t >> x >> y;
        if (t == 1) {
            --x;
            //cerr << mark[x].fi << ' ' << mark[x].se << endl;
            upd(mark[x].fi, A[x] ^ y);
            upd(mark[x].se, A[x] ^ y);
            A[x] = y;
        } else if (t == 2) {
            --x; --y;
            int cur_lca = lca(x, y);
            int answer = ans[x] ^ ans[y] ^ A[cur_lca];
            //cerr << answer << endl;
            answer ^= query(mark[x].fi) ^ query(mark[y].fi);
            cout << answer << '\n';
        } else assert(false);
    }
}
