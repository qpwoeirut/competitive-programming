#include <bits/stdc++.h>

using namespace std;

int Q;
long long K, N, A, B;

bool works(long long plays) {
    if (plays == -1) return true;

    return plays * A + (N - plays) * B < K;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> Q;
    for (int i=0; i<Q; ++i) {
        cin >> K >> N >> A >> B;
        if (B * N >= K) {
            cout << -1 << '\n';
            continue;
        }
        
        int lo = 0, hi = N;
        while (lo < hi) {
            int mid = (lo + hi + 1) / 2;

            if (works(mid)) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }

        cout << lo << '\n';
    }
}
