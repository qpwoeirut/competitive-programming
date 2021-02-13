#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

typedef long long ll;
typedef pair<ll,ll> pii;

const int MN = 200005;

ll N, K, M;
pii A[MN];

int P[MN];
int arr[MN];
set<int> seen[MN];

int par[MN];
int root(const int n) {
    return n == par[n] ? n : par[n] = root(par[n]);
}
void join(const int n, const int m) {
    int rn = root(n), rm = root(m);
    if (rn == rm) return;
    if (seen[rn].size() > seen[rm].size()) swap(rn, rm);
    par[n] = par[rn] = par[m] = par[rm];
    for (const int x: seen[rn]) seen[rm].insert(x);
}

int ans[MN];
void brute() {
    int ki = 0;
    int last = 0;
    while (M-- > 0) {
        ++last;
        swap(arr[A[ki].fi], arr[A[ki].se]);
        if (seen[arr[A[ki].fi]].insert(A[ki].fi).se) last = 0;
        if (seen[arr[A[ki].se]].insert(A[ki].se).se) last = 0;

        if (++ki == K) ki = 0;
        if (last > K) break;
    }

    for (int i=0; i<N; ++i) {
        cout << seen[i].size() << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> K >> M;
    for (int i=0; i<K; ++i) {
        cin >> A[i].fi >> A[i].se;
        --A[i].fi; --A[i].se;
    }

    for (int i=0; i<N; ++i) {
        arr[i] = i;
        seen[i].insert(i);
    }
    if (N <= 100 && K <= 200) {
        brute();
        return 0;
    }

    for (int i=0; i<K; ++i) {
        swap(arr[A[i].fi], arr[A[i].se]);
        seen[arr[A[i].fi]].insert(A[i].fi);
        seen[arr[A[i].se]].insert(A[i].se);
    }

    for (int i=0; i<N; ++i) {
        P[arr[i]] = i;
    }
    for (int i=0; i<N; ++i) {
        par[i] = i;
    }
    for (int i=0; i<N; ++i) {
        join(i, P[i]);
    }

    for (int i=0; i<N; ++i) {
        ans[i] = seen[root(i)].size();
    }

    for (int i=0; i<N; ++i) {
        cout << ans[i] << '\n';
    }
}
