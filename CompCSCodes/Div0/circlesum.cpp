//circlesum.cpp created at 11/12/20 11:51:13
// lazy N^2 sol
#include <bits/stdc++.h>

using namespace std;

const int MN = 101 * 2;

int N;
int A[MN];

int main() {
    freopen("circlesum.in", "r", stdin);
    freopen("circlesum.out", "w", stdout);

    cin.tie(0)->sync_with_stdio(0);
    cin >> N;
    if (N == 0) {
        cout << 0 << endl;
        return 0;
    }

    for (int i=0; i<N; ++i) {
        cin >> A[i];
        A[N+i] = A[i];
    }

    int ans = 0;
    for (int i=0; i<N; ++i) {
        int cur = 0;
        for (int j=i; j-i<N && j<2*N; ++j) {
            cur += A[j];
            ans = max(ans, cur);
        }
    }

    cout << ans << endl;
}
