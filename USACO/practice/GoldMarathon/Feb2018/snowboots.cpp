#include <bits/stdc++.h>

using namespace std;

#define val first
#define pos second

typedef pair<int,int> pii;

struct Boot {
    int s, d;
    int idx;

    inline const bool operator<(const Boot& other) const {
        if (s == other.s) {
            if (d == other.d) {
                return idx < other.idx;
            }
            return d < other.d;
        }
        return s > other.s;
    }
};

const int MN = 100005;

int N, B;
int A[MN];

Boot query[MN];
bool ans[MN];

multiset<int> sizes;
int par[MN], sz[MN];
int root(int u) {
    if (par[u] != u) par[u] = root(par[u]);
    return par[u];
}
void join(int u, int v) {
    int ru = root(u), rv = root(v);
    if (ru == rv) return;
    assert(sz[u] > 0); assert(sz[ru] > 0);
    assert(sz[v] > 0); assert(sz[rv] > 0);

    if (sz[ru] < sz[rv]) swap(ru, rv);

    par[rv] = par[v] = ru;

    sizes.erase(sizes.find(sz[ru]));
    sizes.erase(sizes.find(sz[rv]));
    sz[ru] += sz[rv];
    sizes.insert(sz[ru]);
}

int main() {
    freopen("snowboots.in", "r", stdin);
    freopen("snowboots.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    priority_queue<pii> pq;
    cin >> N >> B;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
        pq.emplace(A[i], i);
    }
    for (int i=0; i<B; ++i) {
        cin >> query[i].s >> query[i].d;
        query[i].idx = i;
    }
    sort(query, query+B);

    for (int i=0; i<N; ++i) {
        par[i] = i;
        sz[i] = 0;
    }
    
    sizes.insert(-1);
    for (int i=0; i<B; ++i) {
        queue<int> q;
        while (pq.size() > 0 && pq.top().val > query[i].s) {
            pii cur = pq.top(); pq.pop();
            //cerr << cur.val << ' ' << cur.pos << endl;

            sz[cur.pos] = 1;
            sizes.insert(1);
            assert(cur.pos > 0 && cur.pos + 1 < N);

            q.push(cur.pos);
        }
        while (q.size() > 0) {
            int idx = q.front(); q.pop();
            //cerr << A[idx-1] << ' ' << A[idx+1] << ' ' << idx << endl;
            if (A[idx - 1] > query[i].s) {
                join(idx - 1, idx);
            }
            if (A[idx + 1] > query[i].s) {
                join(idx + 1, idx);
            }
        }

        ans[query[i].idx] = *sizes.rbegin() < query[i].d;
        //cerr << query[i].idx << ": "; for (auto it:sizes) cerr << it << ' '; cerr << endl;
        //for (int j=0; j<N; ++j) cerr << root(j) << ' '; cerr << endl;
    }

    for (int i=0; i<B; ++i) {
        cout << ans[i] << '\n';
    }
}
