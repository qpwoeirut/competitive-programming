//sure_bet.cpp created at 01/20/21 18:39:34

#include <bits/stdc++.h>

using namespace std;

typedef long double dbl;
typedef long long ll;

const int MN = 1000005;
const int BET = 10000;
const dbl EPS = 1e-8;

int N;
ll A[MN], B[MN];

ll sum[MN];

ll solve() {
    for (int i=0; i<N; ++i) {
        sum[i] = (i ? sum[i-1] : 0) + B[i];
    }
    ll ret = 0;
    ll cur = 0;
    for (int i=0; i<N; ++i) {
        cur += A[i];

        int lo = 0, hi = N-1;
        while (lo < hi) {
            int mid = (lo + hi) >> 1;

            if (sum[mid] < cur) {
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }

        const ll spent = BET * (i+1 + lo+1);
        ret = max(ret, min(cur, sum[lo]) - spent);
    }
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        dbl a, b;
        cin >> a >> b;
        a += EPS; b += EPS;
        A[i] = a * (dbl)BET;
        B[i] = b * (dbl)BET;
    }
    sort(A, A+N, greater<ll>());
    sort(B, B+N, greater<ll>());

    ll ans = solve();
    swap(A, B);
    ans = max(ans, solve());

    dbl x = ans;
    x /= (dbl)BET;
    cout << fixed << setprecision(4);
    cout << x << endl;
}

/*
4
1.4 3.7
1.2 2
1.6 1.4
1.9 1.5
*/
