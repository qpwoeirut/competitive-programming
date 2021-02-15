//array_division.cpp created at 12/16/20 20:49:51

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MN = 200005;

int N, K;
ll A[MN];

bool check(const ll mxsum) {
    int parts = 1;
    ll cur = 0;
    for (int i=0; i<N; ++i) {
        if (A[i] > mxsum) return false;
        cur += A[i];
        if (cur > mxsum) {
            ++parts;
            cur = A[i];
        }
    }
    return parts <= K;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> K;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }

    ll lo = 0, hi = 1e16;
    while (lo < hi) {
        ll mid = (lo + hi) >> 1;
        if (check(mid)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }

    cout << lo << endl;
}
