#include "plants.h"
#include <bits/stdc++.h>

using namespace std;

int N;
vector<set<int>> adj;
int tbl[200001][25];
void init(int k, vector<int> r) {
    N = r.size();
    adj = vector<set<int>>(N, set<int>());
    for (int i=1; i<23; ++i) {
        for (int j=0; j<N; ++j) {
            tbl[j][i] = -1;
        }
    }

    for (int i=0; i<N; ++i) {
        int u = i, v = (i+1) % N;
        if (r[u] == 0) {
            adj[u].insert(v);
            tbl[u][0] = v;        
        } else {
            adj[v].insert(u);
            tbl[v][0] = u;
        }
    }

    for (int i=0; i<23; ++i) {
        for (int j=0; j<N; ++j) {
            if (tbl[j][i] == -1) continue;
            tbl[j][i+1] = tbl[tbl[j][i]][i];
        }
    }
}

int compare_plants(int x, int y) {

}
