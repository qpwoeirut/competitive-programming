#include <bits/stdc++.h>

using namespace std;

using ll=long long;

const int MN = 1000;
const ll INF = 1LL << 48; 

struct Ticket {
    int cpt;
    ll price;
    int a, b;
};

int N, K;
Ticket A[MN];
vector<int> cpts[MN];
ll dist[MN][MN];
ll d1[MN], dn[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> K;
    for (int i=0; i<K; ++i) {
        cin >> A[i].cpt >> A[i].price >> A[i].a >> A[i].b;
        --A[i].cpt;
        --A[i].a; --A[i].b;
        cpts[A[i].cpt].push_back(i);
    }

    for (int u=0; u<K; ++u) {
        for (int v=0; v<K; ++v) {
            dist[u][v] = INF;
        }
        dist[u][u] = 0;
    }

    for (int ticket=0; ticket<K; ++ticket) {
        for (int i=A[ticket].a; i<=A[ticket].b; ++i) {
            for (const int t: cpts[i]) {
                dist[ticket][t] = min(dist[ticket][t], A[t].price);
            }
        }
    }
    for (int i=0; i<N; ++i) {
        for (const int u: cpts[i]) {
            for (const int v: cpts[i]) {
                dist[u][v] = min(dist[u][v], A[v].price);
            }
        }
    }

    for (int i=0; i<K; ++i) {
        for (int j=0; j<K; ++j) {
            for (int k=0; k<K; ++k) {
                if (dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    for (int u=0; u<K; ++u) {
        d1[u] = dn[u] = INF;
        for (int v=0; v<K; ++v) {
            if (A[v].a == 0) d1[u] = min(d1[u], dist[u][v]);
            if (A[v].b == N-1) dn[u] = min(dn[u], dist[u][v]);
        }
    }

    for (int i=0; i<N; ++i) {
        ll ans = INF;
        for (const int t: cpts[i]) {
            for (int u=0; u<K; ++u) {
                if (i == 0) {
                    ans = min(ans, A[t].price + dist[t][u] + dn[u]);
                } else if (i == N-1) {
                    ans = min(ans, A[t].price + dist[t][u] + d1[u]);
                } else {
                    ans = min(ans, A[t].price + dist[t][u] + d1[u] + dn[u]);
                }
            }
        }
        cout << (ans == INF ? -1 : ans) << '\n';
    }
}

