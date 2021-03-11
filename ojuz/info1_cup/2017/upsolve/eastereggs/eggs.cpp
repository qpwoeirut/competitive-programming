//eggs.cpp created at 03/04/21 10:13:42

#include <bits/stdc++.h>
#include "grader.h"

using namespace std;

#define fi first
#define se second

typedef pair<int,int> pii;

const int MN = 512;

set<int> adj[MN];
bool visited[MN];

int findEgg(int N, vector<pii> edges) {
    for (pii& p: edges) {
        --p.fi; --p.se;
        adj[p.fi].insert(p.se);
        adj[p.se].insert(p.fi);
    }

    set<int> candidates;
    for (int i=0; i<N; ++i) candidates.insert(i);

    while (candidates.size() > 1) {
        vector<int> to_query;
        set<int> cur;
        
        fill(visited, visited+N, false);

        queue<int> q;
        int start = *candidates.begin();
        q.push(start);
        visited[start] = true;
        while (q.size() > 0 && (cur.size() << 1) < candidates.size()) {
            const int u = q.front(); q.pop();
            to_query.push_back(u+1);
            if (candidates.count(u)) cur.insert(u);

            for (const int v: adj[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }

        int resp = query(to_query);

        if (resp == 0) {
            for (const int x: cur) {
                candidates.erase(x);
            }
        } else if (resp == 1) {
            candidates = cur;
        } else assert(false);
    }

    assert(candidates.size() == 1);

    return *candidates.begin() + 1;
}

