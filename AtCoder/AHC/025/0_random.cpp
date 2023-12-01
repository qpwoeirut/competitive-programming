#include <bits/stdc++.h>

using namespace std;

const int MN = 100;

int ans[MN];
void solve(const int N, const int D, const int Q) {
    for (int i = 0; i < Q; ++i) {
        cout << "1 1 0 1\n";
        cout.flush();
    }
    for (int i = 0; i < N; ++i) {
        ans[i] = (D * i) / N;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int N, D, Q;
    cin >> N >> D >> Q;

    solve(N, D, Q);

    for (int i = 0; i < N; ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
}

