#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int MN = 100005;

ll A[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int N;
    cin >> N;

    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }

    int flips = 0;
    ll val = 0;
    for (int i=1; i<N; ++i) {
        A[i] = val + (flips & 1 ? -A[i] : A[i]);
        if (A[i-1] > A[i]) {
            A[i] = 2 * A[i-1] - A[i];
            val = 2 * A[i-1] - val;
            ++flips;
        }
    }

    if (A[0] == A[N-1]) {
        cout << A[N-1] << '\n';
        return 0;
    }

    ll g = 2 * (A[N-1] - A[0]);
    for (int i=1; i<N; ++i) {
        if (A[i] > A[i-1]) {
            g = gcd(g, 2 * (A[i] - A[i-1]));
        }
    }

    ll k = (A[0] - 1) / g;
    cout << A[N-1] - k * g << '\n';
}
