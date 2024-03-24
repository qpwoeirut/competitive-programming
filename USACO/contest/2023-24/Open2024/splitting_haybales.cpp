#include <bits/stdc++.h>

using namespace std;

const int MN = 200005;

int A[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int N, Q;
    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }
    cin >> Q;
    for (int i=0; i<Q; ++i) {
        int l, r, x;
        cin >> l >> r >> x;
        --l;

        for (int j=l; j<r; ++j) {
            if (x <= 0) x += A[j];
            else x -= A[j];
        }
        cout << x << '\n';
    }
}
