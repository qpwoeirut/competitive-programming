#include <bits/stdc++.h>

using namespace std;

void solve(int testcase) {
    int R, C;
    cin >> R >> C;

    cout << "Case #" << testcase << ":\n";
    for (int i=0; i<2*R+1; ++i) {
        for (int j=0; j<2*C+1; ++j) {
            if (i + j <= 1) cout << '.';
            else if (i & 1) cout << ((j & 1) ? '.' : '|');
            else cout << ((j & 1) ? '-' : '+');
        }
        cout << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int T;
    cin >> T;
    for (int t=1; t<=T; ++t) solve(t);
}
