#include <bits/stdc++.h>

using namespace std;

using ll=long long;

const int MN = 400005;

int A[MN];
int B[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int N;
    cin >> N;

    map<ll,ll> sum;

    for (int i=0; i<N; ++i) {
        cin >> B[i];
        A[i] = B[i] - i;
        sum[A[i]] += B[i];
    }

    ll ans = 0;
    for (const pair<const ll, ll>& p: sum) {
        ans = max(ans, p.second);
    }
    cout << ans << '\n';
}

