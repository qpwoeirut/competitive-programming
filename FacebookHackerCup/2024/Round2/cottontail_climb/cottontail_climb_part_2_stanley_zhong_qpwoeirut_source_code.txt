//cottontail_climb.cpp created at 10/19/24 10:09:02
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <bits/stdc++.h>

using namespace __gnu_pbds;
using namespace std;

#define pb push_back
#define eb emplace_back
#define ins insert
#define emp emplace

#define fi first
#define se second
#define sz(obj) ((int)(obj.size()))
#define all(obj) begin(obj), end(obj)

#define LB lower_bound
#define UB upper_bound

using ll = long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using pcll = pair<const ll,ll>;

using ull = unsigned long long;
using dbl = long double;
using pib = pair<int,bool>;
using plb = pair<ll,bool>;
using pdd = pair<dbl,dbl>;
using mii = map<int,int>;
using mll = map<ll,ll>;
using mci = map<char,int>;
using msi = map<string,int>;
using mss = map<string,string>;

template <class T> using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
template <class T, class U> using ordered_map = tree<T,U,less<T>,rb_tree_tag,tree_order_statistics_node_update>;

ll binpow(ll x, ll p, const ll& mod) {assert(mod>0);
    ll ret = 1;
    for(; p>0; p>>=1, x = x*x % mod) if(p & 1) ret = ret*x % mod;
    return ret;
}

template <class T> bool chmn(T& a, const T& b) {return (greater<T>()(a, b) ? (a=b, true) : false);}
template <class T> bool chmx(T& a, const T& b) {return (less<T>()(a, b) ? (a=b, true) : false);}

template <class T> T square(const T& a) {return a*a;}
template <class T> T cube(const T& a) {return a*a*a;}

#ifdef DELETE_THIS_IN_CASE_OF_GEO
using _t=PUT_SMTH_HERE;
using pt=complex<_t>;

const dbl EPS = 1e-16;

#define x real()
#define y imag()

namespace std {
    inline bool operator<(const pt& a, const pt& b) {
        if (abs(a.x - b.x) > EPS) return a.x < b.x;
        if (abs(a.y - b.y) > EPS) return a.y < b.y;
        return false;
    }
    inline bool operator>(const pt& a, const pt& b) {
        return b < a;
    }
}

struct Line {
    pt p1, p2;
    Line() {
        p1 = p2 = pt(0, 0);
    }
    Line(const pt& _p1, const pt& _p2) {
        p1 = min(_p1, _p2);
        p2 = max(_p1, _p2);
    }
    Line(const _t a, const _t b, const _t c, const _t d) {
        p1 = pt(a, b);
        p2 = pt(c, d);
        if (p1 > p2) swap(p1, p2);
    }
    inline bool operator<(const Line& o) const {
        return p1 < o.p1 || (p1 == o.p1 && p2 < o.p2);
    }
};

namespace std {
    inline bool operator<(const Line& a, const Line& b) {
        return a.p1 < b.p1 || (a.p1 == b.p1 && a.p2 < b.p2);
    }
}

istream& operator>>(istream& is, pt& p) {
    _t a, b;
    is >> a >> b;
    p = pt(a, b);
    return is;
}
istream& operator>>(istream& is, Line& p) {
    _t a, b, c, d;
    is >> a >> b >> c >> d;
    p = Line(a, b, c, d);
    return is;
}

string to_string(const complex<_t>& p) {
    return "(" + to_string(p.x) + ", " + to_string(p.y) + ")";
}
string to_string(const Line& a) {
    return "(" + to_string(a.p1) + "--" + to_string(a.p2) + ")";
}
#endif

#ifdef LOCAL
#include "qpwoeirut/debug.h"
#else
#define debug
#define debug1
#define debug2
#define debug3
#endif

void setIO(const string& filename = "") {
    if (filename.size() > 0) {
        freopen((filename + ".in").c_str(), "r", stdin);
        freopen((filename + ".out").c_str(), "w", stdout);
    }
    cin.tie(0)->sync_with_stdio(0);
    // cout << fixed << setprecision(?);
}

