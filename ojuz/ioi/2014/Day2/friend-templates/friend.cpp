#include <bits/stdc++.h>
#include "friend.h"

using namespace std;

const int MN = 100001;
set<int> adj[MN];

void construct(int n, int host[], int protocol[]) {
    for (int i=1; i<n; ++i) {
        int u = host[i];
        if (protocol[i] == 0 || protocol[i] == 2) {
            adj[u].insert(i);
            adj[i].insert(u);
        }
        if (protocol[i] == 1 || protocol[i] == 2) {
            for (auto it=adj[u].begin(); it!=adj[u].end(); ++it) {
                adj[*it].insert(i);
                adj[i].insert(*it);
            }
        }
    }
}

int solve1(int n, int confidence[], int host[], int protocol[]) {
    construct(n, host, protocol);
    int ans = 0;
    for (int mask=0; mask<(1 << n); ++mask) {
        bool ok = true;
        for (int u=0; u<n; ++u) {
            if (((mask >> u) & 1) == 0) continue;
            for (int v=u+1; v<n; ++v) {
                if (((mask >> v) & 1) == 0) continue;

                if (adj[u].count(v)) {
                    ok = false;
                    break;
                }
            }
        }
        if (ok) {
            int sum = 0;
            for (int i=0; i<n; ++i) {
                if ((mask >> i) & 1) {
                    sum += confidence[i];
                }
            }
            ans = max(ans, sum);
            //for (int i=0; i<n; ++i) { if ((mask >> i) & 1) { cerr << i << ' '; } }cerr << endl;
        }
    }

    return ans;
}

int solve2(int n, int confidence[], int host[], int protocol[]) {
    int sum = 0;
    for (int i=0; i<n; ++i) {
        sum += confidence[i];
    }
    return sum;
}

int solve3(int n, int confidence[], int host[], int protocol[]) {
    int ans = 0;
    for (int i=0; i<n; ++i) {
        ans = max(ans, confidence[i]);
    }
    return ans;
}

bool visited[MN];
int dp[MN][2];
void dfs(int node, int par, int conf[]) {
    visited[node] = true;
    dp[node][0] = 0;
    dp[node][1] = conf[node];

    for (auto it=adj[node].begin(); it!=adj[node].end(); ++it) {
        if (*it == par) continue;
        dfs(*it, node, conf);

        dp[node][0] += max(dp[*it][0], dp[*it][1]);
        dp[node][1] += dp[*it][0];
    }
}

int solve4(int n, int confidence[], int host[], int protocol[]) {
    construct(n, host, protocol);
    fill(visited, visited+n, false);
    int ans = 0;
    for (int i=0; i<n; ++i) {
        if (!visited[i]) {
            dfs(i, -1, confidence);
            ans += max(dp[i][0], dp[i][1]);
        }
    }
    return ans;
}

int mark[MN];
int ct[2];
bool a[MN];
int rt[MN];
int root(int u) {
    if (rt[u] != u) {
        rt[u] = root(rt[u]);
    }
    return rt[u];
}
void join(int u, int v) {
    int ru = root(u), rv = root(v);
    rt[ru] = rv;
}

int solve5(int n, int confidence[], int host[], int protocol[]) {
    fill(a, a+n, false);
    fill(mark, mark+n, -1);
    for (int i=0; i<n; ++i) {
        rt[i] = i;
        assert(confidence[i] == 1);
    }
    mark[0] = 0;
    for (int i=1; i<n; ++i) {
        int u = host[i];
        assert(mark[u] == 0 || mark[u] == 1);
        assert(mark[i] == -1);
        if (protocol[i] == 0) {
            mark[i] = !mark[u];
            join(i, u);
            a[i] = a[u] = true;
        } else if (protocol[i] == 1) {
            mark[i] = mark[u];
            if (a[u]) {
                join(i, u);
                a[i] = true;
            }
        } else assert(false);
    }

    int ans = 0;
    for (int r=0; r<n; ++r) {
        ct[0] = 0;
        ct[1] = 0;
        for (int i=0; i<n; ++i) {
            if (root(i) == r) {
                ++ct[mark[i]];
            }
        }

        ans += max(ct[0], ct[1]);
    }

    return ans;
}

int findSample(int n, int confidence[], int host[], int protocol[]) {
    int type[3] = {0, 0, 0};
    for (int i=1; i<n; ++i) {
        ++type[protocol[i]];
    }
    if (n <= 10) {
        return solve1(n, confidence, host, protocol);
    } else if (type[0] == 0 && type[2] == 0) {
        return solve2(n, confidence, host, protocol);
    } else if (type[0] == 0 && type[1] == 0) {
        return solve3(n, confidence, host, protocol);
    } else if (type[1] == 0 && type[2] == 0) {
        return solve4(n, confidence, host, protocol);
    } else if (type[2] == 0) {
        return solve5(n, confidence, host, protocol);
    } else {
        return 8;
    }
}
