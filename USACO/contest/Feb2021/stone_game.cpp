#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MN = 100005;
const ll MX = 1000000;

int N;
ll A[MN];

ll floor_sum[MX+1];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll mx = 0;
    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
        mx = max(mx, A[i]);
    }

    for (ll x=1; x<=mx; ++x) {
        for (int i=0; i<N; ++i) {
            floor_sum[x] += A[i] / x;
        }
    }
    //for (int i=0; i<N; ++i) {
    //    for (int x=1; x*x<=A[i]; ++x) {
    //        if (A[i] % x) continue;
    //        floor_sum[x] += A[i] / x;
    //        if (x*x != A[i]) floor_sum[A[i] / x] += x;
    //    }
    //}
    //for (int i=MX-1; i>=0; --i) {
    //    floor_sum[i] += floor_sum[i+1];
    //}

    //for (int x=1; x<=10; ++x) { cerr << x << ' ' << floor_sum[x] << endl; }

    ll ans = 0;
    for (int i=0; i<N; ++i) {
        for (ll x=1; x<=A[i]; ++x) {
            bool ok = true;
            for (ll m=x; m<=mx; m+=x) {
                if ((floor_sum[m] ^ ((A[i] % m) < x)) & 1) {
                    //cerr << i << ' ' << x << ' ' << m << endl;
                    ok = false;
                    break;
                }
            }

            ans += ok;
        }
    }

    cout << ans << endl;
}
