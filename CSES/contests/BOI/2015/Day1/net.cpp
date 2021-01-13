//net.cpp created at 01/11/21 20:25:40

#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

typedef pair<int,int> pii;

const int MN = 500001;

int N;
set<int> adj[MN];
vector<pii> ans;

pii dfs(const int u, const int par) {
    if (adj[u].size() == 1) {
        return pii(u, -1);
    }

    vector<int> open;
    for (const int v: adj[u]) {
        if (v == par) continue;
        pii cur = dfs(v, u);
        assert(cur.fi != -1);

        while (true) {
            const int ct = (cur.fi != -1) + (cur.se != -1);
            if (ct + open.size() > 2) {
                ans.emplace_back(open.back(), cur.fi);
                cur.fi = -1; swap(cur.fi, cur.se);
                open.pop_back();
            } else {
                break;
            }
        }
        if (cur.fi != -1) open.push_back(cur.fi);
        if (cur.se != -1) open.push_back(cur.se);
        assert(open.size() <= 2);
    }

    if (par == -1) {
        if (open.size() == 2) {
            ans.emplace_back(open[0], open[1]);
        } else {
            assert(open.size() == 1);
            ans.emplace_back(u, open[0]);
        }

        return pii(-1, -1);
    }

    open.push_back(-1);
    assert(open.size() >= 2);
    return pii(open[0], open[1]);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N-1; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        adj[u].insert(v);
        adj[v].insert(u);
    }

    int root = 0;
    for (; root<N && adj[root].size() == 1; ++root);
    assert(root < N);

    dfs(root, -1);

    cout << ans.size() << endl;
    for (int i=0; i<ans.size(); ++i) {
        cout << ans[i].fi + 1 << ' ' << ans[i].se + 1 << '\n';
    }
}
/*
6
1 2
2 3
2 4
5 4
6 4

8
1 2
2 3
3 4
4 5
3 6
3 7
3 8
*/
