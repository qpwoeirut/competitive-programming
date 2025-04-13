#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using dbl = double;
using pdd = pair<dbl, dbl>;

#ifdef LOCAL
#include "qpwoeirut/debug.h"
#else
#define debug
#define debug1
#define debug2
#define debug3
#endif

template <class T> bool chmn(T& a, const T& b) {return (greater<T>()(a, b) ? (a=b, true) : false);}
template <class T> bool chmx(T& a, const T& b) {return (less<T>()(a, b) ? (a=b, true) : false);}

const dbl PI = acos(-1.0);
const dbl INF = 1e7;

dbl normalize(dbl theta) {
    if (theta < 0) return theta + 2*PI;
    if (theta >= 2*PI) return theta - 2*PI;
    return theta;
}

using pt = complex<dbl>;
#define x real()
#define y imag()

namespace std {
    inline bool operator<(const pt& a, const pt& b) {
        return normalize(arg(a)) < normalize(arg(b));
    }
    inline bool operator>(const pt& a, const pt& b) {
        return b < a;
    }
}

istream& operator>>(istream& is, pt& p) {
    dbl a, b;
    is >> a >> b;
    p = pt(a, b);
    return is;
}

string to_string(const pt& p) {
    return "(" + to_string(p.x) + ", " + to_string(p.y) + ")";
}

#ifndef TEST
static_assert(0);
#else
static_assert(1 <= TEST && TEST <= 12);
#endif

const int N_ALL[12] = { 8, 100, 100, 15, 100, 100, 100, 1000, 300, 16, 660, 150 };
const int N = N_ALL[TEST - 1];
const int K = TEST <= 8 ? 2 : 3;
string pad(int n) {
    return (n < 10 ? "0" : "") + to_string(n);
}
ifstream fin("tests/" + pad(TEST));
ofstream fout("sol/" + pad(TEST) + ".out");

pair<pt, int> A[N];

#if TEST <= 8
dbl dp[N + 1][2];
dbl angle[N + 1][2][K];
int ans[N][2];

dbl cost(const dbl a[K], const dbl b[K]) {
    return max(
        min(abs(a[0] - b[0]), 2 * PI - abs(a[0] - b[0])),
        min(abs(a[1] - b[1]), 2 * PI - abs(a[1] - b[1]))
    );
}

void solve(const dbl l0, const dbl l1) {
    for (int i=0; i<=N; ++i) {
        dp[i][0] = dp[i][1] = INF;
    }

    for (int i=0; i<N; ++i) {
        const dbl a = l0, b = abs(A[i].first), c = l1;
        const dbl t0 = acos((a*a + b*b - c*c) / (2 * a * b));
        debug(i, a, b, c, t0);

        angle[i + 1][0][0] = normalize(t0 - arg(A[i].first));
        angle[i + 1][1][0] = normalize(t0 + arg(A[i].first));

        const dbl t1 = acos((a*a + c*c - b*b) / (2 * a * c));
        angle[i + 1][0][1] = normalize(PI + t1);
        angle[i + 1][1][1] = normalize(PI - t1);

        pt mid = l0 * pt(cos(angle[i + 1][0][0]), sin(angle[i + 1][0][0]));
        debug(abs(A[i].first - mid));
        pt test = mid + l1 * pt(cos(angle[i + 1][0][1]), sin(angle[i + 1][0][1]));
        if (abs(test - A[i].first) > 1e-6) swap(angle[i + 1][0][1], angle[i + 1][1][1]);
    }

    angle[0][0][0] = angle[0][0][1] = angle[0][1][0] = angle[0][1][1] = 0;
    dp[0][0] = dp[0][1] = 0;
    for (int i=1; i<=N; ++i) {
        if (chmn(dp[i][0], dp[i-1][0] + cost(angle[i-1][0], angle[i][0]))) {
            ans[i][0] = 0;
        }
        if (chmn(dp[i][0], dp[i-1][1] + cost(angle[i-1][1], angle[i][0]))) {
            ans[i][0] = 1;
        }
        if (chmn(dp[i][1], dp[i-1][0] + cost(angle[i-1][0], angle[i][1]))) {
            ans[i][1] = 0;
        }
        if (chmn(dp[i][1], dp[i-1][1] + cost(angle[i-1][1], angle[i][1]))) {
            ans[i][1] = 1;
        }
    }

    vector<pair<int, pdd>> out;
    int cur = dp[N][0] >= dp[N][1];
    for (int i=N; i>0; --i) {
        out.emplace_back(A[i - 1].second, pdd(angle[i][cur][0], angle[i][cur][1]));
        cur = ans[i][cur];
    }
    reverse(out.begin(), out.end());
    debug(l0, l1);
    debug2(dp, N+1, 2);
    debug3(angle, N+1, 2, 2);

    for (const pair<int, pdd>& p: out) {
        fout << fixed << setprecision(12) << p.first + 1 << ' ' << p.second.first << ' ' << p.second.second << '\n';
    }
    cerr << TEST << ": " << dp[N][0] << ' ' << dp[N][1] << '\n';
}
#else
const int MULT = 5000;
const int M = PI * MULT;

dbl cost(const dbl a[K], const dbl b[K]) {
    return max(
        max(
            max(abs(a[0] - b[0]), 2 * PI - abs(a[0] - b[0])),
            max(abs(a[1] - b[1]), 2 * PI - abs(a[1] - b[1]))
        ),
        max(abs(a[2] - b[2]), 2 * PI - abs(a[2] - b[2]))
    );
}

