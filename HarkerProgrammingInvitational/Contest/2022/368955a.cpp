#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

struct Query {
    int type;
    int a, b;
    int c;
};

int n, q;
vector<int> a;
vector<int> adj[MAXN];
Query query[MAXN];

namespace brute {
    int ans[MAXN];
    int par[MAXN];

    void dfs(int u, int p) {
        par[u] = p;
        for (int v: adj[u]) {
            if (v == p) continue;
            dfs(v, u);
        }
    }

    bool visited[MAXN];
    int answer_query(int qa, int qb, int qc) {
        vector<int> path_a, path_b;
        while (qa != -1) {
            path_a.push_back(qa);
            visited[qa] = true;
            qa = par[qa];
        }
        while (qb != -1 && !visited[qb]) {
            path_b.push_back(qb);
            qb = par[qb];
        }

        int ans = 0;
        for (int u: path_a) {
            ans += a[u] == qc;
            if (u == qb) break;
        }
        for (int u: path_b) {
            ans += a[u] == qc;
        }

        //cerr << qa << ' ' << qb << endl;
        //for (int u: path_a) { cerr << u << ',' << a[u] << ' '; if (u == qb) break; } cerr << endl;
        //for (int u: path_b) { cerr << u << ',' << a[u] << ' '; } cerr << endl << endl;

        for (int u: path_a) visited[u] = false;

        return ans;
    }

    void solve() {
        dfs(0, -1);

        for (int i=0; i<q; ++i) {
            if (query[i].type == 1) {
                a[query[i].a] = query[i].b;
            } else {
                ans[i] = answer_query(query[i].a, query[i].b, query[i].c);
            }
        }
    }
}

namespace sol {
}

mt19937 rng(8);

void test() {
    for (n=1; n<=1000; ++n) {
        for (int t=0; t<=100000; ++t) {
            for (int i=0; i<n; ++i) {
                adj[i].clear();
            }
            for (int i=1; i<n; ++i) {
                int u = rng() % i;
                adj[i].push_back(u);
                adj[u].push_back(i);
            }

            q = n + (rng() % 1000);
            for (int i=0; i<q; ++i) {
                query[i].type = rng() % 2;
                query[i].a = rng() % n;
                query[i].b = rng() % n;
                if (query[i].type == 2) {
                    query[i].c = rng() % n;
                } else {
                    query[i].c = 0;
                }
            }

            brute::solve();
            //sol::solve();
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> q;
    a = vector<int>(n);
    for (int i=0; i<n; ++i) {
        cin >> a[i];
    }

    for (int i=0; i<n-1; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i=0; i<q; ++i) {
        cin >> query[i].type >> query[i].a >> query[i].b;
        if (query[i].type == 1) {
            --query[i].a;
        } else {
            cin >> query[i].c;
            --query[i].a; --query[i].b;
        }
    }

    brute::solve();
    for (int i=0; i<q; ++i) {
        if (query[i].type == 2) {
            cout << brute::ans[i] << '\n';
        }
    }
}
