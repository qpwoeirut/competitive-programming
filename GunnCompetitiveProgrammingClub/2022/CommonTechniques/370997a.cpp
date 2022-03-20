#include <bits/stdc++.h>

using namespace std;

using ll=long long;

const int MN = 2001001;
ll A[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    for (int i=0; i<N; ++i) cin >> A[i];

    ll sum = 0;
    for (int i=0; i<N; ++i) {
        sum += A[i];
        cout << sum << '\n';
    }
}