void solve(dbl l0, dbl l1, dbl l2) {
    int ans[N][M][2][2];
    dbl angle[N + 1][M][2][K];
    dbl dp[N + 1][M][2];
    for (int i=0; i<=N; ++i) {
        for (int j=0; j<M; ++j) {
            dp[i][j][0] = dp[i][j][1] = INF;
        }
    }

    for (int i=0; i<N; ++i) {
        debug(i);
        for (int t0m=0; t0m<M; ++t0m) {
            bool ok = false;
            for (dbl off = 0; off * MULT < 1 && !ok; off += 5e-7) {
                const dbl t0 = off + (dbl)(t0m) / MULT;
                const pt p(l0 * cos(t0), l0 * sin(t0));
                const pt t = A[i].first - p;
                const dbl a = l1, b = abs(t), c = l2;
                if (b > a + c) {
                    break;
                }
                const dbl t1 = normalize(acos((a*a + b*b - c*c) / (2 * a * b)) - t0);

                angle[i + 1][t0m][0][0] = t0;
                angle[i + 1][t0m][1][0] = t0;

                angle[i + 1][t0m][0][1] = normalize(t1 - arg(t));
                angle[i + 1][t0m][1][1] = normalize(t1 + arg(t));

                const dbl t2 = acos((a*a + c*c - b*b) / (2 * a * c));
                angle[i + 1][t0m][0][2] = normalize(PI - t2);
                angle[i + 1][t0m][1][2] = normalize(PI + t2);

                pt test0 =
                    l1 * pt(cos(angle[i + 1][t0m][0][1]), sin(angle[i + 1][t0m][0][1])) +
                    l2 * pt(cos(angle[i + 1][t0m][0][2]), sin(angle[i + 1][t0m][0][2]));
                pt test1 =
                    l1 * pt(cos(angle[i + 1][t0m][1][1]), sin(angle[i + 1][t0m][1][1])) +
                    l2 * pt(cos(angle[i + 1][t0m][1][2]), sin(angle[i + 1][t0m][1][2]));
                ok |= abs(test0 - t) < 1e-6 && abs(test1 - t) < 1e-6;
            }
            if (!ok) {
                angle[i + 1][t0m][0][0] = INF;
                angle[i + 1][t0m][0][1] = INF;
            }
        }
    }

    for (int t0=0; t0<M; ++t0) {
        angle[0][t0][0][0] = angle[0][t0][0][1] = angle[0][t0][1][0] = angle[0][t0][1][1] = 0;
    }
    dp[0][0][0] = dp[0][0][1] = 0;
    for (int i=1; i<=N; ++i) {
        for (int t0=0; t0<M; ++t0) {
            if (angle[i-1][t0][0][0] == INF) continue;
            for (int t00=0; t00<M; ++t00) {
                if (angle[i-1][t00][0][0] == INF) continue;
                if (chmn(dp[i][t0][0], dp[i-1][t00][0] + cost(angle[i-1][t00][0], angle[i][t0][0]))) {
                    ans[i][t0][0][0] = 0;
                    ans[i][t0][0][1] = t00;
                }
                if (chmn(dp[i][t0][0], dp[i-1][t00][1] + cost(angle[i-1][t00][1], angle[i][t0][0]))) {
                    ans[i][t0][0][0] = 1;
                    ans[i][t0][0][1] = t00;
                }
                if (chmn(dp[i][t0][1], dp[i-1][t00][0] + cost(angle[i-1][t00][0], angle[i][t0][1]))) {
                    ans[i][t0][1][0] = 0;
                    ans[i][t0][1][1] = t00;
                }
                if (chmn(dp[i][t0][1], dp[i-1][t00][1] + cost(angle[i-1][t00][1], angle[i][t0][1]))) {
                    ans[i][t0][1][0] = 1;
                    ans[i][t0][1][1] = t00;
                }
            }
        }
    }

    vector<pair<int, tuple<dbl, dbl, dbl>>> out;
    int cur = 0, t = 0;
    for (int t0=0; t0<M; ++t0) {
        if (dp[N][t0][0] < dp[N][t][cur]) {
            t = t0;
            cur = 0;
        }
        if (dp[N][t0][1] < dp[N][t][cur]) {
            t = t0;
            cur = 1;
        }
    }
    cerr << TEST << ": " << dp[N][t][0] << ' ' << dp[N][t][1] << '\n';
    for (int i=N; i>0; --i) {
        out.emplace_back(A[i - 1].second, make_tuple(angle[i][t][cur][0], angle[i][t][cur][1], angle[i][t][cur][2]));

        const int tmp_cur = cur;
        cur = ans[i][t][tmp_cur][0];
        t = ans[i][t][tmp_cur][1];
    }
    reverse(out.begin(), out.end());

    for (const pair<int, tuple<dbl, dbl, dbl>>& p: out) {
        dbl t0, t1, t2;
        tie(t0, t1, t2) = p.second;
        fout << p.first + 1 << ' ' << t0 << ' ' << t1 << ' ' << t2 << '\n';
    }
}
#endif

int main() {
    int _k;
    fin >> _k;
    assert(K == _k);

    dbl l0, l1, l2;
    fin >> l0 >> l1;
    if (K == 3) fin >> l2;

    int _n;
    fin >> _n;
    assert(N == _n);

    for (int i=0; i<N; ++i) {
        fin >> A[i].first;
        A[i].second = i;
    }
    sort(A, A+N);

#if TEST <= 8
    solve(l0, l1);
#else
    solve(l0, l1, l2);
#endif

    return 0;
}
