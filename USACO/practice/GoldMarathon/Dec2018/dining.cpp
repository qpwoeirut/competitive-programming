#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

typedef pair<int,int> pii;

const int MN = 50001;
const int INIT = 1001001001;

struct Item {
    int node;
    int dst;
    bool eat;

    Item(const int _node, const int _dst, const bool _eat) {
        node = _node;
        dst = _dst;
        eat = _eat;
    }

    inline const bool operator<(const Item& other) const {
        if (dst == other.dst) {
            if (eat == other.eat) {
                return node > other.node;
            }
            return eat > other.eat;
        }
        return dst > other.dst;
    }
};

int N, M, K;
int A[MN];
bool ans[MN];
vector<pii> adj[MN];

int dist[2][MN];

bool chmn(int& a, const int b) {
    if (a > b) {
        a = b;
        return true;
    }
    return false;
}

int main() {
    freopen("dining.in", "r", stdin);
    freopen("dining.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M >> K;
    for (int i=0; i<M; ++i) {
        int u, v, t;
        cin >> u >> v >> t;

        --u; --v;
        adj[u].emplace_back(v, t);
        adj[v].emplace_back(u, t);
    }

    for (int i=0; i<K; ++i) {
        int idx, val;
        cin >> idx >> val;

        --idx;
        A[idx] = max(A[idx], val);
    }

    for (int i=0; i<N; ++i) {
        dist[0][i] = dist[1][i] = INIT;
    }          

    priority_queue<Item> pq;
    pq.emplace(N-1, 0, false);
    dist[0][N-1] = 0;

    while (pq.size() > 0) {
        const Item cur = pq.top(); pq.pop();

        if (cur.dst > dist[cur.eat][cur.node]) {
            continue;
        }
        for (const pii& p: adj[cur.node]) {
            if (chmn(dist[cur.eat][p.fi], cur.dst + p.se)) {
                pq.emplace(p.fi, dist[cur.eat][p.fi], cur.eat);
            }
        }

        if (cur.eat == false && A[cur.node] > 0 && chmn(dist[1][cur.node], cur.dst - A[cur.node])) {
            pq.emplace(cur.node, dist[1][cur.node], true);
        }
    }

    for (int i=0; i<N-1; ++i) {
        cout << (dist[0][i] >= dist[1][i]) << '\n';
    }
}

