//295b.cpp created at 09/09/20 21:06:13

#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "qpwoeirut/debug.h"
#else
#define debug(x)
#define debug1(x, sz)
#define debug2(x, sz1, sz2)
#define debug3(x, sz1, sz2, sz3)
#endif

typedef long long ll;

const ll MN = 501;

ll N;
ll dist[MN][MN];
ll A[MN], ans[MN];
bool in[MN];
bool done[MN];
void dijkstra(ll start, ll ct) {
    fill(done, done+N, false);
    debug(start);
    for (int i=0; i<N; ++i) {
        int nxt = -1;
        for (int j=0; j<N; ++j) {
            if (in[j] && !done[j] && (nxt == -1 || dist[start][nxt] > dist[start][j])) {
                nxt = j;
            }
        }
        debug(nxt);
        if (nxt == -1) break;

        for (int j=0; j<N; ++j) {
            dist[start][j] = min(dist[start][j], dist[start][nxt] + dist[nxt][j]);
        }
        done[nxt] = true;
    }
}

void rdijkstra(ll start, ll ct) {
    fill(done, done+N, false);
    debug(start);
    for (int i=0; i<N; ++i) {
        int nxt = -1;
        for (int j=0; j<N; ++j) {
            if (in[j] && !done[j] && (nxt == -1 || dist[nxt][start] > dist[j][start])) {
                nxt = j;
            }
        }
        debug(nxt);
        if (nxt == -1) break;

        for (int j=0; j<N; ++j) {
            dist[j][start] = min(dist[j][start], dist[j][nxt] + dist[nxt][start]);
        }
        done[nxt] = true;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N;

    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            cin >> dist[i][j];
        }
    }

    for (int i=N-1; i>=0; --i) {
        cin >> A[i];
        --A[i];
    }

    for (int k=0; k<N; ++k) {
        in[A[k]] = true;
        dijkstra(A[k], k);
        rdijkstra(A[k], k);

        debug2(dist, N, N);
        for (int i=0; i<N; ++i) {
            if (!in[i]) continue;
            for (int j=0; j<N; ++j) {
                if (!in[j]) continue;
                if (dist[i][j] > dist[i][A[k]] + dist[A[k]][j]) {
                    dist[i][j] = dist[i][A[k]] + dist[A[k]][j];
                }
                ans[k] += dist[i][j];
            }
        }
        debug2(dist, N, N);
        debug1(in, N);
    }

    reverse(ans, ans+N);
    for (int i=0; i<N; i++) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << endl;
}
