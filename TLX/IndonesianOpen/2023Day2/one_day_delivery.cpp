//one_day_delivery.cpp created at 08/31/23 17:58:50

#include <bits/stdc++.h>

using namespace std;
using ll=long long;

bool DEBUG = false;
int SECRET = 0;

string get_resp(const int q) {
    if (DEBUG) {
        if (SECRET < q) return "KEBESARAN";
        else if (SECRET > q) return "KEKECILAN";
        else return "PAS";
    } else {
        string S;
        cin >> S;
        return S;
    }
}

const int MN = 5000;
int dp[MN][MN + 1];

const int N_FIB = 25;
ll fib[N_FIB];

ll N, T;
void dp_solve() {
    assert(N <= MN);

    fib[0] = fib[1] = 1;
    for (int i=2; i<N_FIB; ++i) {
        fib[i] = fib[i-1] + fib[i-2];
    }

    for (int diff=0; diff<N; ++diff) {
        for (int q=0; q<N; ++q) {
            dp[diff][q] = diff + 1;
        }
        dp[diff][N] = diff + 2;
    }

    for (int diff=2; diff<N; ++diff) {
        for (int q=0; q<=diff; ++q) {
            for (int x=0; x<=diff; ++x) {
                const int lower = q > 0 ? dp[q - 1][x < q ? x : N] : 0;
                const int higher = q < diff ? dp[diff - q - 1][x > q ? x - q - 1 : N] : 0;
                dp[diff][q] = min(dp[diff][q], max(lower, higher) + 1);
            }
            dp[diff][N] = min(dp[diff][N], dp[diff][q] + 1);
        }
    }
    //for (int d=0; d<N; ++d) {
    //    cerr << dp[d][N] << "  ";
    //    for (int q=0; q<=d; ++q) {
    //        cerr << char('a' + dp[d][q] - 1) << ' ';
    //    } cerr << endl;
    //}

    ll lo = 1, hi = N;
    ll qval = -1;

    for (int t=0; t<T; ++t) {
        int val = -1, cost = N;
        const int q = (qval < lo || qval > hi) ? N : qval - lo;
        for (int x=0; x+lo<=hi; ++x) {
            if (q == N) {
                if (cost > dp[hi - lo][x]) {
                    cost = dp[hi - lo][x];
                    val = lo + x;
                }
            } else {
                const int lower = q > 0 ? dp[q - 1][x < q ? x : N] : 0;
                const int higher = q < hi - lo ? dp[hi - lo - q - 1][x > q ? x - q - 1 : N] : 0;
                if (cost > max(lower, higher) + 1) {
                    cost = max(lower, higher) + 1;
                    val = lo + x;
                }
            }
        }
        //cerr << "diff, q: " << hi - lo << ' ' << q << endl;
        //cerr << "x:";
        //for (int x=0; x+lo<=hi; ++x) {
        //    if (q == N) {
        //        if (cost == dp[hi - lo][x]) {
        //            cerr << ' ' << x;
        //        }
        //    } else {
        //        const int lower = q > 0 ? dp[q - 1][x < q ? x : N] : 0;
        //        const int higher = q < hi - lo ? dp[hi - lo - q - 1][x > q ? x - q - 1 : N] : 0;
        //        if (cost == max(lower, higher) + 1) {
        //            cerr << ' ' << x;
        //        }
        //    }
        //}
        //cerr << endl;


        //if (q == N) {
        //    int f_i = upper_bound(fib, fib+N_FIB, hi - lo) - fib;
        //    const int x = hi - lo - fib[max(0, f_i - 2)] + 1;
        //    cerr << "qn x: " << x << endl;
        //    assert(cost == dp[hi - lo][x]);
        //    val = lo + x;
        //} else {
        //    int f_i = upper_bound(fib, fib+N_FIB, hi - lo - q) - fib;
        //    const int x = hi - lo - q - fib[max(0, f_i - 1)] + 1;
        //    cerr << "fib: " << x << endl;
        //    const int lower = q > 0 ? dp[q - 1][x < q ? x : N] : 0;
        //    const int higher = q < hi - lo ? dp[hi - lo - q - 1][x > q ? x - q - 1 : N] : 0;
        //    assert(cost == max(lower, higher) + 1);

        //    val = lo + x;
        //}

        cout << val << '\n';
        cout.flush();

        //cerr << t << ' ' << lo << ' ' << qval << ' ' << val << ' ' << hi << ' ' << dp[hi - lo][q] << endl;
        //cerr << val << ' ' << hi - lo << ' ' << q << endl;

        if (t > 0) {
            const string S = get_resp(qval);
            if (S == "KEKECILAN") {
                lo = min(max(lo, qval + 1), N);
            } else if (S == "KEBESARAN") {
                hi = max(min(hi, qval - 1), 1LL);
            } else if (S == "PAS") {
                return;
            } else assert(0);
        }
        qval = val;
    }
    assert(0);
}

void solve() {
    fib[0] = fib[1] = 1;
    for (int i=2; i<N_FIB; ++i) {
        fib[i] = fib[i-1] + fib[i-2];
    }

    ll lo = 1, hi = N;
    ll qval = -1;

    for (int t=0; t<T; ++t) {
        const int f_i = upper_bound(fib, fib+N_FIB, hi - lo) - fib;
        const ll x = hi - fib[max(0, f_i - 2)] + 1;
        cout << x << '\n';
        cout.flush();

        cerr << t << ' ' << lo << ' ' << qval << ' ' << x << ' ' << hi << endl;

        if (t > 0) {
            const string S = get_resp(qval);
            if (S == "KEKECILAN") {
                lo = min(max(lo, qval + 1), N);
            } else if (S == "KEBESARAN") {
                hi = max(min(hi, qval - 1), 1LL);
            } else if (S == "PAS") {
                return;
            } else assert(0);
        }
        qval = x;
    }

    assert(0);
}

void bad_solve() {
    ll lo = 1, hi = N;
    ll q = -1;

    for (int t=0; t<T; ++t) {
        ll x;
        if (lo <= q && q <= hi) {
            if (q - lo >= hi - q) {
                x = (lo + lo + q + 1) / 3;
            } else {
                x = (q + hi + hi + 2) / 3;
            }
        } else {
            x = (lo + lo + hi) / 3;
        }
        cout << x << '\n';
        cout.flush();

        //cerr << t << ' ' << lo << ' ' << q << ' ' << x << ' ' << hi << endl;

        if (t > 0) {
            string S;
            cin >> S;
            if (S == "KEKECILAN") {
                lo = min(max(lo, q + 1), N);
            } else if (S == "KEBESARAN") {
                hi = max(min(hi, q - 1), 1LL);
            } else if (S == "PAS") {
                break;
            } else assert(0);
        }

        q = x;
    }
}

void test() {
    DEBUG = true;
    for (SECRET=1; SECRET <= N; ++SECRET) {
        cerr << "SECRET = " << SECRET << endl;
        dp_solve();
        solve();
    }
}

int main() {
    cin >> N >> T;

    //test(); return 0;

    //solve();
    if (N < MN) dp_solve();
    else bad_solve();
}

