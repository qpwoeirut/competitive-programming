//fil.cpp created at 01/13/21 20:06:30
 
#include <bits/stdc++.h>
 
using namespace std;
 
#define fi first
#define se second
 
typedef pair<int,int> pii;
 
const int MN = 6005;
const int MX = 1001001;
 
int N, M, K, S;
int par[MN], len[MN];
set<pii> adj[MN];
 
int total[MN];
bool exists[MX];
pii mark[MN];
int cur_mark = 0;
void process(const int u) {
    mark[u].fi = cur_mark++;
    for (const pii& p: adj[u]) {
        total[p.fi] = total[u] + p.se;
        process(p.fi);
    }
    if (u <= N) {
        exists[total[u]] = true;
    }
    mark[u].se = cur_mark;
}
 
bool anc(const int a, const int b) {
    return mark[a].fi <= mark[b].fi && mark[b].se <= mark[a].se;
}
 
vector<int> divs[MX];
 
bool solve(int node) {
    //cerr << "solving: " << node << ' ' << total[node] << endl;
    if (total[node] == K) return true;
    assert(total[node] < K);
 
    const int full = total[node];
    node = par[node];
    while (node != -1) {
        const int after = full - total[node];
        const int target = K - S - after;
        //cerr << node << ' ' << target << endl;
        if (target >= 0 && exists[target]) return true;
 
        if (N <= 500 && M <= 500) {
            for (int i=0; i<=N; ++i) {
                if (!anc(node, i)) continue;
                const int rep = S + total[i] - total[node];
                const int x = K - total[node] - (full - total[node]);
                cerr << x << ' ' << rep << ' ' << node << ' ' << i << endl;
                if (x % rep == 0) return true;
            }
        }
 
        node = par[node];
    }
 
    return false;
}
 
int main() {
    cin.tie(0)->sync_with_stdio(0);
 
    cin >> N >> M >> K >> S;
    ++S;
 
    for (int i=2; i<MN; ++i) {
        for (int j=i << 1; j<MN; j+=i) {
            divs[j].push_back(i);
        }
    }
 
    par[0] = -1;
    for (int i=1; i<=N; ++i) {
        cin >> par[i] >> len[i];
        adj[par[i]].emplace(i, len[i] + 1);
    }
    for (int i=0; i<M; ++i) {
        const int j = i + N + 1;
        cin >> par[j] >> len[j];
        adj[par[j]].emplace(j, len[j] + 1);
    }
 
    total[0] = 0;
    process(0);
 
    //for (int i=0; i<20; ++i) { cerr << exists[i] << ' '; } cerr << endl;
    
    for (int i=0; i<M; ++i) {
        const int j = i + N + 1;
        cout << (solve(j) ? "YES\n" : "NO\n");
    }
}
 
/*
2 4 22
2
0 1
1 5
2 13
2 10
1 4
0 7
 
3 3 9
2
0 1
0 2
0 3
0 1
0 2
0 3
 
2 4 12
2
0 2
1 2
0 2
1 2
2 2
3 2
*/
