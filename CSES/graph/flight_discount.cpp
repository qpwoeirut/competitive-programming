#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pll = pair<ll,ll>;
#define f first
#define s second

// create a struct to store data in a priority_queue
struct Item {
    int node;
    ll cost;
    bool discount;

    Item(int _node, ll _cost, bool _discount) {
        node = _node;
        cost = _cost;
        discount = _discount;
    }

    inline const bool operator<(const Item& other) const {
        if (discount == other.discount) {
            return cost > other.cost;
        }
        return discount > other.discount;
    }
};

const int MN = 100005;

int N, M;
vector<pll> adj[MN];
ll dist[MN][2];
// dist[i][0] represents the shortest distance without discount
// dist[i][1] represents the shortest distance with a discount

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M;
    for (int i=0; i<M; ++i) {
        ll u, v, c;
        cin >> u >> v >> c;
        --u; --v;
        adj[u].emplace_back(v, c);
    }

    // initialize dist
    for (int i=0; i<N; ++i) {
        dist[i][0] = dist[i][1] = 1e18;
    }

    priority_queue<Item> pq;
    pq.emplace(0, 0, false);

    while (pq.size() > 0) {
        Item cur = pq.top(); pq.pop();

        if (cur.node == N-1 && cur.discount) {
            cout << cur.cost << '\n';
            return 0;
        }

        for (pll nxt: adj[cur.node]) {
            // travel without a discount
            if (dist[nxt.f][cur.discount] > cur.cost + nxt.s) {
                dist[nxt.f][cur.discount] = cur.cost + nxt.s;
                pq.emplace(nxt.f, dist[nxt.f][cur.discount], cur.discount);
            }
            // if we haven't used the discount yet, try using it on this edge
            if (cur.discount == false) {
                if (dist[nxt.f][true] > cur.cost + nxt.s / 2) {
                    dist[nxt.f][true] = cur.cost + nxt.s / 2;
                    pq.emplace(nxt.f, dist[nxt.f][true], true);
                }
            }
        }
    }

    // it is guaranteed that we can reach our destination, so this should never happen
    assert(false);
}
