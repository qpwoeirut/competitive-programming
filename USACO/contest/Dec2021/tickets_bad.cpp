#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

using pii=pair<int,int>;
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
bool done[MN];

void dijkstra(ll d[]) {
    fill(done, done+K, false);
    for (int _=0; _<K; ++_) {
        ll min_val = INF;
        int idx = -1;
        for (int i=0; i<K; ++i) {
            if (min_val > d[i] && !done[i]) {
                min_val = d[i];
                idx = i;
            }
        }
        if (idx == -1) break;
        done[idx] = true;

        for (int i=0; i<K; ++i) {
            if (d[i] > dist[idx][i] + d[idx]) {
                d[i] = dist[idx][i] + d[idx];
            }
        }
    }
}

ll dst[MN];
ll dijkstra2(const int start) {
    fill(dst, dst+K, INF);
    dst[start] = 0;
    fill(done, done+K, false);
    ll best = INF;
    for (int _=0; _<K; ++_) {
        ll min_val = INF;
        int idx = -1;
        for (int i=0; i<K; ++i) {
            if (min_val > dst[i] && !done[i]) {
                min_val = dst[i];
                idx = i;
            }
        }
        if (idx == -1) break;
        done[idx] = true;
        
        for (int i=0; i<K; ++i) {
            if (dst[i] > dist[idx][i] + dst[idx]) {
                dst[i] = dist[idx][i] + dst[idx];
            }
        }
        best = min(best, dst[idx] + d1[idx] + dn[idx]);
    }
    return best;
}

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

    for (int u=0; u<K; ++u) {
        d1[u] = dn[u] = INF;
        if (A[u].a == 0) d1[u] = 0;
        if (A[u].b == N-1) dn[u] = 0;
    }

    dijkstra(d1);
    dijkstra(dn);

    for (int i=0; i<N; ++i) {
        ll ans = INF;
        for (const int t: cpts[i]) {
            if (i == 0) {
                ans = min(ans, A[t].price + dn[t]);
            } else if (i == N-1) {
                ans = min(ans, A[t].price + d1[t]);
            } else {
                for (int u=0; u<K; ++u) {
                    ans = min(ans, A[t].price + dijkstra2(u));
                }
            }
        }
        cout << (ans == INF ? -1 : ans) << '\n';
    }
}

