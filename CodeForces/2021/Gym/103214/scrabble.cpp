//scrabble.cpp created at 08/06/21 11:36:41

#include <bits/stdc++.h>

using namespace std;

const int MN = 21;

string A[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int N;
    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }

    string chars;
    for (int i=0; i<7; ++i) {
        char c;
        cin >> c;
        chars += c;
    }
    sort(chars.begin(), chars.end());

    int ans = 0;
    for (int i=0; i<N; ++i) {
        sort(A[i].begin(), A[i].end());

        bool ok = true;
        int k = 0;
        for (int j=0; j<A[i].size(); ++j) {
            while (k < chars.size() && chars[k] != A[i][j]) ++k;
            if (k == chars.size()) {
                ok = false;
                break;
            }
            ++k;
        }

        if (ok) {
            int score = A[i].size();
            if (score > 3) score <<= 1;
            ans = max(ans, score);
        }
    }
    cout << ans << endl;
}