const ll INF = 4e18;
const bool p1 = false;

// dp[idx][digit][is_max]
mll dp[20][10][2];

int digits(ll n, int d[]) {
    int len = 0;
    while (n > 0) {
        d[len] = n % 10;
        n /= 10;
        ++len;
    }
    reverse(d, d+len);
    return len;
}

ll p10(ll n, ll p, ll mod) {
    if (p == 0) return n;
    if (p == 1) return (n * 10) % mod;
    if (p == 2) return (n * 100) % mod;
    if (p == 3) return (n * 1000) % mod;
    if (p == 4) return (n * 10000) % mod;
    if (p == 5) return (n * 100000) % mod;
    if (p == 6) return (n * 1000000) % mod;
    if (p == 7) return (n * 10000000) % mod;
    if (p == 8) return (n * 100000000) % mod;
    return p10((n * 1000000000) % mod, p - 9, mod);
}

ll count(ll mx, ll mod) {
    if (mx <= 0) return 0;
    ll res = 0;
    for (int d=1; d<=9; ++d) {
        if (d % mod == 0) ++res;
    }

    //mll ansmap;
    //ansmap[1] = res;

    int mx_d[20];
    int mx_len = digits(mx, mx_d);
    for (int len=3; len < mx_len; len+=2) {
        for (int i=0; i<=len; ++i) {
            for (int d=0; d<=9; ++d) {
                dp[i][d][0].clear();
                dp[i][d][1].clear();
            }
        }

        for (int d=1; d<=9; ++d) {
            dp[1][d][0][p10(d, len - 1, mod)] = 1;
        }

        int mlen = (len + 1) / 2;
        for (int i=1; i<mlen; ++i) {
            for (int d0=1; d0<=9; ++d0) {
                const int dmn = d0 + (i + 1 == mlen);
                for (const auto& p: dp[i][d0][0]) {
                    if (p1) {
                        int d1 = d0 + 1;
                        if (d1 <= 9) dp[i+1][d1][0][(p.first + p10(d1, len - i - 1, mod)) % mod] += p.second;
                    } else {
                        for (int d1=dmn; d1<=9; ++d1) {
                            dp[i+1][d1][0][(p.first + p10(d1, len - i - 1, mod)) % mod] += p.second;
                        }
                    }
                }
            }
        }

        for (int i=mlen; i<len; ++i) {
            for (int d0=1; d0<=9; ++d0) {
                const int dmx = d0 - (i == mlen);
                for (const auto& p: dp[i][d0][0]) {
                    if (p.first + p10(1, len - i, INF) < mod) continue;
                    if (p1) {
                        int d1 = d0 - 1;
                        if (d1 > 0) dp[i+1][d1][0][(p.first + p10(d1, len - i - 1, mod)) % mod] += p.second;
                    } else {
                        for (int d1=1; d1<=dmx; ++d1) {
                            dp[i+1][d1][0][(p.first + p10(d1, len - i - 1, mod)) % mod] += p.second;
                        }
                    }
                }
            }
        }

        for (int d=1; d<=9; ++d) {
            res += dp[len][d][0][0];
            //ansmap[len] += dp[len][d][0][0];
        }
    }

    if (mx_len % 2 == 1 && mx_len >= 3) {
        for (int i=0; i<=mx_len; ++i) {
            for (int d=0; d<=9; ++d) {
                dp[i][d][0].clear();
                dp[i][d][1].clear();
            }
        }

        for (int d=1; d<=mx_d[0]; ++d) {
            dp[1][d][d == mx_d[0]][p10(d, mx_len - 1, mod)] = 1;
        }

        int mlen = (mx_len + 1) / 2;
        for (int i=1; i<mlen; ++i) {
            for (int d0=1; d0<=9; ++d0) {
                const int dmn = d0 + (i + 1 == mlen);
                for (const auto& p: dp[i][d0][0]) {
                    if (p1) {
                        int d1 = d0 + 1;
                        if (d1 <= 9) dp[i+1][d1][0][(p.first + p10(d1, mx_len - i - 1, mod)) % mod] += p.second;
                    } else {
                        for (int d1=dmn; d1<=9; ++d1) {
                            dp[i+1][d1][0][(p.first + p10(d1, mx_len - i - 1, mod)) % mod] += p.second;
                        }
                    }
                }
                for (const auto& p: dp[i][d0][1]) {
                    if (p1) {
                        int d1 = d0 + 1;
                        if (d1 <= mx_d[i]) dp[i+1][d1][d1 == mx_d[i]][(p.first + p10(d1, mx_len - i - 1, mod)) % mod] += p.second;
                    } else {
                        for (int d1=dmn; d1<=mx_d[i]; ++d1) {
                            dp[i+1][d1][d1 == mx_d[i]][(p.first + p10(d1, mx_len - i - 1, mod)) % mod] += p.second;
                        }
                    }
                }
            }
        }

        for (int i=mlen; i<mx_len; ++i) {
            for (int d0=1; d0<=9; ++d0) {
                const int dmx = d0 - (i == mlen);
                for (const auto& p: dp[i][d0][0]) {
                    if (p1) {
                        int d1 = d0 - 1;
                        if (d1 > 0) dp[i+1][d1][0][(p.first + p10(d1, mx_len - i - 1, mod)) % mod] += p.second;
                    } else {
                        for (int d1=1; d1<=dmx; ++d1) {
                            dp[i+1][d1][0][(p.first + p10(d1, mx_len - i - 1, mod)) % mod] += p.second;
                        }
                    }
                }
                for (const auto& p: dp[i][d0][1]) {
                    if (p1) {
                        int d1 = d0 - 1;
                        if (d1 > 0 && d1<=mx_d[i]) dp[i+1][d1][d1 == mx_d[i]][(p.first + p10(d1, mx_len - i - 1, mod)) % mod] += p.second;
                    } else {
                        for (int d1=1; d1<=mx_d[i]; ++d1) {
                            dp[i+1][d1][d1 == mx_d[i]][(p.first + p10(d1, mx_len - i - 1, mod)) % mod] += p.second;
                        }
                    }
                }
            }
        }

        for (int d=1; d<=9; ++d) {
            res += dp[mx_len][d][0][0] + dp[mx_len][d][1][0];
            //ansmap[mx_len] += dp[mx_len][d][0][0] + dp[mx_len][d][1][0];
        }
    }

    //debug(ansmap);
    return res;
}

