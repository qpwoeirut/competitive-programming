#include <bits/stdc++.h>

using namespace std;

const int MN = 1000006;

int A[MN];

int solve(int N) {
    int ct[4];  // 0 1 2345 6789
    fill(ct, ct+4, 0);
    for (int i=0; i<N; ++i) {
        ct[(A[i] >= 1) + (A[i] >= 2) + (A[i] >= 6)]++;
    }

    int ans = 0;
    while (ct[0] + ct[1] + ct[2] + ct[3] >= 4) {
        if (ct[0]) {
            --ct[0];
            int mx = -1;
            for (int i=0; i<4; ++i) if (ct[i]) mx = i;
            --ct[mx];
        } else if (ct[1] >= 2) {
            ct[1] -= 2;
        } else break;

        int m0 = -1;
        for (int i=0; i<3; ++i) if (ct[i]) m0 = i;
        if (m0 == -1) break;
        --ct[m0];

        int m1 = -1;
        for (int i=0; i<4; ++i) if (ct[i]) m1 = i;
        assert(m1 >= 0);
        --ct[m1];

        ++ans;
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int T;
    cin >> T;

    while (T --> 0) {
        int N;
        cin >> N;
        for (int i=0; i<N; ++i) {
            char c;
            cin >> c;
            A[i] = c - '0';
        }
        int ans = solve(N);
        cout << ans << '\n';
    }
}
