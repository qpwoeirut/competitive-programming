/*
ID: zhongbr1
TASK: stall4
LANG: C++14
*/

//stall4.cpp created at 12/24/20 14:47:48

#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

typedef pair<int,int> pii;

const int MN = 205 * 2;
const int INIT = 1001001;

int N, M;
map<int,int> adj[MN];
int par[MN];

int find_path() {
    fill(par, par+N+M+2, -1);
    queue<pii> q;
    q.emplace(0, INIT);
    par[0] = -2;

    while (q.size() > 0) {
        const pii cur = q.front(); q.pop();
        
        if (cur.fi == N+M+1) return cur.se;

        for (const pii& p: adj[cur.fi]) {
            if (par[p.fi] != -1 || p.se == 0) continue;
            par[p.fi] = cur.fi;
            q.emplace(p.fi, min(p.se, cur.se));
        }
    }
    return 0;
}

int main() {
    freopen("stall4.in", "r", stdin);
    freopen("stall4.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M;
    for (int i=1; i<=N; ++i) {
        int s;
        cin >> s;
        for (int j=0; j<s; ++j) {
            int x;
            cin >> x;
            adj[i][N+x] = 1;
        }
        adj[0][i] = 1;
    }
    for (int i=1; i<=M; ++i) {
        adj[N+i][N+M+1] = 1;
    }

    int ans = 0;
    int cur_flow = find_path();
    while (cur_flow > 0) {
        ans += cur_flow;

        int cur = N+M+1;
        while (cur != 0) {
            adj[par[cur]][cur] -= cur_flow;
            adj[cur][par[cur]] += cur_flow;

            cur = par[cur];
        }

        cur_flow = find_path();
    }

    cout << ans << endl;
}
