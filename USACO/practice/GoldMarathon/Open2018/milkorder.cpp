#include <bits/stdc++.h>

using namespace std;

#define val first
#define nxt second

typedef pair<int,int> pii;

const int MN = 100005;

int N, M;
set<pii> adj[MN];

int deg[MN];
vector<int> ans;
bool order(const int limit, bool add) {
    ans = vector<int>();

    fill(deg, deg+N, 0);
    for (int i=0; i<N; ++i) {
        for (auto p: adj[i]) {
            if (p.val <= limit) {
                ++deg[p.nxt];
            }
        }
    }

    priority_queue<int, vector<int>, greater<int> > pq;
    for (int i=0; i<N; ++i) {
        if (deg[i] == 0) pq.push(i);
    }

    int ct = 0;
    while (pq.size() > 0) {
        int cur = pq.top(); pq.pop();
        ++ct;

        if (add) ans.push_back(cur);
        for (auto p: adj[cur]) {
            if (p.val <= limit) {
                if (--deg[p.nxt] == 0) {
                    pq.push(p.nxt);
                }
            }
        }
    }

    return ct == N;
}

int main() {
    freopen("milkorder.in", "r", stdin);
    freopen("milkorder.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M;
    for (int i=0; i<M; ++i) {
        int x;
        cin >> x;
        int prev = -1;
        for (int j=0; j<x; ++j) {
            int cur;
            cin >> cur;
            --cur;
            if (prev != -1) {
                adj[prev].emplace(i, cur);
            }
            prev = cur;
        }
    }

    int lo = 0, hi = M-1;
    while (lo < hi) {
        int mid = (lo + hi + 1) >> 1;
        if (order(mid, false)) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }

    order(lo, true);
    //cerr << lo << endl << ans.size() << endl;
    for (int i=0; i<ans.size(); ++i) {
        if (i) cout << ' ';
        cout << ans[i] + 1;
    }
    cout << endl;
}
