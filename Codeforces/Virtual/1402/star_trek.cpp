//star_trek.cpp created at 09/07/20 09:57:16

#include <bits/stdc++.h>

using namespace std;

#define FI first
#define SE second

typedef long long ll;
typedef pair<ll,ll> pll;
typedef unordered_map<ll,bool> mib;

const ll MOD = 1e9 + 7;
const ll MN = 100001;

ll binpow(ll x, ll p) {
    ll res = 1;
    while (p) {
        res = (res * ((p&1) ? x : 1)) % MOD;
        x = (x * x) % MOD;
        p >>= 1;
    }
    return res;
}

ll N, D;
vector<ll> adj[MN];
pll winner[MN];
bool dfs(int node, int par) {
    //cerr << node << ' ' << par << endl;
    bool win = false;
    for (int i=0; i<adj[node].size(); ++i) {
        if (adj[node][i] == par) continue;
        if (!dfs(adj[node][i], node)) {
            winner[node].FI = adj[node][i];
            ++winner[node].SE;
            win = true;
        }
    }
    return win;
}
ll ct;
mib mem;
bool mdfs(ll node, ll par) {
    if (par != -1) {
        mib::iterator it=mem.find(node * MN + par);
        if (it != mem.end()) return it->SE;
    }

    bool ret = false;
    for (int i=0; i<adj[node].size(); ++i) {
        if (adj[node][i] == par) continue;
        if (!mdfs(adj[node][i], node)) {
            ret = true;
            break;
        }
    }
    if (par != -1) {
        mem[node * MN + par] = ret;
    }
    return ret;
}
ll dfs2(int node, int par) {
    if (winner[node].SE > 1) {
        return 0;
    }
    if (winner[node].SE == 0) {
        ll ret = ct;
        for (int i=0; i<adj[node].size(); ++i) {
            if (adj[node][i] == par) continue;
            ret += dfs2(adj[node][i], node);
        }
        return ret;
    }
    return dfs2(winner[node].FI, node);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N >> D;

    for (int i=0; i<N-1; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    if (D > 1) {
        cout << binpow(2 * N, D) << endl;
        return 0;
    }

    mem.reserve(MN << 1);
    bool cap = dfs(0, -1);
    for (int i=0; i<N; ++i) {
        if (!mdfs(i, -1)) {
            ++ct;
        }
    }
    ll ans = dfs2(0, -1) % MOD;
    if (cap) {
        ll total = (N * N) % MOD;
        ans = (total - ans) % MOD;
    }

    //cerr << "adj: " << endl;
    //for (int i=0; i<N; i++) {
    //    for (set<ll>::iterator it=adj[i].begin(); it!=adj[i].end(); it++) {
    //        cerr << *it << ' ';
    //    }
    //    cerr << endl;
    //} cerr << endl;
    //cerr << "cap,ct[0],ct[1]: " << cap << ' ' << ct[0] << ' ' << ct[1] << endl;
    //cerr << "mark: ";
    //for (int i=0; i<N; i++) {
    //    cerr << mark[i] << ' ';
    //} cerr << endl;
    //cerr << "winner: " << endl;
    //for (int i=0; i<N; i++) {
    //    for (set<ll>::iterator it=winner[i].begin(); it!=winner[i].end(); it++) {
    //        cerr << *it << ' ';
    //    }
    //    cerr << endl;
    //} cerr << endl;
    //cerr << "ans: " << endl;
    cout << (ans + MOD) % MOD << endl;
}
