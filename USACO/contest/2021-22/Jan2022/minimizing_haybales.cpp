#include <bits/stdc++.h>

using namespace std;

using pii=pair<int,int>;

#define fi first
#define se second
#define pb push_back

const int MN = 100005;

int N, K;
int A[MN];
int ans[MN];

vector<int> mn_adj[MN], mx_adj[MN];
int mn_ptr[MN], mx_ptr[MN];
bool mn_ok[MN], mx_ok[MN];
priority_queue<pii, vector<pii>, greater<pii>> pq;

void disconnect_mn(int v) {
    //cerr << "mn: " << v << ' ' << remaining[v] << endl;
    mn_ptr[v] = -1;
    mn_ok[v] = true;
    if (mn_ok[v] && mx_ok[v]) {
        pq.emplace(A[v], -v);
        //cerr << "adding " << A[v] << ' ' << -v << endl;
    }
    while (mn_adj[v].size() > 0) {
        disconnect_mn(mn_adj[v].back());
        mn_adj[v].pop_back();
    }
}

void disconnect_mx(int v) {
    //cerr << "mx: " << v << ' ' << remaining[v] << endl;
    mx_ptr[v] = -1;
    mx_ok[v] = true;
    if (mn_ok[v] && mx_ok[v]) {
        pq.emplace(A[v], -v);
        //cerr << "adding " << A[v] << ' ' << -v << endl;
    }
    while (mx_adj[v].size() > 0) {
        disconnect_mx(mx_adj[v].back());
        mx_adj[v].pop_back();
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> K;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }

    /*
    for (int i=0; i<N; ++i) {
        int mn = A[i], mx = A[i];
        int best = i;
        for (int j=i+1; j<N; ++j) {
            mn = min(mn, A[j]);
            mx = max(mx, A[j]);
            if (A[j] - mn <= K && mx - A[j] <= K && A[j] < A[best]) best = j;
        }
        for (; best>i; --best) swap(A[best-1], A[best]);

        //for (int j=0; j<N; ++j) { cerr << A[j] << ' '; } cerr << endl;
    }

    for (int i=0; i<N; ++i) {
        cout << A[i] << '\n';
    }

    return 0;
    */

    set<pii, greater<pii>> mn;
    set<pii> mx;
    for (int i=0; i<N; ++i) {
        mn_ptr[i] = mx_ptr[i] = -1;
        mn_ok[i] = mx_ok[i] = false;

        auto it = mn.emplace(A[i], i).fi; ++it;
        if (it != mn.end()) {
            mn_ptr[i] = it->se;
        }
        it = mx.emplace(A[i], -i).fi; ++it;
        if (it != mx.end()) {
            mx_ptr[i] = -(it->se);
        }

        it = mn.lower_bound(pii(A[i] - K, -1));
        if (it != mn.end()) {
            mn_adj[it->se].pb(i);
        } else mn_ok[i] = true;

        it = mx.lower_bound(pii(A[i] + K, 1));
        if (it != mx.end()) {
            mx_adj[-(it->se)].pb(i);
        } else mx_ok[i] = true;

        if (mn_ok[i] && mx_ok[i]) {
            //cerr << "start: " << A[i] << ' ' << -i << endl;
            pq.emplace(A[i], -i);
        }
    }

    /*
    for (int i=0; i<N; ++i) { cerr << mn_ptr[i] << ' '; } cerr << endl;
    for (int i=0; i<N; ++i) { cerr << mx_ptr[i] << ' '; } cerr << endl;
    for (int i=0; i<N; ++i) { cerr << remaining[i] << ' '; } cerr << endl;
    for (int i=0; i<N; ++i) { cerr << i << ':'; for (const int v: mn_adj[i]) { cerr << ' ' << v; } cerr << endl; }
    for (int i=0; i<N; ++i) { cerr << i << ':'; for (const int v: mx_adj[i]) { cerr << ' ' << v; } cerr << endl; }
    */
    
    int idx = 0;
    while (pq.size() > 0) {
        const pii cur = pq.top(); pq.pop();
        //cerr << "cur: " << cur.fi << ' ' << -cur.se << endl;
        ans[idx++] = cur.fi;
        const int i = -cur.se;

        if (mn_ptr[i] == -1) {
            while (mn_adj[i].size() > 0) {
                disconnect_mn(mn_adj[i].back());
                mn_adj[i].pop_back();
            }
        } else mn_adj[mn_ptr[i]].pb(i);
        if (mx_ptr[i] == -1) {
            while (mx_adj[i].size() > 0) {
                disconnect_mx(mx_adj[i].back());
                mx_adj[i].pop_back();
            }
        } else mx_adj[mx_ptr[i]].pb(i);
    }

    for (int i=0; i<N; ++i) {
        cout << ans[i] << '\n';
    }
}
