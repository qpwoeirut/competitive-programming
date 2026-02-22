#include <bits/stdc++.h>

using namespace std;
using ll=long long;

const int MN = 50004;

ll N, K;
ll A[MN];
ll B[MN];

void solve() {

}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int T;
    cin >> T;

    while (T --> 0) {
        cin >> N >> K;
        for (int i=0; i<N; ++i) {
            cin >> A[i];
        }
        for (int i=0; i<N; ++i) {
            cin >> B[i];
        }

        solve();
    }
}
