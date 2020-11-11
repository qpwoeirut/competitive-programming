#include <bits/stdc++.h>

using namespace std;

#define FI first
#define SE second
#define to first
#define cost second

typedef long long ll;
typedef pair<ll,ll> pll;

const int LG = 22;
const int MN = 100001;
const ll INF = 1e18;

void chmn(ll& a, ll b) {if (a>b) a=b;}

ll N, S, Q, E;
set<pll> adj[MN];
pll edge[MN];
bool shop[MN];

pll range[MN];
ll mark = 0;
ll dist[MN], magic[MN];
void process(ll node, ll par) {
    range[node].FI = mark++;
    magic[node] = shop[node] ? dist[node] : INF;
    for (auto it: adj[node]) {
        if (it.to == par) continue;
        dist[it.to] = dist[node] + it.cost;
        process(it.to, node);
        chmn(magic[node], magic[it.to]);
    }

    range[node].SE = mark;
}

bool inside(ll a, ll b) {
    return range[a].FI <= range[b].FI && range[b].SE <= range[a].SE;
}

ll lift[MN][LG];
ll min_magic[MN][LG];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N >> S >> Q >> E;
    --E;

    for (int i=0; i<N-1; ++i) {
        int a, b, w;
        cin >> a >> b >> w;
        --a; --b;
        adj[a].emplace(b, w);
        adj[b].emplace(a, w);
        edge[i] = pll(a, b);
    }

    for (int i=0; i<S; ++i) {
        int s;
        cin >> s;
        --s;
        shop[s] = true;
    }

    process(E, -1);
    for (int i=0; i<N; ++i) {
        //cerr << i << ": " << dist[i] << ' ' << magic[i] << endl;
        if (magic[i] != INF) {
            magic[i] -= 2 * dist[i];
        }
        //cerr << i << ": " << dist[i] << ' ' << magic[i] << endl;
        lift[i][0] = -1;
        min_magic[i][0] = magic[i];
    }
    for (int i=0; i<N-1; ++i) {
        ll low = edge[i].FI, high = edge[i].SE;
        if (!inside(low, high)) swap(low, high);
        
        lift[high][0] = low;
    }

    for (int i=1; i<LG; ++i) {
        for (int j=0; j<N; ++j) {
            if (lift[j][i-1] == -1) {
                lift[j][i] = -1;
                min_magic[j][i] = INF;
                continue;
            }
            lift[j][i] = lift[lift[j][i-1]][i-1];
            min_magic[j][i] = min(min_magic[j][i-1], min_magic[lift[j][i-1]][i-1]);
        }
    }

    for (int q=0; q<Q; ++q) {
        ll I, R;
        cin >> I >> R;
        --I; --R;

        ll low = edge[I].FI, high = edge[I].SE;
        if (!inside(low, high)) swap(low, high);
        if (!inside(high, R)) {
            cout << "escaped" << endl;
        } else {
            ll best = INF;
            ll cur = R;
            for (int i=LG - 1; i>=0; --i) {
                if (lift[cur][i] == -1 || !inside(low, lift[cur][i])) continue;
                chmn(best, min_magic[cur][i]);
                cur = lift[cur][i];
                //cerr << "cur,best: " << cur << ' ' << best << endl;
            }

            //cerr << "R,dist,best: " << R << ' ' << dist[R] << ' ' << best << endl;
            if (best == INF) {
                cout << "oo" << endl;
            } else {
                cout << dist[R] + best << endl;
            }
        }
    }
}
/*
5 2 3 1
1 2 3
1 3 2
3 4 1
3 5 2
2
4
2 2
2 5
4 5

10 2 5 4
7 2 3
4 8 3
9 10 1
6 7 3
9 2 3
10 1 2
8 2 2
5 2 1
3 8 2
8
7
2 1
1 5
8 4
6 2
7 7
*/
