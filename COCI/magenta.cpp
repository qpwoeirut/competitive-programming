//magenta.cpp created at 02/13/21 07:09:19

#include <bits/stdc++.h>

using namespace std;

const int MN = 100005;
const int INIT = 1001001001;

int N;
set<int> adj[2][MN];

int dist[2][MN];
void dfs(const int u, const int par, const int idx) {
    for (const int v: adj[idx][u]) {
        if (v == par) continue;
        dist[idx][v] = dist[idx][u] + 1;
        dfs(v, u, idx);
    }
}

int dist2[2][MN];
void dfs2(const int u, const int par, const int idx) {
    for (int i=0; i<2; ++i) {
        for (const int v: adj[i][u]) {
            if (v == par) continue;
            dist2[idx][v] = dist2[idx][u] + 1;
            dfs(v, u, idx);
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    cin >> N;
    int a, b;
    cin >> a >> b;
    --a; --b;

    for (int i=0; i<N-1; ++i) {
        int x, y;
        string color;
        cin >> x >> y >> color;
        --x; --y;

        if (color == "plava" || color == "magenta") {
            adj[0][x].insert(y);
            adj[0][y].insert(x);
        }
        if (color == "crvena" || color == "magenta") {
            adj[1][x].insert(y);
            adj[1][y].insert(x);
        }
    }

    fill(dist[0], dist[0] + MN, INIT);
    fill(dist[1], dist[1] + MN, INIT);
    dist[0][a] = 0;
    dfs(a, -1, 0);
    dist[1][b] = 0;
    dfs(b, -1, 1);

    const int D = min(dist[0][b], dist[1][a]);
    if (D == INIT) {
        cout << "Magenta" << endl;
        return 0;
    }

    fill(dist2[0], dist2[0] + MN, INIT);
    fill(dist2[1], dist2[1] + MN, INIT);
    dist2[0][a] = 0;
    dfs2(a, -1, 0);
    dist2[1][b] = 0;
    dfs2(b, -1, 1);

    const int winner = D & 1;
    //cerr << winner << endl;
    for (int i=0; i<N; ++i) {
        //cerr << i << ' ' << adj[!winner][i].size() << ' ' << dist[0][i] << ' ' << dist[1][i] << ' ' << dist2[0][i] << ' ' << dist2[1][i] << endl;
        if (adj[!winner][i].size() >= 2 && dist[winner][i] == INIT && dist[!winner][i] != INIT && make_pair(dist2[winner][i], !winner) > make_pair(dist2[!winner][i], !!winner)) {
            cout << "Magenta" << endl;
            return 0;
        }
    }
    cout << (winner ? "Marin" : "Paula") << endl;
}

/*
3
1 3
3 2 magenta
2 1 magenta

5
3 5
1 2 magenta
1 3 magenta
2 4 plava
2 5 crvena

5
1 4
2 1 plava
1 3 crvena
5 2 plava
4 1 magenta
*/
