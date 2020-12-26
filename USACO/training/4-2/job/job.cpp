/*
ID: zhongbr1
TASK: job
LANG: C++14
*/

//job.cpp created at 12/24/20 15:04:40

#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

typedef pair<int,int> pii;

const int MN = 36;
const int INIT = 1001001;

int N, M[2];
int A[2][MN];

map<int,int> adj[MN];
int par[MN];

int find_path(int finish) {
    fill(par, par+MN, -1);
    queue<pii> q;
    q.emplace(0, INIT);
    par[0] = -2;

    while (q.size() > 0) {
        const pii cur = q.front(); q.pop();

        if (cur.fi == finish) return cur.se;

        for (const pii& p: adj[cur.fi]) {
            if (par[p.fi] != -1 || p.se == 0) continue;

            par[p.fi] = cur.fi;
            q.emplace(p.fi, min(cur.se, p.se));
        }
    }

    return 0;
}

int flow(int part, int mx_time) {
    const int finish = M[part] + 1;
    for (int i=0; i<MN; ++i) {
        adj[i].clear();
    }
    for (int i=1; i<=M[part]; ++i) {
        adj[0][i] = INIT;
        adj[i][finish] = mx_time / A[part][i];
    }

    int total_flow = 0;
    int cur_flow = find_path(finish);
    while (cur_flow > 0 && total_flow < N) {
        total_flow += cur_flow;
        
        int cur = finish;
        while (cur != 0) {
            adj[par[cur]][cur] -= cur_flow;
            adj[cur][par[cur]] += cur_flow;

            cur = par[cur];
        }
        cur_flow = find_path(finish);
    }

    return min(N, total_flow);
}

int main() {
    freopen("job.in", "r", stdin);
    freopen("job.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M[0] >> M[1];
    vector<int> time[2];
    for (int part=0; part<2; ++part) {
        for (int i=1; i<=M[part]; ++i) {
            cin >> A[part][i];
        }

        for (int t=0; t<=N*20; ++t) {
            const int f = flow(part, t);
            while (time[part].size() < f) time[part].push_back(t);
        }
    }
    //for (int i=0; i<N; ++i) { cerr << time[0][i] << ' '; } cerr << endl;
    //for (int i=0; i<N; ++i) { cerr << time[1][i] << ' '; } cerr << endl;

    int ans1 = time[0].back();
    int ans2 = 0;
    reverse(time[1].begin(), time[1].end());
    for (int i=0; i<N; ++i) {
        ans2 = max(ans2, time[0][i] + time[1][i]);
    }

    cout << ans1 << ' ' << ans2 << endl;
}

