/*
ID: zhongbr1
TASK: comehome
LANG: C++11
*/

#include <bits/stdc++.h>

using namespace std;

#define FI first 
#define SE second 

typedef pair<char,int> pci;

int P;
set<pci> adj[128];
int dist[128];

struct cmps {
    inline const bool operator()(const pci& a, const pci& b) {
        return a.SE > b.SE;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("comehome.in", "r", stdin);
    freopen("comehome.out", "w", stdout);

    cin >> P;

    for (int i=0; i<P; i++) {
        char u, v;
        int d;
        cin >> u >> v >> d;

        adj[u].insert(pci(v, d));
        adj[v].insert(pci(u, d));
    }

    fill(dist, dist+128, 1001001001);

    priority_queue<pci, vector<pci>, cmps> pq;
    pq.push(pci('Z', 0));
    dist['Z'] = 0;

    while (pq.size() > 0) {
        pci cur = pq.top();
        pq.pop();

        if (isupper(cur.FI) && cur.FI != 'Z') {
            cout << cur.FI << ' ' << cur.SE << endl;
            return 0;
        }

        for (set<pci>::iterator it=adj[cur.FI].begin(); it!=adj[cur.FI].end(); it++) {
            if (dist[it->FI] > cur.SE + it->SE) {
                dist[it->FI] = cur.SE + it->SE;
                pq.push(pci(it->FI, dist[it->FI])); 
            }
        }
    }

    assert(false);
}

