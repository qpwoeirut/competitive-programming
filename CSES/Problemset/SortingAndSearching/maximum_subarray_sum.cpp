//maximum_subarray_sum.cpp created at 10/16/20 21:44:46

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    ll ans = -1001001001;
    ll cur = 0, x;
    for (int i=0; i<N; ++i) {
        cin >> x;
        cur = max(x, cur + x);
        ans = max(ans, cur);
    }
    cout << ans << endl;
}
