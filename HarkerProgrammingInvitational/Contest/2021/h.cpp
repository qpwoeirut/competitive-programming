#include <bits/stdc++.h>

using namespace std;

#define x real()
#define y imag()

typedef long double dbl;
typedef complex<dbl> pt;

const int MN = 4003;

int N, M;
pt A[MN];
dbl dp[MN];

dbl angle(const pt& p) {
    return atan2(p.y, p.x);
}

bool cmp_angle(const pt& a, const pt& b) {
    return angle(a) < angle(b);
}

dbl cost(const pt& a, const pt& b) {
    return abs(b) * sin(angle(b) - angle(a));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M;
    for (int i=0; i<N; ++i) {
        int px, py;
        cin >> px >> py;
        A[i] = pt(px, py);
    }

    sort(A, A+N, cmp_angle);

    fill(dp, dp+N, 1e18);
    dp[0] = cost(pt(1, 0), A[0]);
    for (int i=1; i<N; ++i) {
        for (int j=0; j<i; ++j) {
            dp[i] = min(dp[i], dp[j] + cost(A[j], A[i]));
        }
    }

    dbl ans = dp[N-1] * 1000;
    long long print = round(ans) + 1e-8;
    ans = print;
    ans /= 1000;
    cout << fixed << setprecision(3);
    cout << ans << '\n';
}

