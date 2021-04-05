//001a.cpp created at 03/12/21 17:08:11

#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "qpwoeirut/debug.h"
#else
#define debug
#define debug1
#define debug2
#define debug3
#endif

#define pb push_back
#define ins insert

#define fi first
#define se second
#define sz(obj) ((int)(obj.size()))
#define all(obj) begin(obj), end(obj)

#define LB lower_bound
#define UB upper_bound

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

typedef unsigned long long ull;
typedef long double dbl;
typedef pair<int,bool> pib;
typedef pair<ll,bool> plb;
typedef pair<dbl,dbl> pdd;
typedef map<int,int> mii;
typedef map<ll,ll> mll;
typedef map<char,int> mci;
typedef map<string,int> msi;
typedef map<string,string> mss;

ll gcd(ll a, ll b) {return b ? gcd(b, a%b) : a;}

ll binpow(ll x, ll p, const ll& mod) {assert(mod>0);
    ll ret = 1;
    for(; p>0; p>>=1, x = x*x % mod) if(p & 1) ret = ret*x % mod;
    return ret;
}

template <class T> bool chmn(T& a, const T& b) {return (greater<T>()(a, b) ? (a=b, true) : false);}
template <class T> bool chmx(T& a, const T& b) {return (less<T>()(a, b) ? (a=b, true) : false);}

template <class T> T square(const T& a) {return a*a;}
template <class T> T cube(const T& a) {return a*a*a;}

void setIO(const string& filename = "") {
    if (filename.size() > 0) {
        freopen((filename + ".in").c_str(), "r", stdin);
        freopen((filename + ".out").c_str(), "w", stdout);
    }
	cin.tie(0)->sync_with_stdio(0);
}

const int MN = 200;
const int MX = 10000;
const double STOP_TIME = 4.88;

struct Ad {
    int idx;
    ll x, y, r;
    ll x1, y1, x2, y2;

    void reset() {
        x1 = x;
        y1 = y;
        x2 = x + 1;
        y2 = y + 1;
    }
    
    inline dbl score() const {
        assert(x1 <= x && x < x2 && y1 <= y && y < y2);
        const ll s = area();
        return 1.0 - square(1.0 - (dbl(min(r, s)) / max(r, s)));
    }

    inline ll area() const {
        return (x2 - x1) * (y2 - y1);
    }

    void shrink() {
        if (area() <= r) return;

        ll best = 1, bw = 1, bh = 1;
        for (ll w=1; w+x1<=x2; ++w) {
            for (ll h=1; h+y1<=y2; ++h) {
                if (w*h <= r && best < w*h) {
                    best = w * h;
                    bw = w;
                    bh = h;
                }
            }
        }

        const ll dw = (x2 - x1) - bw;
        x1 += dw >> 1;
        x2 -= (dw + 1) >> 1;
        if (x < x1) {
            x2 -= x1 - x;
            x1 -= x1 - x;
        }
        if (x2 <= x) {
            x1 += x - x2 + 1;
            x2 += x - x2 + 1;
        }

        const ll dh = (y2 - y1) - bh;
        y1 += dh >> 1;
        y2 -= (dh + 1) >> 1;
        if (y < y1) {
            y2 -= y1 - y;
            y1 -= y1 - y;
        }
        if (y2 <= y) {
            y1 += y - y2 + 1;
            y2 += y - y2 + 1;
        }
    }

    inline bool x_cross(const Ad& o) const {
        return x1 < o.x2 && o.x1 < x2;
    }
    inline bool y_cross(const Ad& o) const {
        return y1 < o.y2 && o.y1 < y2;
    }
};

inline string to_string(const Ad& a) {
    return to_string(a.x) + ' ' + to_string(a.y) + ' ' + to_string(a.r) + '\n';
}

