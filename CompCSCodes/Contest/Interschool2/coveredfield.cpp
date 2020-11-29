//coveredfield.cpp created at 11/21/20 11:48:03

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

template <class T> bool chmn(T& a, const T& b) {return ((a>b) ? ((a=b) || true) : false);}
template <class T> bool chmx(T& a, const T& b) {return ((a<b) ? ((a=b) || true) : false);}

void setIO(const string& filename = "coveredfield") {
    cin.tie(0)->sync_with_stdio(0);
    if (filename.size() > 0) {
        freopen((filename + ".in").c_str(), "r", stdin);
        freopen((filename + ".out").c_str(), "w", stdout);
    }
}

int chr[8] = {-1, 0, 1, 0, -1, -1, 1, 1};
int chc[8] = {0, 1, 0, -1, -1, 1, -1, 1};

const ll MOD = 1e9+7; //998244353 //1e9+9 //1e9+21 // 1e9+33;
const int INIT = 1001001001;
const int MN = 1001001;

struct Rect {
    ll x1, y1, x2, y2;

    inline const bool operator<(const Rect& other) const {
        if (x1 == other.x1) {
            if (y1 == other.y1) {
                if (x2 == other.x2) return y2 < other.y2;
                return x2 < other.x2;
            }
            return y1 < other.y1;
        }
        return x1 < other.x1;
    }
};
struct cmp_y {
    inline const bool operator()(const Rect& a, const Rect& b) const {
        if (a.y1 == b.y1) {
            if (a.x1 == b.x1) {
                if (a.y2 == b.y2) return a.x2 < b.x2;
                return a.y2 < b.y2;
            }
            return a.x1 < b.x1;
        }
        return a.y1 < b.y1;
    }
};

struct Item {
    ll val;
    Rect r;
    bool start;

    Item(int _val, Rect _r, bool _start) { 
        val = _val;
        r = _r;
        start = _start;
    }
    inline const bool operator<(const Item& other) const {
        if (val == other.val) return start < other.start;
        return val < other.val;
    }
};

ll N, M, K;
Rect A[MN];
//ll G[MN][MN];
//set<ll> adj[MN];

ll ans[MN];
void solve(int testcase) {
    cin >> N >> M;

    multiset<Item> x;
    for (int i=0; i<N; ++i) {
        cin >> A[i].x1 >> A[i].y1 >> A[i].x2 >> A[i].y2;
        ++A[i].x2; ++A[i].y2;
        x.emplace(A[i].x1, A[i], true);
        x.emplace(A[i].x2, A[i], false);
    }

    multiset<pll> cur;
    ll xprev = x.begin()->val;
    for (auto xit=x.begin(); xit!=x.end(); ++xit) {
        int screws = 0;
        if (cur.size() > 0) {
            ll yprev = cur.begin()->FI;
            for (auto yit=cur.begin(); yit!=cur.end(); ++yit) {
                ans[screws] += (yit->FI - yprev) * (xit->val - xprev);
                screws += yit->SE;
                yprev = yit->FI;
            }
        }

        if (xit->start) {
            cur.emplace(xit->r.y1, 1);
            cur.emplace(xit->r.y2, -1);
        } else {
            cur.erase(cur.find(pii(xit->r.y1, 1)));
            cur.erase(cur.find(pii(xit->r.y2, -1)));
        }

        xprev = xit->val;
    }
    
    for (int i=N; i>0; --i) {
        ans[i-1] += ans[i];
    }
    for (int i=1; i<=M; ++i) {
        cout << ans[i] << '\n';
    }
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}
