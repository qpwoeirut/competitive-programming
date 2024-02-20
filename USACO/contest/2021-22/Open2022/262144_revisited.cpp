#include <bits/stdc++.h>

using namespace std;

using ll=long long;

const int MN = 265005;
const int INIT = 1001001001;

int N;
int A[MN];

ll out = 0;
int merge_until(int i, int val) {
    ll res = A[i];
    if (val == INIT) out += res;
    ++i;
    while (res < val && i < N) {
        if (res <= A[i]) {
            res = A[i] + 1;
            if (val == INIT) out += res;
            ++i;
        } else {
            const int new_i = merge_until(i, res);
            ++res;
            if (val == INIT) out += (new_i - i) * res;
            i = new_i;
        }
    }

    return i - (res > val);
}

ll solve() {
    ll ans = 0;
    for (int i=0; i<N; ++i) {
        out = 0;
        merge_until(i, INIT);
        ans += out;
    }
    return ans;
}

/*
int dp[MN][MN];

ll brute() {
    for (int i=0; i<N; ++i) {
        for (int j=0; j<=N; ++j) {
            dp[i][j] = INIT;
        }
    }

    for (int r=0; r<N; ++r) {
        for (int i=0; i<N; ++i) {
            const int j = i + r + 1;
            if (r == 0) {
                dp[i][j] = A[i];
            } else {
                for (int k=0; k<=r; ++k) {
                    dp[i][j] = min(dp[i][j], max(dp[i][i+k], dp[i+k][j]) + 1);
                }
            }
        }
    }

    long long ans = 0;
    for (int i=0; i<N; ++i) {
        for (int j=i+1; j<=N; ++j) {
            ans += dp[i][j];
        }
    }
    return ans;
}

mt19937 rng(8);

void test() {
    for (N=2; N<=10; ++N) {
        cerr << N << endl;
        for (int t=0; t<1000000; ++t) {
            for (int i=0; i<N; ++i) {
                A[i] = (rng() % 10) + 1;
            }

            ll sans = solve();
            ll bans = brute();
            if (sans != bans) {
                cerr << N << endl;
                for (int i=0; i<N; ++i) {
                    if (i) cerr << ' ';
                    cerr << A[i];
                }
                cerr << endl;
                cerr << sans << ' ' << bans << endl;
            }
            assert(sans == bans);
        }
    }
}
*/
int main() {
    cin.tie(0)->sync_with_stdio(0);

    //test(); return 0;

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }
    ll ans = solve();
    cout << ans << '\n';
}
