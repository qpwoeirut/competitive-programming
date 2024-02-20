#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define eb emplace_back

#define x real()
#define y imag()

#define fi first
#define se second

typedef long long ll;
typedef complex<ll> pt;
typedef pair<pt,pt> line;
typedef pair<int,int> pii;

bool cmp(const pt& a, const pt& b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

const int MN = 41;
const int MOD = 1e9 + 7;

int N;
pt A[MN];

// dp[n][a][b][c] = # of perms of len n such that outer triangle has points (a, b, c)
ll dp[MN][MN][MN][MN];

int ccw(const pt& a, const pt& b, const pt& c) {
    if (a == b || a == c || b == c) return 0;
    int dx1 = b.x - a.x;
    int dy1 = b.y - a.y;
    int dx2 = c.x - a.x;
    int dy2 = c.y - a.y;

    if (dx1 * dy2 > dx2 * dy1) return -1;
    else if (dx1 * dy2 < dx2 * dy1) return 1;
    else assert(0);
}

bool intersect(const pt& p1, const pt& p2, const pt& p3, const pt& p4) {
    return ccw(p1, p2, p3) * ccw(p1, p2, p4) == -1 && ccw(p3, p4, p1) * ccw(p3, p4, p2) == -1;
}

bool in_triangle(const pt& a, const pt& b, const pt& c, const pt& d) {
    if (a == d || b == d || c == d) return true;
    const int orientation = ccw(a, b, d);
    return ccw(b, c, d) == orientation && ccw(c, a, d) == orientation;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        int px, py;
        cin >> px >> py;
        A[i] = pt(px, py);
    }

    for (int a=0; a<N; ++a) {
        for (int b=a+1; b<N; ++b) {
            for (int c=b+1; c<N; ++c) {
                dp[3][a][b][c] = 3 * 2 * 1;
            }
        }
    }

    for (int i=3; i<N; ++i) {
        for (int a=0; a<N; ++a) {
            for (int b=a+1; b<N; ++b) {
                for (int c=b+1; c<N; ++c) {
                    int internal = 0;
                    for (int d=0; d<N; ++d) {
                        internal += in_triangle(A[a], A[b], A[c], A[d]);
                    }
                    dp[i+1][a][b][c] += ((internal - i) * dp[i][a][b][c]) % MOD;
                    if (dp[i+1][a][b][c] >= MOD) dp[i+1][a][b][c] -= MOD;
                    for (int d=0; d<N; ++d) {
                        if (a == d || b == d || c == d) continue;

                        int idx[3] = {a, b, c};

                        if (!intersect(A[a], A[b], A[c], A[d]) && !intersect(A[b], A[c], A[a], A[d]) &&
                            !intersect(A[a], A[c], A[b], A[d]) && !in_triangle(A[a], A[b], A[c], A[d])) {

                            if (ccw(A[b], A[a], A[d]) != ccw(A[c], A[a], A[d])) idx[0] = d;
                            if (ccw(A[a], A[b], A[d]) != ccw(A[c], A[b], A[d])) idx[1] = d;
                            if (ccw(A[a], A[c], A[d]) != ccw(A[b], A[c], A[d])) idx[2] = d;
                            if (idx[0] > idx[2]) {
                                swap(idx[0], idx[1]);
                                swap(idx[1], idx[2]);
                            }
                            if (idx[0] > idx[1]) {
                                swap(idx[0], idx[1]);
                            }
                            if (idx[1] > idx[2]) {
                                swap(idx[1], idx[2]);
                            }

                            dp[i+1][idx[0]][idx[1]][idx[2]] += dp[i][a][b][c];
                        }
                    }
                }
            }
        }
    }
    
    //for (int i=3; i<=N; ++i) {
    //    for (int a=0; a<N; ++a) {
    //        for (int b=a+1; b<N; ++b) {
    //            for (int c=b+1; c<N; ++c) {
    //                cerr << i << ' ' << a << ' ' << b << ' ' << c << " = " << dp[i][a][b][c] << endl;
    //            }
    //        }
    //    }
    //}

    ll ans = 0;
    for (int a=0; a<N; ++a) {
        for (int b=a+1; b<N; ++b) {
            for (int c=b+1; c<N; ++c) {
                ans += dp[N][a][b][c];
                if (ans >= MOD) ans -= MOD;
            }
        }
    }

    cout << ans << '\n';
}
