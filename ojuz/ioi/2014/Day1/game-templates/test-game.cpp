#include <bits/stdc++.h>
#include "game.h"

using namespace std;

#define FI first
#define SE second

typedef pair<int,int> pii;

const int N = 5;
set<int> adj[N];
bool visited[N];
int dfs(int cur) {
    if (visited[cur]) return 0;
    visited[cur] = true;
    int ans = 1;
    for (set<int>::iterator it=adj[cur].begin(); it!=adj[cur].end(); ++it) {
        ans += dfs(*it);
    }
    return ans;
}
int count(int start) {
    fill(visited, visited+N, false);
    return dfs(start);
}


int main() {
    vector<pii> edges;
    for (int i=0; i<N; ++i) {
        for (int j=i+1; j<N; ++j) {
            edges.emplace_back(i, j);
        }
    }

    do {
        fill(adj, adj+N, set<int>());
        initialize(N);
        int prev, cur = count(0);
        for (int i=0; i<edges.size(); ++i) {
            int u = edges[i].FI, v = edges[i].SE;
            if (hasEdge(u, v)) {
                adj[u].insert(v);
                adj[v].insert(u);
            }
            prev = cur;
            cur = count(0);
        }

        if (prev == N || cur != N) {
            cout << prev << ' ' << cur << endl;
            cout << N << endl;
            for (int i=0; i<edges.size(); ++i) {
                cout << edges[i].FI << ' ' << edges[i].SE << endl;
            }
            cout << endl;
            return 0;
        }
    } while (next_permutation(edges.begin(), edges.end()));
}

/*
g++-10 -DEVAL -O2 -std=c++11 -o test_game test-game.cpp game.cpp
*/
