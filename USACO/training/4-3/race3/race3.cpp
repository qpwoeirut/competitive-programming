/*
ID: zhongbr1
TASK: race3
LANG: C++14
*/

//race3.cpp created at 12/25/20 14:32:05

#include <bits/stdc++.h>

using namespace std;

const int MN = 55;

int N;
set<int> adj[2][MN];

bool visited[MN];
void dfs(int u, int removed, bool rev) {
    if (visited[u]) return;
    visited[u] = true;
    //cerr << u << ' ' << removed << endl;

    for (const int& v: adj[rev][u]) {
        if (v == removed) continue;
        dfs(v, removed, rev);
    }
}

int main() {
    freopen("race3.in", "r", stdin);
    freopen("race3.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    int ending = -2;
    while (ending != -1) {
        int x;
        cin >> x;
        while (x >= 0) {
            adj[0][N].insert(x);
            adj[1][x].insert(N);
            cin >> x;
        }
        ending = x;
        ++N;
    }
    --N;
    cerr << N << endl;

    //for (int i=0; i<N; ++i) { for (const int x: adj[i]) cerr << x << ' '; cerr << endl; }

    vector<int> ans1, ans2;
    for (int i=1; i+1<N; ++i) {
        //cerr << i << endl;
        fill(visited, visited+N, false);
        dfs(0, i, 0);
        if (!visited[N-1]) ans1.push_back(i);
    }

    for (const int u: ans1) {
        bool ok = true;

        fill(visited, visited+N, false);
        dfs(0, u, 0);
        set<int> p1;
        for (int i=0; i<N; ++i) {
            if (visited[i]) {
                p1.insert(i);
            }
        }
        fill(visited, visited+N, false);
        dfs(u, u, 1);
        for (int i=0; i<N; ++i) {
            if (i == u) continue;
            if (visited[i] < p1.count(i)) {
                ok = false;
            }
        }


        fill(visited, visited+N, false);
        dfs(u, u, 0);
        set<int> p2;
        for (int i=0; i<N; ++i) {
            if (visited[i]) {
                p2.insert(i);
            }
        }
        fill(visited, visited+N, false);
        dfs(N-1, u, 1);
        for (int i=0; i<N; ++i) {
            if (i == u) continue;
            if (visited[i] < p2.count(i)) {
                ok = false;
            }
        }

        for (int i=0; i<N; ++i) {
            if (i == u) continue;
            if (p1.count(i) + p2.count(i) != 1) {
                ok = false;
            }
        }
        
        if (ok) {
            ans2.push_back(u);
        }
    }

    cout << ans1.size();
    for (const int x: ans1) {
        cout << ' ' << x;
    }
    cout << endl;
    cout << ans2.size();
    for (const int x: ans2) {
        cout << ' ' << x;
    }
    cout << endl;
}
    
