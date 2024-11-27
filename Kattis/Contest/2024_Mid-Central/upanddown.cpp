#include <bits/stdc++.h>

using namespace std;

using ll=long long;

const int MN = 200005;
const ll INF = 1e16;

int T;
int N;
ll A[MN];

int up[MN], down[MN];
ll lenval[MN];
void solve() {
    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }
    fill(up, up+N, 0);
    fill(lenval, lenval+N+1, INF);
    lenval[0] = A[0];
    for (int i=1; i<N; ++i) {
        int idx = upper_bound(lenval, lenval+N+1, A[i] - 1) - lenval;
        lenval[idx] = min(lenval[idx], A[i]);
        up[i] = idx;
    }

    fill(down, down+N, 0);
    fill(lenval, lenval+N+1, INF);
    lenval[0] = A[N-1];
    for (int i=N-1; i>=0; --i) {
        int idx = upper_bound(lenval, lenval+N+1, A[i] - 1) - lenval;
        lenval[idx] = min(lenval[idx], A[i]);
        down[i] = idx;
    }

    int ans = 0;
    for (int i=0; i<N; ++i) {
        //cerr << up[i] << ' ' << down[i] << endl;
        if (up[i] == 0 || down[i] == 0) continue;
        ans = max(ans, up[i] + down[i] + 1);
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> T;
    while (T --> 0) {
        solve();
    }
}