inline bool cmp_idx(const Ad& a, const Ad& b) {
    return a.idx < b.idx;
}
inline bool cmp_x(const Ad& a, const Ad& b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}
inline bool cmp_y(const Ad& a, const Ad& b) {
    return a.y < b.y || (a.y == b.y && a.x < b.x);
}
inline bool cmp_r(const Ad& a, const Ad& b) {
    return a.r < b.r || (a.r == b.r && (a.x < b.x || (a.x == b.x && a.y < b.y)));
}

ll N;
Ad ad_x[MN], ad_y[MN];

void change_y(Ad ad[]) {
    sort(ad, ad+N, cmp_x);
    for (int i=0; i<N; ++i) {
        ad[i].y1 = 0;
        ad[i].y2 = MX;
        for (int j=0; j<N; ++j) {
            if (i == j) continue;
            if (!ad[i].x_cross(ad[j])) continue;

            if (ad[j].y2 <= ad[i].y) {
                chmx(ad[i].y1, ad[j].y2);
            }
            if (ad[i].y <= ad[j].y1) {
                chmn(ad[i].y2, ad[j].y1);
            }

            assert(!(ad[j].y1 < ad[i].y && ad[i].y < ad[j].y2));
        }
        ad[i].shrink();
    }
}

void change_x(Ad ad[]) {
    sort(ad, ad+N, cmp_y);
    for (int i=0; i<N; ++i) {
        ad[i].x1 = 0;
        ad[i].x2 = MX;
        for (int j=0; j<N; ++j) {
            if (i == j) continue;
            if (!ad[i].y_cross(ad[j])) continue;

            if (ad[j].x2 <= ad[i].x) {
                chmx(ad[i].x1, ad[j].x2);
            }
            if (ad[i].x <= ad[j].x1) {
                chmn(ad[i].x2, ad[j].x1);
            }

            assert(!(ad[j].x1 < ad[i].x && ad[i].x < ad[j].x2));
        }
        ad[i].shrink();
    }
}
        
void save(Ad ad[], Ad ans[], dbl& score) {
    dbl new_score = 0;
    for (int i=0; i<N; ++i) {
        new_score += ad[i].score();
    }

    if (score < new_score) {
        score = new_score;
        copy(ad, ad+N, ans);
    }
}

void print(Ad ans[]) {
    sort(ans, ans+N, cmp_idx);
    for (int i=0; i<N; ++i) {
        cout << ans[i].x1 << ' ' << ans[i].y1 << ' ' << ans[i].x2 << ' ' << ans[i].y2 << '\n';
    }
}

Ad ans_x[MN], ans_y[MN];

using namespace chrono;

// timing stuff ripped off from https://codeforces.com/gym/102646/submission/86954384
int main() {
    setIO();

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> ad_x[i].x >> ad_x[i].y >> ad_x[i].r;
        ad_x[i].idx = i;
    }
    copy(ad_x, ad_x+N, ad_y);

    for (int i=0; i<N; ++i) {
        ad_x[i].reset();
        ad_y[i].reset();
    }

    dbl x_first = 0, y_first = 0;
    const auto start_time = high_resolution_clock::now();
    do {
        change_x(ad_x);
        change_y(ad_x);

        save(ad_x, ans_x, x_first);
        debug(x_first);
    } while (duration_cast<duration<double>>(high_resolution_clock::now() - start_time).count()*2 < STOP_TIME);

    do {
        change_y(ad_y);
        change_x(ad_y);

        save(ad_y, ans_y, y_first);
        debug(y_first);
    } while (duration_cast<duration<double>>(high_resolution_clock::now() - start_time).count() < STOP_TIME);

    if (x_first >= y_first) {
        print(ans_x);
    } else {
        print(ans_y);
    }

    const dbl score = max(x_first, y_first) * 1e9 / N;
    debug(score);
}
/*
10
5000 0 10000000
5100 0 10000000
5200 0 10000000
5300 0 10000000
5400 0 10000000
5500 0 10000000
5600 0 10000000
5700 0 10000000
5800 0 10000000
5900 0 10000000
*/
