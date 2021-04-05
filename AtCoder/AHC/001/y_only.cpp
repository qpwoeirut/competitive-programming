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
const double STOP_TIME = 4.85;

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
    
    inline const dbl score() const {
        if (!(x1 <= x && x < x2 && y1 <= y && y < y2)) return 0.0;
        const ll s = area();
        return 1.0 - square(1.0 - (dbl(min(r, s)) / max(r, s)));
    }

    inline const ll area() const {
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

        const int choice = rand() & 3;
        if (choice & 1) {
            x2 = max(x+1, x1 + bw);
            x1 = x2 - bw;
        } else {
            x1 = min(x, x2 - bw);
            x2 = x1 + bw;
        }

        if (choice & 2) {
            y2 = max(y+1, y1 + bh);
            y1 = y2 - bh;
        } else {
            y1 = min(y, y2 - bh);
            y2 = y1 + bh;
        }
    }

    inline const bool x_cross(const Ad& o) const {
        return x1 < o.x2 && o.x1 < x2;
    }
    inline const bool y_cross(const Ad& o) const {
        return y1 < o.y2 && o.y1 < y2;
    }
};

inline const bool cmp_idx(const Ad& a, const Ad& b) {
    return a.idx < b.idx;
}
inline const bool cmp_x(const Ad& a, const Ad& b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}
inline const bool cmp_y(const Ad& a, const Ad& b) {
    return a.y < b.y || (a.y == b.y && a.x < b.x);
}
inline const bool cmp_r(const Ad& a, const Ad& b) {
    return a.r < b.r || (a.r == b.r && (a.x < b.x || (a.x == b.x && a.y < b.y)));
}

ll N;
Ad ad[MN];

void solve() {
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
        
Ad ans[MN];
dbl score = 0;
void save() {
    dbl new_score = 0;
    for (int i=0; i<N; ++i) {
        new_score += ad[i].score();
    }
    if (score < new_score) {
        score = new_score;
        copy(ad, ad+N, ans);
    }
}

void print() {
    sort(ans, ans+N, cmp_idx);
    for (int i=0; i<N; ++i) {
        cout << ans[i].x1 << ' ' << ans[i].y1 << ' ' << ans[i].x2 << ' ' << ans[i].y2 << '\n';
    }
}

// timing stuff ripped off from https://codeforces.com/gym/102646/submission/86954384
int main() {
    auto start_time = chrono::high_resolution_clock::now();
    setIO();

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> ad[i].x >> ad[i].y >> ad[i].r;
        ad[i].idx = i;
    }

    for (int i=0; i<N; ++i) {
        ad[i].reset();
    }

    chrono::high_resolution_clock::time_point now;
    int ct = 0;
    do {
        solve();
        debug(++ct, score);
        now = chrono::high_resolution_clock::now();

        save();
    } while (chrono::duration_cast<chrono::duration<double>>(now - start_time).count() < STOP_TIME);

    print();

    score *= 1e9 / N;
    debug(score);
}

