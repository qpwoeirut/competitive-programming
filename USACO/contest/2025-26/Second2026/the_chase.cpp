#include <bits/stdc++.h>

using namespace std;

const int MN = 500005;

int N, F;
int A[MN];
int S[MN];

int cycle[MN];
void detect(int u) {
    if (cycle[u] == -2) cycle[u] = -1;
    else if (cycle[u] == -1) cycle[u] = 1;
    else if (cycle[u] == 0 || cycle[u] == 1) return;

    detect(A[u]);
    if (cycle[u] == -1) cycle[u] = 0;
}

int dist[MN];
void follow(int u, int d) {
    if (dist[u] != -2 && d >= 0) return;
    dist[u] = d;
    follow(A[u], d + 1);
}

const int LG = 20;
int jmp[LG+1][MN];

bitset<MN> vis;
int forward(int u) {
    //cerr << "u=" << u << "dist=" << dist[u] << endl;
    if (dist[u] >= 0) return dist[u] - 1;
    if (vis[u]) return -1;
    vis[u] = true;

    const int val = forward(A[u]);
    dist[u] = max(-1, val);

    return val - 1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> F;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
        --A[i];
    }
    for (int i=0; i<F; ++i) {
        cin >> S[i];
        --S[i];
    }

    copy(A, A+N, jmp[0]);
    for (int i=1; i<=LG; ++i) {
        for (int j=0; j<N; ++j) {
            jmp[i][j] = jmp[i-1][jmp[i-1][j]];
        }
    }

    fill(dist, dist+N, -2);
    for (int i=0; i<F; ++i) {
        dist[S[i]] = -1;
    }
    for (int i=0; i<F; ++i) {
        follow(S[i], -1);
    }

    fill(cycle, cycle+N, -2);
    for (int i=0; i<N; ++i) {
        detect(i);
    }

    set<int> covered;
    for (int i=0; i<F; ++i) {
        covered.insert(jmp[LG][S[i]]);
        //cerr << S[i] << ' ' << jmp[LG][S[i]] << endl;
    }
    for (int i=0; i<N; ++i) {
        //cerr << i << ' ' << dist[i] << ' ' << cycle[i] << endl;

        if (dist[i] < 0) continue;
        int u = i;
        int d = (1 << LG) - dist[i];
        for (int j=LG; j>=0; --j) {
            if (d >= (1 << j)) {
                d -= 1 << j;
                u = jmp[j][u];
            }
        }
        if (covered.count(u)) {
            dist[i] = -1;
            //cerr << "reset i=" << i << endl;
        }
    }
    for (int i=0; i<N; ++i) {
        if (dist[i] == -1) {
            forward(i);
        }
        //cerr << i << ' ' << dist[i] << ' ' << cycle[i] << endl;
    }

    for (int i=0; i<N; ++i) {
        cout << dist[i] << '\n';
    }
}
/*
3 1
2 3 2
2

3 2
2 3 2
1 2

8 2
2 3 4 5 6 7 8 7
1 7

8 2
2 3 4 5 6 7 8 7
1 4
*/
