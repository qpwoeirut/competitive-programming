//shopping_fever.cpp created at 09/05/21 20:31:06

#include <bits/stdc++.h>

using namespace std;

using ll=long long;

const int MN = 100005;

ll A[MN], B[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll N, Q;
    cin >> N >> Q;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }
    sort(A, A+N);
    B[0] = 0;
    B[1] = A[0] * (100 - Q) / 100;
    if (N >= 2) B[2] = (A[0] + A[1]) * (100 - Q) / 100;

    for (int i=3; i<=N; ++i) {
        B[i] = min(B[i-1] + A[i-1] * (100 - Q) / 100, B[i-3] + A[i-2] + A[i-1]);
    }
    cout << B[N] << '\n';
}

