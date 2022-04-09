//d1000000.cpp created at 04/02/22 16:07:12

#include <bits/stdc++.h>

using namespace std;

const int MN = 100005;

int N;
int A[MN];

void solve(int testcase) {
    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }
    sort(A, A+N);

    int ans = 0;
    for (int i=0; i<N; ++i) {
        if (A[i] > ans) ++ans;
    }

    cout << "Case #" << testcase << ": " << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int T;
    cin >> T;

    for (int t=1; t<=T; ++t) solve(t);
}
