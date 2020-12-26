/*
ID: zhongbr1
TASK: shopping
LANG: C++14
*/

//shopping.cpp created at 12/22/20 17:28:31

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define fi first
#define se second

typedef pair<int,int> pii;

const int MS = 105;
const int INIT = 1001001001;

struct Offer {
    map<int,int> items;
    int cost;
};

int S, B;
Offer offer[MS];

int code[5];

int pack(const map<int,int>& m) {
    int state = 0;
    for (int i=0; i<B; ++i) {
        state <<= 3;
        auto it = m.find(code[i]);
        if (it != m.end()) {
            state += it->second;
        }
    }
    return state;
}

map<int,int> unpack(int state) {
    map<int,int> m;
    for (int i=B-1; i>=0; --i) {
        m[code[i]] = state & 7;
        state >>= 3;
    }
    assert(state == 0);

    return m;
}

int dist[1 << 16];

int main() {
    freopen("shopping.in", "r", stdin);
    freopen("shopping.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> S;
    for (int i=0; i<S; ++i) {
        int n;
        cin >> n;

        for (int j=0; j<n; ++j) {
            int c, k;
            cin >> c >> k;
            offer[i].items[c] = k;
        }
        cin >> offer[i].cost;
    }

    map<int,int> target;
    cin >> B;
    for (int i=0; i<B; ++i) {
        int c, k, p;
        cin >> c >> k >> p;
        code[i] = c;
        offer[S+i].items[c] = 1;
        offer[S+i].cost = p;

        target[c] = k;
    }
    S += B;

    fill(dist, dist+(1 << 16), INIT);
    const int target_state = pack(target);

    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.emplace(0, 0);
    dist[0] = 0;

    while (pq.size() > 0) {
        const pii cur = pq.top(); pq.pop();

        if (cur.se == target_state) {
            cout << cur.fi << endl;
            return 0;
        }
        
        if (dist[cur.se] < cur.fi) continue;

        for (int i=0; i<S; ++i) {
            map<int,int> nitem = unpack(cur.se);
            const int ncost = cur.fi + offer[i].cost;
            bool ok = true;
            for (const pii& p: offer[i].items) {
                nitem[p.fi] += p.se;
                if (nitem[p.fi] > target[p.fi]) {
                    ok = false;
                    break;
                }
            }
            if (!ok) continue;

            const int state = pack(nitem);
            if (dist[state] > ncost) {
                dist[state] = ncost;
                pq.emplace(ncost, state);
            }
        }
    }

    assert(false);
}
