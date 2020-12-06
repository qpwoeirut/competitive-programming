#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

typedef pair<int,int> pii;

const int MN = 100001;
const int LG = 18;
const int X = 1000;

struct Query {
    int idx;
    int child, anc;
    int type;

    Query(int _idx, int _child, int _anc, int _type) {
        idx = _idx;
        child = _child;
        anc = _anc;
        type = _type;
    }

    inline const bool operator<(const Query& other) const {
        if (anc == other.anc) {
            if (idx == other.idx) {
                return child < other.child;
            }
            return idx < other.idx;
        }
        return anc < other.anc;
    }
};

int N, M;
int A[MN];
int ct[MN];
vector<int> adj[MN];

bool ans[MN];
set<Query> query[MN];

int lift[LG][MN];

int cur_mark = 0;
pii mark[MN];
void dfs(const int node, const int par) {
    mark[node].fi = cur_mark++;
    for (const int child: adj[node]) {
        if (child == par) continue;
        lift[0][child] = node;
        dfs(child, node);
    }
    mark[node].se = cur_mark;
}

bool is_anc(const int anc, const int child) {
    return mark[anc].fi <= mark[child].fi && mark[child].se <= mark[anc].se;
}

int lca(int u, int v) {
    if (is_anc(u, v)) return u;
    if (is_anc(v, u)) return v;

    for (int i=LG-1; i>=0; --i) {
        if (lift[i][u] != -1 && !is_anc(lift[i][u], v)) {
            u = lift[i][u];
        }
    }
    return lift[0][u];
}

bool lift_val[LG][MN];
bool processed[MN];
void process(const int val) {
    if (processed[val]) return;
    //cerr << "processing: " << val << endl;

    for (int i=0; i<N; ++i) {
        lift_val[0][i] = A[i] == val;
    }
    for (int i=1; i<LG; ++i) {
        for (int j=0; j<N; ++j) {
            if (lift[i-1][j] == -1) lift_val[i][j] = false;
            else lift_val[i][j] = (lift_val[i-1][j] || lift_val[i-1][lift[i-1][j]]);
        }
    }

    for (const Query& q: query[val]) {
        //cerr << q.idx << ' ' << q.child << ' ' << q.anc << ' ' << q.type << endl;
        if (ans[q.idx]) continue;
        int u = q.child;
        for (int i=LG-1; i>=0; --i) {
            if (lift[i][u] != -1 && !is_anc(lift[i][u], q.anc)) {
                if (lift_val[i][u]) {
                    ans[q.idx] = true;
                    break;
                }
                u = lift[i][u];
            }
        }
        if (u != q.anc) {
            ans[q.idx] |= lift_val[0][u];
            u = lift[0][u];
        }
        ans[q.idx] |= lift_val[0][u];
    }

    processed[val] = true;
}

int main() {
    freopen("milkvisits.in", "r", stdin);
    freopen("milkvisits.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
        ++ct[A[i]];
    }

    for (int i=0; i<N-1; ++i) {
        int x, y;
        cin >> x >> y;
        --x; --y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    for (int i=0; i<LG; ++i) {
        for (int j=0; j<N; ++j) {
            lift[i][j] = -1;
        }
    }
    dfs(0, -1);
    for (int i=1; i<LG; ++i) {
        for (int j=0; j<N; ++j) {
            if (lift[i-1][j] == -1) continue;
            lift[i][j] = lift[i-1][lift[i-1][j]];
        }
    }

    for (int i=0; i<M; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        --a; --b;
        query[c].emplace(i, a, lca(a, b), c);
        query[c].emplace(i, b, lca(a, b), c);
        //cerr << "query i,a,b,lca,c: " << i << ' ' << a << ' ' << b << ' ' << lca(a,b) << ' ' << c << endl;
    }

    for (int i=0; i<N; ++i) {
        if (ct[A[i]] < X) {
            for (auto it=query[A[i]].begin(); it!=query[A[i]].end();) {
                //cerr << it->idx << ' ' << it->child << ' ' << it->anc << ' ' << it->type << endl;
                if (ans[it->idx] || (is_anc(i, it->child) && is_anc(it->anc, i))) {
                    ans[it->idx] = true;
                    it = query[A[i]].erase(it);
                } else {
                    ++it;
                }
            }
        } else {
            process(A[i]);
        }
    }

    for (int i=0; i<M; ++i) {
        cout << ans[i];
    }
    cout << endl;
}
