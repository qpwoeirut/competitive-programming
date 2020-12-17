//subarray_divisibility.cpp created at 12/16/20 20:46:51

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MN = 200005;

int N;
ll A[MN];
ll psum[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
        psum[i+1] = (((A[i] + psum[i]) % N) + N) % N;
    }

    map<ll, int> ct;
    ll ans = 0;
    for (int i=0; i<=N; ++i) {
        auto it = ct.find(psum[i]);
        if (it != ct.end()) {
            ans += it->second;
        }
        ++ct[psum[i]];
    }

    cout << ans << endl;
}

