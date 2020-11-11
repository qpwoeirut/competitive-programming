#include <bits/stdc++.h>
#include "grader.h"

using namespace std;

const int MN = 515;

int NN;
int dist[MN], ct[MN], sum[MN];
set<int> adj[MN];
int mem[MN], mem2[MN][MN];

void dfs(int node, int par) {
    for (auto it=adj[node].begin(); it!=adj[node].end(); ++it) {
        if (*it == par) continue;
        dist[*it] = dist[node] + 1;
        dfs(*it, node);
    }
    ++ct[dist[node]];
}

bool check(int mid) {
    if (mem[mid] != -1) return mem[mid];
    int qdist = lower_bound(sum, sum+NN, mid) - sum;
    vector<int> qnodes;
    for (int i=0; i<NN; ++i) {
        if (dist[i] <= qdist) {
            qnodes.emplace_back(i+1);
        }
    }
    //cerr << "mid,qnodes: " << mid; for (int i=0; i<qnodes.size(); ++i) { cerr << ' ' << qnodes[i]; } cerr << endl;
    mem[mid] = query(qnodes);
    return mem[mid];
}

vector<int> nodes, to_query;
bool check2(int start, int finish) {
    if (mem2[start][finish] != -1) return mem2[start][finish];
    int s = nodes.size();

    assert(finish <= to_query.size());
    nodes.insert(nodes.end(), to_query.begin() + start, to_query.begin() + finish);
    mem2[start][finish] = query(nodes);
    nodes.resize(s);
    return mem2[start][finish];
}

int findEgg (int n, vector<pair<int,int>> bridges) {
    NN = n;
    //cerr << "NN: " << N << endl;
    for (int i=0; i<MN; ++i) {
        dist[i] = ct[i] = sum[i] = 0;
        adj[i].clear();
        mem[i] = -1;
        for (int j=0; j<MN; ++j) {
            mem2[i][j] = -1;
        }
    }
    nodes.clear();
    to_query.clear();
    for (int i=0; i<bridges.size(); ++i) {
        int u = bridges[i].first, v = bridges[i].second;
        --u; --v;
        adj[u].emplace(v);
        adj[v].emplace(u);
    }

    dist[0] = 0;
    dfs(0, -1);
    sum[0] = ct[0];
    for (int i=1; i<NN; ++i) {
        sum[i] = sum[i-1] + ct[i];
    }

    int lo = 1, hi = NN+1; 
    while (lo < hi) {
        int mid = (lo + hi) >> 1;
        if (!check(mid)) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    int egg_depth = lower_bound(sum, sum+NN, lo) - sum;
    //cerr << "depth: " << egg_depth << endl;

    for (int i=0; i<NN; ++i) {
        //cerr << "i: " << i << endl;
        if (dist[i] < egg_depth) nodes.emplace_back(i+1);
        if (dist[i] == egg_depth) to_query.emplace_back(i+1);
    }

    lo = 0, hi = to_query.size();
    while (lo < hi) {
        int mid = (lo + hi) >> 1;
        //cerr << "mid: " << mid << endl;
        if (!check2(lo, mid+1)) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    //cerr << "lo: " << lo << endl;
    assert(lo < to_query.size());
    return to_query[lo];
}
/*
16
1 2
1 3
1 4
1 5
1 6
1 7
1 8
1 9
1 10
1 11
1 12
1 13
1 14
1 15
1 16
16
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16

16
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 10
10 11 
11 12 
12 13
13 14
14 15
15 16
16
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16

16
1 2
2 3
3 4
4 5
4 6
4 7
4 8
4 9
4 10
4 11 
4 12 
4 13
13 14
14 15
15 16
16
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
*/
