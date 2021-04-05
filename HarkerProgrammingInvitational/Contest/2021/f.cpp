#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct Block {
    ll a, b, c;

    inline const bool operator<(const Block& o) const {
        if (a == o.a) {
            if (b == o.b) return c < o.c;
            return b > o.b;
        }
        return a > o.a;
    }
};

const int MN = 5003;

int N;
Block A[MN];
ll dp[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i].a >> A[i].b >> A[i].c;
        if (A[i].a < A[i].b) swap(A[i].a, A[i].b);
    }
    sort(A, A+N);

    for (int i=0; i<N; ++i) {
        dp[i] = A[i].c;
        for (int j=0; j<i; ++j) {
            if (A[i].a < A[j].a && A[i].b < A[j].b) {
                dp[i] = max(dp[i], dp[j] + A[i].c);
            }
        }
        //cerr << i << ' ' << A[i].a << ' ' << A[i].b << ' ' << A[i].c << " = " << dp[i] << endl;
    }

    cout << *max_element(dp, dp+N) << '\n';
}
