//daily_commute.cpp created at 02/26/21 19:05:02

#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

typedef pair<int,int> pii;

const int MN = 200005;
const int INIT = 1001001001;

int N, M, D;
int A[MN];
pii swaps[MN];
set<int> adj[MN];

int pos[MN];
int dist[MN];
int total[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M >> D;
    for (int i=0; i<M; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;

        adj[b].insert(a);
    }

    for (int i=0; i<N; ++i) {
        cin >> A[i];
        --A[i];
        pos[A[i]] = i;
    }
    for (int i=0; i<D; ++i) {
        cin >> swaps[i].fi >> swaps[i].se;
        --swaps[i].fi;
        --swaps[i].se;
    }

    fill(dist, dist+N, INIT);
    queue<int> q;
    q.push(N-1);
    dist[N-1] = 0;

    while (q.size() > 0) {
        const int u = q.front(); q.pop();

        for (const int v: adj[u]) {
            if (dist[v] > dist[u] + 1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    multiset<int> totals;
    for (int i=0; i<N; ++i) {
        total[i] = pos[i] + dist[i];
        totals.insert(total[i]);
    }

    for (int i=0; i<D; ++i) {
        const int x = A[swaps[i].fi], y = A[swaps[i].se];
        totals.erase(totals.find(total[x]));
        totals.erase(totals.find(total[y]));

        swap(A[swaps[i].fi], A[swaps[i].se]);
        swap(pos[x], pos[y]);
        total[x] = pos[x] + dist[x];
        total[y] = pos[y] + dist[y];

        totals.insert(total[x]);
        totals.insert(total[y]);

        //cerr << "totals: "; for (const int p: totals) { cerr << p << ' '; } cerr << endl;
        //cerr << "pos: "; for (int j=0; j<N; ++j) { cerr << pos[j] << ' '; } cerr << endl;
        cout << *totals.begin() << '\n';
    }
}

