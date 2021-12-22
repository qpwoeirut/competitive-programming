#include <bits/stdc++.h>

using namespace std;

using ll=long long;

string row[2], col[2];

ll ct_row[9], ct_col[9];

int to_int(char c) {
    if (c == 'R') return 0;
    if (c == 'G') return 1;
    if (c == 'B') return 2;
    assert(0);
}

string color[9] = { "RR", "RG", "RB", "GR", "GG", "GB", "BR", "BG", "BB" };

int main() {
    int N;
    cin >> N;
    cin >> row[0];
    cin >> col[0];
    cin >> row[1];
    cin >> col[1];
    
    for (int i=0; i<N; ++i) {
        ++ct_row[to_int(row[0][i]) * 3 + to_int(row[1][i])];
        ++ct_col[to_int(col[0][i]) * 3 + to_int(col[1][i])];
    }

    ll ans = 0;
    for (int i=0; i<9; ++i) {
        for (int j=0; j<9; ++j) {
            string s = color[i] + color[j];
            sort(s.begin(), s.end());
            s.resize(unique(s.begin(), s.end()) - s.begin());

            if (s.size() == 3) {
                ans += ct_row[i] * ct_col[j];
            }
        }
    }

    cout << ans << '\n';
}
