//melody.cpp created at 02/23/21 19:50:23

#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

typedef pair<int,int> pii;

const int MN = 102;
const int MX = 100005;
const int INIT = 1001001001;

int N, S, G, L;
string A[MN];

set<int> adj[MN];
int dist[MN][MN];
int par[MN][MN];

void bfs(const int start) {
    fill(dist[start], dist[start] + N, INIT);
    queue<pii> q;
    q.emplace(0, start);
    dist[start][start] = 0;
    par[start][start] = -1;

    while (q.size() > 0) {
        const pii cur = q.front(); q.pop();

        if (dist[start][cur.se] < cur.fi) continue;

        for (const int v: adj[cur.se]) {
            if (dist[start][v] > cur.fi + 1) {
                dist[start][v] = cur.fi + 1;
                par[start][v] = cur.se;

                q.emplace(dist[start][v], v);
            }
        }
    }
    dist[start][start] = 1;
}

int B[MX];
int dp[MX];
int prv[MX];

vector<int> pos[MN];
int ans[MX];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> S >> G;

    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }
    cin >> L;
    for (int i=0; i<L; ++i) {
        cin >> B[i];
        --B[i];

        pos[B[i]].push_back(i);
    }

    for (int i=0; i<N; ++i) {
        for (int j=i; j<N; ++j) {
            int diff = 0;
            for (int k=0; k<S; ++k) {
                diff += A[i][k] != A[j][k];
            }
            if (diff <= G) {
                adj[i].insert(j);
                adj[j].insert(i);
            }
        }
    }

    for (int i=0; i<N; ++i) bfs(i);

    for (int i=0; i<L; ++i) {
        dp[i] = 1;
        prv[i] = -1;
        for (int j=0; j<N; ++j) {
            int idx = (upper_bound(pos[j].begin(), pos[j].end(), i - dist[B[i]][j]) - pos[j].begin()) - 1;
            //cerr << "i,j,idx,d: " << i << ' ' << j << ' ' << idx << ' ' << dist[B[i]][j] << endl;
            if (idx >= 0) {
                idx = pos[j][idx];
                if (dp[i] < dp[idx] + 1) {
                    dp[i] = dp[idx] + 1;
                    prv[i] = idx;
                }
            }
        }
    }

    int best_val = 0, best_idx = -1;
    for (int i=0; i<L; ++i) {
        if (best_val < dp[i]) {
            best_val = dp[i];
            best_idx = i;
        }
    }
    assert(best_val >= 1);
    assert(best_val <= L);
    assert(best_idx != -1);

    //for (int i=0; i<L; ++i) { cerr << dp[i] << ' '; } cerr << endl;
    
    int cur = best_idx;
    for (int i=cur; i<L; ++i) {
        ans[i] = B[cur];
    }
    while (cur != -1) {
        //cerr << "cur, prv: " << cur << ' ' << prv[cur] << endl;
        if (prv[cur] == -1) {
            for (int i=0; i<=cur; ++i) {
                ans[i] = B[cur];
            }
            break;
        }

        int x = B[cur];
        int i = 0;
        while (x != B[prv[cur]]) {
            //cerr << "x, i: " << x << ' ' << i << endl;
            ans[cur - i] = x;
            ++i;
            x = par[B[prv[cur]]][x];
        }
        while (cur - i > prv[cur]) {
            ans[cur - i] = B[prv[cur]];
            ++i;
        }
        assert(cur - i == prv[cur]);

        cur = prv[cur];
    }

    cout << L - best_val << '\n';
    for (int i=0; i<L; ++i) {
        if (i) cout << ' ';
        cout << ans[i] + 1;
    }
    cout << endl;

}

/*
5 4 2
1111
2101
2000
0100
0000
7
1 5 4 5 3 2 1

4 4 1
0000
1111
1112
1113
6
1 1 2 3 4 2
*/
