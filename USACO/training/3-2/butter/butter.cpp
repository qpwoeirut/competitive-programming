/*
ID: zhongbr1
TASK: butter
LANG: C++14
*/

//butter.cpp created at 12/21/20 21:36:16

#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

typedef pair<int,int> pii;

const int MN = 805;
const int INIT = 1001001001;

int N, P, C;
int A[MN];
int dist[MN][MN];
set<pii> adj[MN];

bool chmn(int& a, const int& b) {
    if (a>b) {
        a = b; return true;
    }
    return false;
}

void dijkstra(const int start) {
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.emplace(0, start);

    while (pq.size() > 0) {
        const pii cur = pq.top(); pq.pop();

        for (const pii& p: adj[cur.se]) {
            if (chmn(dist[start][p.fi], cur.fi + p.se)) {
                pq.emplace(dist[start][p.fi], p.fi);
            }
        }
    }
}


int main() {
    freopen("butter.in", "r", stdin);
    freopen("butter.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> P >> C;
    for (int i=0; i<N; ++i) {
        int x;
        cin >> x;
        ++A[--x];
    }
    for (int i=0; i<C; ++i) {
        int u, v, d;
        cin >> u >> v >> d;
        --u; --v;
        adj[u].emplace(v, d);
        adj[v].emplace(u, d);
    }

    for (int i=0; i<P; ++i) {
        for (int j=0; j<P; ++j) {
            dist[i][j] = INIT;
        }
        dist[i][i] = 0;
    }
    for (int i=0; i<P; ++i) {
        dijkstra(i);
    }

    //for (int i=0; i<P; ++i) { for (int j=0; j<P; ++j) { cerr << dist[i][j] << ' '; } cerr << endl; }

    int best = INIT;
    for (int i=0; i<P; ++i) {
        int cur = 0;
        for (int j=0; j<P; ++j) {
            cur += A[j] * dist[i][j];
        }
        chmn(best, cur);
    }

    cout << best << endl;
}
