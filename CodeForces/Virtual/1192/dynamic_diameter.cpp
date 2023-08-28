//dynamic_diameter.cpp created at 09/13/20 10:50:41

#include <bits/stdc++.h>

using namespace std;

#define FI first
#define SE second

typedef long long ll;
typedef pair<ll,ll> pll;

const ll MN = 100001;

ll N, Q, W;
set<pll> adj[MN];
pll parent[MN];
multiset<ll> paths[MN];
multiset<ll> ans;

ll get_ans(ll node) {
    if (paths[node].size() == 1) {
        return *paths[node].begin();
    }
    auto it = paths[node].rbegin();
    ll x = *it;
    ++it;
    ll y = *it;
    return x + y;
}

void dfs(ll node, ll par) {
    //cerr << "node,par: " << node << ' ' << par << endl;
    for (set<pll>::iterator it=adj[node].begin(); it!=adj[node].end(); ++it) {
        if (it->FI == par) continue;

        parent[it->FI] = pll(node, it->SE);

        dfs(it->FI, node);
        assert(paths[it->FI].size() > 0);
        ll dist = *paths[it->FI].rbegin() + it->SE;
        paths[node].insert(dist);
    }
    if (paths[node].empty()) {
        paths[node].insert(0);
    }
    ans.insert(get_ans(node));
}

void update(ll node, ll par, ll old_w, ll new_w) {
    if (par == -1 || old_w == new_w) return;
    //cerr << "n,p,ow,nw: " << node << ' ' << par << ' ' << old_w << ' ' << new_w << endl;
    //cerr << "paths:" << endl;
    //for (auto it=paths[par].begin(); it!=paths[par].end();  ++it) {cerr << *it << ' ';}cerr << endl;
    ll old_ans = get_ans(par);
    ll old_dist = *paths[par].rbegin();
    assert(paths[par].find(old_w) != paths[par].end());
    paths[par].erase(paths[par].find(old_w));
    paths[par].insert(new_w);

    ans.erase(ans.find(old_ans));
    ans.insert(get_ans(par));
 
    update(par, parent[par].FI, old_dist + parent[par].SE, *paths[par].rbegin() + parent[par].SE);
}

        
pll edge[MN];
ll weight[MN];
int main() {
    cin >> N >> Q >> W;

    for (int i=0; i<N-1; ++i) {
        ll u, v, w;
        cin >> u >> v >> w;
        --u; --v;
        adj[u].insert(pll(v, w));
        adj[v].insert(pll(u, w));
        edge[i] = pll(u, v);
        weight[i] = w;
    }

    parent[0] = pll(-1, 0);
    dfs(0, -1);

    ll last = 0;
    for (int i=0; i<Q; ++i) {
        ll d, e;
        cin >> d >> e;

        ll dd = (d + last) % (N - 1);
        ll ee = (e + last) % W;
        //cerr << "dd,ee: " << dd << ' ' << ee << endl;

        ll old = weight[dd];
        weight[dd] = ee;
        
        ll par, node;
        if (parent[edge[dd].FI].FI == edge[dd].SE) {
            par = edge[dd].SE;
            node = edge[dd].FI;
        } else if (parent[edge[dd].SE].FI == edge[dd].FI) {
            par = edge[dd].FI;
            node = edge[dd].SE;
        } else assert(false);

        parent[node] = pll(par, ee);
        update(node, par, old + *paths[node].rbegin(), ee + *paths[node].rbegin());

        last = *ans.rbegin();

        cout << last << endl;
    }
}
