//13b.cpp created at 02/19/21 16:29:27

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

#define PB push_back
#define INS insert

#define FI first
#define SE second
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

template <class T1,class T2> struct cmpf {
	bool rev;
	inline bool operator()(const pair<T1,T2>& a, const pair<T1,T2>& b) const {return (a.first<b.first)^rev;}
	cmpf(bool b=false) {rev=b;}
};
template <class T1,class T2> struct cmps {
	bool rev;
	inline bool operator()(const pair<T1,T2>& a, const pair<T1,T2>& b) const {return (a.second<b.second)^rev;}
	cmps(bool b=false) {rev=b;}
};

ll binpow(ll x, ll p, const ll& mod) {assert(mod>0);
    ll ret = 1;
    for(; p>0; p>>=1, x = x*x % mod) if(p & 1) ret = ret*x % mod;
    return ret;
}

template <class T> bool chmn(T& a, const T& b) {return (greater<T>()(a, b) ? (a=b, true) : false);}
template <class T> bool chmx(T& a, const T& b) {return (less<T>()(a, b) ? (a=b, true) : false);}

void setIO(const string& filename = "") {
    if (filename.size() > 0) {
        freopen((filename + ".in").c_str(), "r", stdin);
        freopen((filename + ".out").c_str(), "w", stdout);
    }
	cin.tie(0)->sync_with_stdio(0);
}

int chr[8] = {-1, 0, 1, 0, -1, -1, 1, 1};
int chc[8] = {0, 1, 0, -1, -1, 1, -1, 1};

const ll MOD = 1e9+7; //998244353 //1e9+9 //1e9+21 // 1e9+33;
const int INIT = 1001001001;
const int MN = 1001001;
const ll INF = 2e18 + 1;

ll N, M, K, Q;
//ll A[MN], B[MN];
//ll G[MN][MN];
//set<ll> adj[MN];

const double EPS = 1e-16;

struct Segment {
    ll x1, y1, x2, y2;

    inline const bool operator<(const Segment& o) const {
        if (x1 == o.x1) {
            if (y1 == o.y1) {
                if (x2 == o.x2) {
                    return y2 < o.y2;
                }
                return x2 < o.x2;
            }
            return y1 < o.y1;
        }
        return x1 < o.x1;
    }
};

Segment A[3];

bool on_seg(const Segment seg, const ll x, const ll y) {
    if (x < min(seg.x1, seg.x2) || max(seg.x1, seg.x2) < x) return false;
    if (y < min(seg.y1, seg.y2) || max(seg.y1, seg.y2) < y) return false;
    ll dx1 = seg.x1 - x, dy1 = seg.y1 - y;
    ll dx2 = seg.x2 - x, dy2 = seg.y2 - y;

    return dx1 * dy2 == dx2 * dy1;
}

dbl dist(const ll x1, const ll y1, const ll x2, const ll y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

string to_string(Segment s) {
    return "(" + to_string(s.x1) + ", " + to_string(s.y1) + ") " + "(" + to_string(s.x2) + ", " + to_string(s.y2) + ")";
}

const double PI = acos(-1.0);

bool check() {
    if (A[0].x1 != A[1].x1 || A[0].y1 != A[1].y1) return false;
    debug1(A, 3);
    if (!on_seg(A[0], A[2].x1, A[2].y1) || !on_seg(A[1], A[2].x2, A[2].y2)) return false;

    dbl d1 = dist(A[0].x1, A[0].y1, A[2].x1, A[2].y1);
    dbl d2 = dist(A[0].x2, A[0].y2, A[2].x1, A[2].y1);
    debug(d1, d2);
    if (min(d1, d2) * 4 < max(d1, d2)) return false;

    d1 = dist(A[1].x1, A[1].y1, A[2].x2, A[2].y2);
    d2 = dist(A[1].x2, A[1].y2, A[2].x2, A[2].y2);
    if (min(d1, d2) * 4 < max(d1, d2)) return false;

    ll x1 = A[0].x2 - A[0].x1, y1 = A[0].y2 - A[0].y1;
    ll x2 = A[1].x2 - A[1].x1, y2 = A[1].y2 - A[1].y1;

    double angle = abs(atan2(y1, x1) - atan2(y2, x2));
    debug(PI, angle, angle*180.0/PI);

    return EPS < angle && angle <= PI + EPS;
}

void solve(int testcase) {
    for (int i=0; i<3; ++i) {
        cin >> A[i].x1 >> A[i].y1 >> A[i].x2 >> A[i].y2;
    }
    sort(A, A+3);

    do {
        for (int i=0; i<8; ++i) {
            for (int j=0; j<3; ++j) {
                if ((i >> j) & 1) {
                    swap(A[j].x1, A[j].x2);
                    swap(A[j].y1, A[j].y2);
                }
            }
            if (check()) {
                cout << "YES\n";
                return;
            }
            for (int j=0; j<3; ++j) {
                if ((i >> j) & 1) {
                    swap(A[j].x1, A[j].x2);
                    swap(A[j].y1, A[j].y2);
                }
            }
        }
    }
    while (next_permutation(A, A+3));    

    cout << "NO\n";
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    cin >> T;
    
    for (int t=1; t<=T; ++t) {
        solve(t);
    }
    
    return 0;
}
/*
1
0 0 -5 -10
0 0 5 -10
-3 -5 3 -5

1
0 0 -4 -10
0 0 4 -10
-2 -5 2 -5

1
0 0 -2 -5
0 0 2 -5
-4 -10 4 -10
*/
