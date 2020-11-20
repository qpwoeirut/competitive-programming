#include <bits/stdc++.h>

using namespace std;

#define x first
#define y second

typedef long long ll;
typedef pair<ll,ll> Cow;

const int MN = 1005;
const ll INIT = 1e18;

int N;
Cow A[MN];
bool done[MN];
ll dist[MN];

inline ll get_dist(const int i, const int j) {
    return (A[i].x - A[j].x) * (A[i].x - A[j].x) + (A[i].y - A[j].y) * (A[i].y - A[j].y);
}

int main() {
    freopen("moocast.in", "r", stdin);
    freopen("moocast.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i].x >> A[i].y;
        dist[i] = INIT;
    }

    ll ans = 0;
    dist[0] = 0;
    for (int i=0; i<N; ++i) {
        ll idx = -1, best = INIT;
        for (int j=0; j<N; ++j) {
            if (dist[j] == INIT || done[j]) continue;
            if (best > dist[j]) {
                best = dist[j];
                idx = j;
            }
        }

        assert(idx != -1);
        done[idx] = true;
        for (int j=0; j<N; ++j) {
            if (done[j]) continue;
            dist[j] = min(dist[j], get_dist(idx, j));
        }
        ans = max(ans, dist[idx]);
        //cerr << idx << ' ' << dist[idx] << endl;
    }

    cout << ans << endl;
}
