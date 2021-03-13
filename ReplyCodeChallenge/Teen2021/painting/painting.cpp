//p4.cpp created at 03/11/21 00:25:10

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

void setIO(const string& filename = "painting") {
    if (filename.size() > 0) {
        freopen((filename + ".in").c_str(), "r", stdin);
        freopen((filename + ".out").c_str(), "w", stdout);
    }
    cin.tie(0)->sync_with_stdio(0);
    cout << fixed << setprecision(32);
    cerr << fixed << setprecision(10);
}

int chr[8] = {-1, 0, 1, 0, -1, -1, 1, 1};
int chc[8] = {0, 1, 0, -1, -1, 1, -1, 1};

const ll MOD = 1e9+7; //998244353; //1e9+9; //1e9+21; //1e9+33;
const int INIT = 1001001001;
const int MN = 1001001;
const int LG = 24;
const ll INF = 2e18 + 1;
const dbl EPS = 1e-24;

ll N, M, K, Q;
dbl A[MN], B[MN];
//ll G[MN][MN];
//set<ll> adj[MN];

typedef complex<dbl> pt;

#define x real()
#define y imag()

bool cmp(const pt& a, const pt& b) {
    return (b.x - a.x) >= EPS || (fabs(a.x - b.x) < EPS && a.y < b.y);
}

bool cmpx(const pt& a, const pt& b) {
    return fabs(a.x - b.x) < EPS;
}

dbl dot(const pt& a, const pt& b) {
    return (conj(a) * b).x;
}
dbl cross(const pt& a, const pt& b) {
    return (conj(a) * b).y;
}

pt intersect(const pt& p, const pt& q) {
    assert(p.x != q.x);
    const dbl px = (q.y - p.y) / (p.x - q.x);
    const dbl py = p.x * px + p.y;
    return pt(px, py);
}

vector<pt> hull, vecs;
void add_line(const pt& nw) {
    while (!vecs.empty() && dot(vecs.back(), nw - hull.back()) > 0) {
        hull.pop_back();
        vecs.pop_back();
    }
    if (!hull.empty()) {
        vecs.push_back(pt(0, 1) * (nw - hull.back()));
    }
    hull.push_back(nw);
}

dbl area(const vector<pt>& poly) {
    dbl res = 0;
    for (int i=0; i<poly.size(); i++) {
        pt p = i ? poly[i - 1] : poly.back();
        pt q = poly[i];
        res += (p.x - q.x) * (p.y + q.y);
    }
    return fabs<dbl>(res) / 2;
}

void solve(int testcase) {
    debug(testcase);
    hull.clear(); vecs.clear();
    vector<pt> top, bottom;
    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i] >> B[i];
        if (B[i] > 0) {
            top.pb(pt(A[i], -B[i]));
        } else if (B[i] < 0) {
            bottom.pb(pt(A[i], B[i]));
        } else assert(0);
    }
    //for (int i=0; i<N; ++i) { cerr << A[i] << "x + " << B[i] << endl; }

    sort(all(top), cmp);
    reverse(all(top));
    top.resize(unique(all(top), cmpx) - top.begin());
    reverse(all(top));

    sort(all(bottom), cmp);
    reverse(all(bottom));
    bottom.resize(unique(all(bottom), cmpx) - bottom.begin());
    reverse(all(bottom));

    //debug(top);
    //debug(bottom);

    for (const pt& p: bottom) {
        add_line(p);
    }
    deque<pt> bhull(all(hull));
    hull.clear(); vecs.clear();

    for (const pt& p: top) {
        add_line(p);
    }
    deque<pt> thull;
    for (pt& p: hull) {
        thull.pb(pt(p.x, -p.y));
    }
    hull.clear(); vecs.clear();

    if (bhull.empty() || thull.empty()) {
        cout << "inf\n";
        return;
    }

    //debug(bhull);
    //debug(thull);

    int idx;
    dbl intx;

    bool change = true;
    while (change) {
        change = false;
        idx = -1;
        intx = 1e18;
        for (int i=0; i<bhull.size(); ++i) {
            const pt inter = intersect(thull[0], bhull[i]);
            if (inter.x > 0 && inter.x < intx) {
                idx = i;
                intx = inter.x;
            }
        }
        debug(idx);
        if (idx == -1) {
            cout << "Case #" << testcase << ": inf" << '\n';
            return;
        }
        while (bhull.size() > idx+1) {
            bhull.pop_back();
            change = true;
        }

        idx = -1;
        intx = -1e18;
        for (int i=0; i<bhull.size(); ++i) {
            const pt inter = intersect(thull.back(), bhull[i]);
            if (inter.x < 0 && inter.x > intx) {
                idx = i;
                intx = inter.x;
            }
        }
        debug(idx);
        if (idx == -1) {
            cout << "Case #" << testcase << ": inf" << '\n';
            return;
        }
        while (idx-- > 0) {
            bhull.pop_front();
            change = true;
        }

        idx = -1;
        intx = 1e18;
        for (int i=0; i<thull.size(); ++i) {
            const pt inter = intersect(bhull.back(), thull[i]);
            if (inter.x > 0 && inter.x < intx) {
                idx = i;
                intx = inter.x;
            }
        }
        debug(idx);
        if (idx == -1) {
            cout << "Case #" << testcase << ": inf" << '\n';
            return;
        }
        while (idx-- > 0) {
            thull.pop_front();
            change = true;
        }

        idx = -1;
        intx = -1e18;
        for (int i=0; i<thull.size(); ++i) {
            const pt inter = intersect(bhull[0], thull[i]);
            if (inter.x < 0 && inter.x > intx) {
                idx = i;
                intx = inter.x;
            }
        }
        debug(idx);
        if (idx == -1) {
            cout << "Case #" << testcase << ": inf" << '\n';
            return;
        }
        while (thull.size() > idx+1) {
            thull.pop_back();
            change = true;
        }
    
        //debug(bhull); debug(thull);
    }

    vector<pt> pts;
    for (int i=0; i<bhull.size(); ++i) {
        if (i+1 < bhull.size()) {
            pts.pb(intersect(bhull[i], bhull[i+1]));
        } else {
            if (fabs(bhull[i].x - thull[0].x) < EPS) {
                debug(bhull[i], thull[0]);
                cout << "Case #" << testcase << ": inf" << '\n';
                return;
            }
            pts.pb(intersect(bhull[i], thull[0]));
            if (pts.back().x <= 0) {
                debug(pts.back());
                cout << "Case #" << testcase << ": inf" << '\n';
                return;
            }
        }
    }
    for (int i=0; i<thull.size(); ++i) {
        if (i+1 < thull.size()) {
            pts.pb(intersect(thull[i], thull[i+1]));
            debug(i, pts.back());
        } else {
            if (fabs(thull[i].x - bhull[0].x) < EPS) {
                debug(thull[i], bhull[0]);
                cout << "Case #" << testcase << ": inf" << '\n';
                return;
            }
            pts.pb(intersect(thull[i], bhull[0]));
            if (pts.back().x >= 0) {
                debug(pts.back());
                cout << "Case #" << testcase << ": inf" << '\n';
                return;
            }
        }
    }
    //debug(pts);
    //for (pt p: pts) { cerr << to_string(p) << '\n'; }
    const dbl ans = area(pts);
    cout << "Case #" << testcase << ": " << ans << '\n';
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    cin >> T;
    
    for (int test_case=1; test_case<=T; ++test_case) {
        solve(test_case);
    }
    
    return 0;
}
