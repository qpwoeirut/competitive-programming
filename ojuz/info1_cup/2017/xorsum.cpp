#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MN = 1001001;
const int MX = 4001;
const int BITS = 60;

ll N;
ll A[MN], freq[MN];
ll ct[BITS];
int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }

    ll ans = 0;
    if (N <= MX) {
        for (int i=0; i<N; ++i) {
            for (int j=i; j<N; ++j) {
                ll x = A[i] + A[j];
                ans ^= x;
            }
        }
    } else {
        for (int i=0; i<N; ++i) ++freq[A[i]];
        for (int i=0; i<MX; ++i) {
            for (int j=i; j<MX; ++j) {
                ll x;
                if (i == j) {
                    x = (freq[i] * (freq[i] + 1)) >> 1;
                } else {
                    x = freq[i] * freq[j];
                }
                if (x & 1) ans ^= (i+j);
                //if (x) cerr << i << ' ' << j << ' ' << x << endl;
            }
        }
    }

    cout << ans << endl;
}
