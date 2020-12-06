#include <bits/stdc++.h>

using namespace std;

#define dst first
#define pos second

typedef pair<int,int> pii;
typedef long long ll;

const int MN = 1001;
const int INIT = 1001001001;

struct Pipe {
    int from, to;
    int cost, flow;
    Pipe(int _from, int _to, int _cost, int _flow) {
        from = _from;
        to = _to;
        cost = _cost;
        flow = _flow;
    }
};

bool chmn(int& a, const int b) {
    if (a>b) {
        a=b;
        return true;
    }
    return false;
}
void chmx(ll& a, const ll b) {if (a<b) a=b;}

int N, M;
vector<Pipe> adj[MN];

int dist[MN];
ll solve(const ll flow) {
    fill(dist, dist+N, INIT);
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.emplace(0, 0);
    dist[0] = 0;

    while (pq.size() > 0) {
        pii cur = pq.top();
        pq.pop();

        if (cur.pos == N-1) {
            ll cost = cur.dst;
            ll f = flow * 1e6;
            return f / cost;
        }

        for (const Pipe& p: adj[cur.pos]) {
            if (p.flow < flow) continue;
            if (chmn(dist[p.to], dist[p.from] + p.cost)) {
                pq.emplace(dist[p.to], p.to);
            }
        }
    }

    return -1;
}

int main() {
    freopen("pump.in", "r", stdin);
    freopen("pump.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M;
    for (int i=0; i<M; ++i) {
        int from, to, cost, flow;
        cin >> from >> to >> cost >> flow;
        --from; --to;
        adj[from].emplace_back(from, to, cost, flow);
        adj[to].emplace_back(to, from, cost, flow);
    }

    ll ans = 0;
    for (int flow=1; flow<=1000; ++flow) {
        chmx(ans, solve(flow));
    }

    cout << ans << endl;
}
