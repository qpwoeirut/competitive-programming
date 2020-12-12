#include <bits/stdc++.h>

using namespace std;

#define to first
#define cost second

typedef pair<int,int> pii;

const int MN = 100005;

int N, M, C;
int A[MN];
int deg[MN];

set<pii> adj[MN];

int main() {
    freopen("timeline.in", "r", stdin);
    freopen("timeline.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M >> C;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }

    for (int i=0; i<C; ++i) {
        int a, b, x;
        cin >> a >> b >> x;
        --a; --b;
        adj[a].emplace(b, x);
        ++deg[b];
    }

    queue<int> q;
    for (int i=0; i<N; ++i) {
        if (deg[i] == 0) {
            q.push(i);
        }
    }

    while (q.size() > 0) {
        int cur = q.front();
        q.pop();
        cerr << cur << endl;

        for (auto it=adj[cur].begin(); it!=adj[cur].end(); ) {
            A[it->to] = max(A[it->to], A[cur] + it->cost);
            
            if (--deg[it->to] == 0) {
                q.push(it->to);
            }
            it = adj[cur].erase(it);
        }
    }

    for (int i=0; i<N; ++i) {
        cout << A[i] << '\n';
    }
}        
