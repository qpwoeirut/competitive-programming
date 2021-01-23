//fil.cpp created at 01/13/21 20:06:30

#include <bits/stdc++.h>

using namespace std;

#define LB lower_bound
#define UB upper_bound
#define all(x) (x).begin(), (x).end()

#define fi first
#define se second

typedef pair<int,int> pii;

const int MN = 6005;
const int MX = 1000005;

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
vector<int> pos[MX];

bool solve(int node) {
    //cerr << "solving: " << node << ' ' << total[node] << endl;
    if (total[node] == K) return true;
    assert(total[node] < K);

    const int full = total[node];
    const int x = K - full;
    //cerr << "full=" << full << endl;
    //cerr << "x=" << x << endl;

    node = par[node];
    while (node != -1) {
        const int after = full - total[node];
        const int target = K - S - after;
        //cerr << node << ' ' << target << endl;
        if (target >= 0 && exists[target]) return true;

        for (const int d: divs[x]) {
            const int t = d + total[node] - S;
            //cerr << "x,d,t = " << x << ' ' << d << ' ' <<t << endl;
            if (t < 0) continue;
            if (LB(all(pos[t]), mark[node].fi) != LB(all(pos[t]), mark[node].se)) return true;
        }
        //const int rep = S + total[i] - total[node];

        node = par[node];
    }

    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M >> K >> S;
    ++S;

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

    for (int i=0; i<=N; ++i) {
        pos[total[i]].push_back(mark[i].fi);
    }
    for (int i=0; i<MX; ++i) {
        if (pos[i].size() > 0) {
            sort(all(pos[i]));
        }
    }
    set<int> nums;
    for (int i=N+1; i<=N+M; ++i) {
        nums.insert(K - total[i]);
    }
    for (const int i: nums) {
        //cerr << "i=" << i << endl;
        divs[i].push_back(0);
        for (int d=1; d*d<=i; ++d) {
            if ((i % d) == 0) {
                divs[i].push_back(d);
                if (d * d != i) {
                    divs[i].push_back(i / d);
                }
            }
        }
    }

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
