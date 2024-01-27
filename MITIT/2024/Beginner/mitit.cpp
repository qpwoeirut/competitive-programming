#include <bits/stdc++.h>

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int Q;
    cin >> Q;
    while (Q --> 0) {
        string S;
        cin >> S;

        bool ok = false;
        for (int i=1; i<S.size(); ++i) {
            int n2 = S.size() - i;
            if (n2 % 2 == 1) continue;

            int n = n2 / 2;
            bool match = true;
            for (int j=0; j<n; ++j) {
                match &= S[i + j] == S[n + i + j];
            }
            ok |= match;
        }

        cout << (ok ? "YES" : "NO") << '\n';
    }
}