ll brute(ll a, ll b, ll m) {
    ll ans = 0;
    mll ansmap;
    int d[20];
    for (ll x=m; x<=b; x+=m) {
        if (x < a) continue;
        int len = digits(x, d);
        if (len % 2 == 0) continue;

        bool ok = true;
        for (int i=0; i<len; ++i) ok &= d[i] > 0;

        int mlen = len / 2;
        for (int i=0; i<mlen; ++i) {
            if (d[i] > d[i+1]) ok = false;
        }
        if (len >= 3) {
            ok &= d[mlen - 1] < d[mlen];
            ok &= d[mlen] > d[mlen + 1];
        }
        for (int i=mlen+1; i<len; ++i) {
            if (d[i-1] < d[i]) ok = false;
        }
        ans += ok;
        ansmap[len] += ok;
    }
    debug(ansmap);
    return ans;
}

void solve(int testcase, ll a, ll b, ll m) {
    ll ans = count(b, m) - count(a - 1, m);
    
    cout << "Case #" << testcase << ": " << ans << '\n';
}

int main() {
    setIO();

    ll TEST_COUNT = 1;
    cin >> TEST_COUNT;

    for (int test_case=1; test_case<=TEST_COUNT; ++test_case) {
        ll a, b, m;
        cin >> a >> b;   
        cin >> m;

        solve(test_case, a, b, m);
        //cerr << brute(a, b, m) << endl;
    }

    return 0;
}
/*
8
0 1000000000000000000 1
0 1000000000000000000 2
0 1000000000000000000 22354
0 1000000000000000000 475853
0 1000000000000000000 445293
0 1000000000000000000 4645893
0 1000000000000000000 500000000
0 1000000000000000000 1000000000
*/
