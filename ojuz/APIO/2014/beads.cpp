#include <bits/stdc++.h>

using namespace std;

#define to first
#define len second

typedef long long ll;
typedef pair<ll,ll> pii;

const int MN = 200001;

struct Edge {
    int from, to;
    ll len;

    Edge(int _from, int _to, ll _len) {
        from = _from;
        to = _to;
        len = _len;
    }

    inline const bool operator<(const Edge& other) const {
        if (len != other.len) {
            return len < other.len;
        }
        if (from != other.from) {
            return from < other.from;
        }
        return to < other.to;
    }
    inline const bool operator>(const Edge& other) const {
        return other < *this;
    }
};

void chmx(ll& a, ll b) {if (a<b) a=b;}

int N;
set<Edge> adj[MN];
bool leaf[MN];

ll two_len[MN];
ll submax[MN], subsize[MN];
ll left_mx[MN], right_mx[MN];

pii range[MN];
int mark = 0;
void calc_range(int node, int par) {
    range[node].first = mark++;
    for (auto it=adj[node].begin(); it!=adj[node].end(); ++it) {
        if (it->to == par) continue;
        calc_range(it->to, node);
    }
    range[node].second = mark;
}


void process(int node, int par) {
    submax[node] = two_len[node];
    subsize[node] = 1;
    for (auto it=adj[node].begin(); it!=adj[node].end(); ++it) {
        if (it->to == par) continue;
        process(it->to, node);
        chmx(submax[node], submax[it->to]);
        subsize[node] += subsize[it->to];
    }
}

ll remove_edge(int node, int par, ll edge_len) {
    ll ret = 1e18;
    if ((subsize[node] & 1) && par != -1) ret = edge_len;

    for (auto it=adj[node].begin(); it!=adj[node].end(); ++it) {
        if (it->to == par) continue;
        ret = min(ret, remove_edge(it->to, node, it->len));
    }

    return ret;
}


ll best = -1e18;
void dfs(int node, int par, ll edge_len) {
    if (par != -1) {
        ll cur = -edge_len;
        if (subsize[node] & 1) {
            cur += max(left_mx[range[node].first], right_mx[range[node].second]);
        } else {
            cur += submax[node];
        }
        if (cur != -edge_len) {
            chmx(best, cur);
        }
    }

    for (auto it=adj[node].begin(); it!=adj[node].end(); ++it) {
        if (it->to == par) continue;
        dfs(it->to, node, it->len);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N-1; ++i) {
        ll a, b, c;
        cin >> a >> b >> c;
        --a; --b;
        adj[a].emplace(a, b, c);
        adj[b].emplace(b, a, c);
    }

    for (int i=0; i<N; ++i) {
        leaf[i] = adj[i].size() == 1;
        two_len[i] = 0;
    }

    set<Edge> twos;
    for (int i=0; i<N; ++i) {
        int leaf_ct = 0;
        for (auto it=adj[i].begin(); it!=adj[i].end(); ++it) {
            if (leaf[it->to]) ++leaf_ct;
        }
        //cerr << "i,leaf_ct: " << i << ' ' << leaf_ct << endl;
        for (auto it=adj[i].begin(); leaf_ct > 2 && it!=adj[i].end(); ) {
            if (leaf[it->to]) {
                adj[it->to].erase(Edge(it->to, it->from, it->len));
                it = adj[i].erase(it);
                --leaf_ct;
            } else {
                ++it;
            }
        }

        if (leaf_ct == 2) {
            for (auto it=adj[i].begin(); it!=adj[i].end(); ++it) {
                if (leaf[it->to]) {
                    twos.insert(*it);
                    break;
                }
            }
        }
    }

    //cerr << "twos:"; for (auto it=twos.begin(); it!=twos.end(); ++it) { cerr << " (" << it->from << ',' << it->to << ": " << it->len << ") "; } cerr << endl;

    for (auto it=twos.begin(); it!=twos.end(); ++it) {
        adj[it->from].erase(*it);
        adj[it->to].erase(Edge(it->to, it->from, it->len));
    }

    ll total = 0;
    int edge_ct = 0;
    for (int i=0; i<N; ++i) {
        for (auto it=adj[i].begin(); it!=adj[i].end(); ++it) {
            if (it->from < it->to) {
                total += it->len;
                ++edge_ct;
            }
        }
    }
    //cerr << "total, edge_ct: " << total << ' ' << edge_ct << endl;
    //cerr << "====adj====\n"; for (int i=0; i<N; ++i) { cerr << i << ':';
    //  for (auto it=adj[i].begin(); it!=adj[i].end(); ++it) { cerr << " (" << it->from << ',' << it->to << ": " << it->len << ") "; } cerr << endl; }

    calc_range(0, -1);

    for (auto it=twos.begin(); it!=twos.end(); ++it) {
        two_len[range[it->from].first] = it->len;
    }

    left_mx[0] = 0;
    for (int i=0; i<N; ++i) {
        left_mx[i+1] = max(left_mx[i], two_len[i]);
    }
    right_mx[N-1] = 0;
    for (int i=N-1; i>0; --i) {
        right_mx[i-1] = max(right_mx[i], two_len[i]);
    }

    process(0, -1);

    if (edge_ct & 1) {
        if (twos.size() > 0) {
            cout << total + twos.rbegin()->len << endl;
        } else {
            ll cost = remove_edge(0, -1, 0);
            cout << total - cost << endl;
        }
    } else {
        if (twos.size() > 0) {
            dfs(0, -1, 0);
            cout << max(total, total + best) << endl;
        } else {
            cout << total << endl;
        }
    }
}
/*
5
1 2 10
1 3 40
1 4 15
1 5 20

10
4 10 2
1 2 21
1 3 13
6 7 1
7 9 5
2 4 3
2 5 8
1 6 55
6 8 34
*/

