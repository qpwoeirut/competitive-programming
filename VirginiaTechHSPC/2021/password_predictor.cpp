#include <bits/stdc++.h>

using namespace std;

int L, T, G;
char A[1000 * 1000];
int B[1000];

char guess[1000];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> L;

    cin >> T;
    for (int i=0; i<T; ++i) {
        for (int j=0; j<L; ++j) cin >> A[i*L+j];
        cin >> B[i];
    }

    int ans = 0;
    cin >> G;
    for (int i=0; i<G; ++i) {
        for (int j=0; j<L; ++j) cin >> guess[j];
        bool ok = true;
        for (int j=0; j<T; ++j) {
            int match = 0;
            for (int k=0; k<L; ++k) {
                match += A[j*L + k] == guess[k];
            }
            if (match != B[j]) {
                ok = false;
                break;
            }
        }
        ans += ok;
    }

    cout << ans << '\n';
}
