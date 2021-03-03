//1485b.cpp created at 02/27/21 11:43:42

#include <bits/stdc++.h>

using namespace std;

const int MN = 100005;

int N, Q, K;
int A[MN];
int psum[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> Q >> K;
    for (int i=1; i<=N; ++i) {
        cin >> A[i];
    }

    A[0] = 0;
    A[N+1] = K+1;
    for (int i=1; i<=N; ++i) {
        psum[i] = psum[i-1];
        psum[i] += A[i+1] - A[i-1] - 2;
    }

    for (int i=0; i<Q; ++i) {
        int L, R;
        cin >> L >> R;

        int ans = psum[R-1] - psum[L];
        ans += K - A[R-1] - 1;
        ans += A[L+1] - 2;

        cout << ans << '\n';
    }
}

