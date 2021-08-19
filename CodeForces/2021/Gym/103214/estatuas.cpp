//estatuas.cpp created at 08/06/21 13:21:35

#include <bits/stdc++.h>

using namespace std;

#define pb push_back

const int MN = 16;

int N;
int A;

bool V[1 << 8][MN][MN][2];

vector<int> ans;
bool recurse(const int mask, const int idx, const int pos, const bool direction) {
    if (V[mask][idx][pos][direction]) return false;
    V[mask][idx][pos][direction] = true;
    if (idx == N) return pos == 0;
    if (pos+1 < N && ((mask >> pos) & 1) == ((A >> idx) & 1)) {
        if (!direction) ans.pb(pos);
        if (recurse(mask, idx+1, pos+1, true)) return true;
        if (!direction) ans.pop_back();
    }

    if (pos > 0 && ((mask >> (pos - 1)) & 1) != ((A >> idx) & 1)) {
        if (direction) ans.pb(pos);
        if (recurse(mask, idx+1, pos-1, false)) return true;
        if (direction) ans.pop_back();
    }
    return false;
}

void solve() {
    for (int i=0; i<(1<<(N+1)); ++i) {
        for (int j=0; j<N; ++j) {
            for (int k=0; k<N; ++k) {
                V[i][j][k][0] = V[i][j][k][1] = false;
            }
        }

        if (recurse(i, 0, 0, true)) {
            cout << "SI\n10\n";
            string s(10, 'D');
            int idx = 0;
            while (i > 0) {
                if (i & 1) s[idx] = 'I';
                i >>= 1;
                ++idx;
            }
            cout << s << '\n';
            cout << ans.size() << '\n';
            for (int j=0; j<ans.size(); ++j) {
                if (j) cout << ' ';
                cout << ans[j];
            }
            cout << '\n';
            return;
        }
    }

    cout << "NO\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int T;
    cin >> T;
    while (T--) {
        cin >> N;

        string S;
        cin >> S;
        reverse(S.begin(), S.end());

        A = 0;
        for (const char c: S) {
            A = (A << 1) + (c == 'I');
        }

        assert(N <= 15);

        solve();
    }
}

