#include <bits/stdc++.h>

using namespace std;

const int MN = 200005;

int N, M;
vector<int> adm[MN];

int child[MN];

int par[MN];
int sz[MN];
int root(int u) {
    if (par[u] != u) {
        par[u] = root(par[u]);
    }
    return par[u];
}

int join(int, int);

void join_children(int ru, int rv) {
    //cerr << "join_children: " << ru << ' ' << rv << ' ' << adm[rv].size() << endl;
    while (adm[rv].size() > 0) {
        int cur = adm[rv].back();
        adm[rv].pop_back();
        if (child[ru] == -1) {
            child[ru] = cur;
        } else {
            child[ru] = join(child[ru], cur);
        }
    }
    if (child[ru] != -1 && child[rv] != -1) {
        child[ru] = join(child[ru], child[rv]);
    } else if (child[ru] == -1 && child[rv] != -1) {
        child[ru] = child[rv];
    }
    //cerr << "joined children: " << ru << ' ' << rv << endl;
}

int join(int u, int v) {
    assert(u != -1 && v != -1);
    int ru = root(u);
    int rv = root(v);

    if (ru == rv) return ru;
    //cerr << u << ' ' << v << ' ' << ru << ' ' << rv << endl;
    if (sz[ru] < sz[rv]) swap(ru, rv);
    par[rv] = par[v] = ru;
    sz[ru] += sz[rv];

    join_children(ru, ru);
    join_children(ru, rv);

    //cerr << "joined: " << u << ' ' << v << endl;
    return ru;
}

int mark[MN];
int main() {
    freopen("fcolor.in", "r", stdin);
    freopen("fcolor.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M;
    for (int i=0; i<M; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        adm[u].push_back(v);
    }
    for (int i=0; i<N; ++i) {
        par[i] = i;
        sz[i] = 1;
        child[i] = -1;
    }
    for (int i=0; i<N; ++i) {
        join_children(i, i);
        //cerr << "processed " << i << endl;
    }

    //for (int i=0; i<N; ++i) { cerr << root(i) << ' '; } cerr << endl;

    int cur_mark = 1;
    for (int i=0; i<N; ++i) {
        if (mark[root(i)] == 0) {
            mark[root(i)] = cur_mark++;
        }

        cout << mark[root(i)] << '\n';
    }
}

