//movie_festival_ii.cpp created at 12/16/20 21:43:28

#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

typedef pair<int,int> pii;

const int MN = 200005;

int N, K;
pii A[MN];

inline const bool cmps(const pii& a, const pii& b) {
    if (a.se == b.se) return a.fi < b.fi;
    return a.se < b.se;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> K;
    for (int i=0; i<N; ++i) {
        cin >> A[i].fi >> A[i].se;
    }
    sort(A, A+N, cmps);

    multiset<int> cur;
    for (int i=0; i<K; ++i) {
        cur.insert(0);
    }

    int ans = 0;
    for (int i=0; i<N; ++i) {
        auto it = cur.upper_bound(A[i].fi);
        if (it == cur.begin()) continue;
        --it;
        ++ans;
        cur.erase(it);
        cur.insert(A[i].se);
    }

    cout << ans << endl;
}
