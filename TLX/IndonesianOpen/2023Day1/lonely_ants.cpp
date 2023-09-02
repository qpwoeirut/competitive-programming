//lonely_ants.cpp created at 08/29/23 17:20:40

#include <bits/stdc++.h>

using namespace std;
using pii=pair<int,int>;
using ll=long long;

const int MN = 100001;

ll N, M;
vector<int> adj[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M;
    for (int i=0; i<M; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i=0; i<N; ++i) {
        sort(adj[i].begin(), adj[i].end());
    }

    ll ans = 0;
    for (int u=0; u<N; ++u) {
        vector<pii> intervals;

        const int mid = lower_bound(adj[u].begin(), adj[u].end(), u) - adj[u].begin();
        for (int i=max(0, mid - 2); i < mid + 2; ++i) {
            for (int j=i+1; j < mid + 2 && j < adj[u].size(); ++j) {
                intervals.emplace_back(min(u, adj[u][i]), max(u, adj[u][j]));
            }
        }

        for (const int v: adj[u]) {
            const int idx = lower_bound(adj[v].begin(), adj[v].end(), u) - adj[v].begin();

            if (idx - 1 >=            0) intervals.emplace_back(min(min(u, v), adj[v][idx - 1]), max(max(u, v), adj[v][idx - 1]));
            if (idx + 1 < adj[v].size()) intervals.emplace_back(min(min(u, v), adj[v][idx + 1]), max(max(u, v), adj[v][idx + 1]));
        }

        sort(intervals.begin(), intervals.end());

        vector<pii> candidates;
        for (const pii& interval: intervals) {
            while (!candidates.empty() && candidates.back().first <= interval.first && interval.second <= candidates.back().second) {
                candidates.pop_back();
            }
            if (candidates.empty() || (candidates.back().first < interval.first && candidates.back().second < interval.second)) {
                candidates.push_back(interval);
            }
        }

        int lo = 0;
        ll lonely = (u + 1LL) * (N - u);
        for (int i=0; i<candidates.size(); ++i) {
            lonely -= (candidates[i].first - lo + 1LL) * (N - candidates[i].second);
            lo = candidates[i].first + 1;
        }

        ans += lonely;

        //cerr << u << ' ' << lonely << endl;
        //for (const pii& c: candidates) cerr << '[' << c.first << ',' << c.second << "] ";
        //cerr << endl;
    }
    cout << ans << '\n';
}

