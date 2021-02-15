//subarray_sums_ii.cpp created at 12/16/20 20:39:07

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MN = 200005;

int N, X;
ll A[MN];
ll psum[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> X;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
        psum[i+1] = A[i] + psum[i];
    }

    map<ll, int> ct;
    ll ans = 0;
    for (int i=0; i<=N; ++i) {
        auto it = ct.find(psum[i] - X);
        if (it != ct.end()) {
            ans += it->second;
        }
        ++ct[psum[i]];
    }

    cout << ans << endl;
}

