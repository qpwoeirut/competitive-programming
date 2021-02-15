//shortest_routes_ii.cpp created at 12/18/20 23:59:13

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MN = 502;
const ll INIT = 1e18;

int N, M, Q;
ll mat[MN][MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M >> Q;
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            mat[i][j] = INIT;
        }
        mat[i][i] = 0;
    }

    for (int i=0; i<M; ++i) {
        ll u, v, d;
        cin >> u >> v >> d;
        --u; --v;
        mat[u][v] = mat[v][u] = min(mat[u][v], d);
    }
    
    for (int k=0; k<N; ++k) {
        for (int i=0; i<N; ++i) {
            for (int j=0; j<N; ++j) {
                mat[i][j] = min(mat[i][j], mat[i][k] + mat[k][j]);
            }
        }
    }

    for (int i=0; i<Q; ++i) {
        int s, f;
        cin >> s >> f;
        --s; --f;
        cout << (mat[s][f] == INIT ? -1 : mat[s][f]) << '\n';
    }
}

