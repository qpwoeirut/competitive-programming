//boring_numbers.cpp created at 11/14/20 19:07:12

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

void setIO(const string& filename = "") {
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

ll N, M, K;
ll A[MN];
//ll G[MN][MN];
//set<ll> adj[MN];

ll L, R;
ll p5[20];

vector<int> digits;
ll count(ll idx) {
    if (idx > digits.size()) return idx != 1;
    ll total = 0;

    for (int j=0; j<10; ++j) {
        if ((j & 1) == (idx & 1)) {
            if (j > digits[idx-1]) continue;
            debug(idx, j);
            if (j < digits[idx-1]) {
                total += p5[sz(digits) - idx];
            } else if (j == digits[idx-1]) {
                total += count(idx+1);
            }
        }
    }
    return total;
}

void solve(int testcase) {
    cin >> L >> R;

    digits.clear();
    while (R) {
        digits.push_back(R % 10);
        R /= 10;
    }
    reverse(all(digits));
    ll hi = count(1);
    debug(hi);
    for (int i=1; i<sz(digits); ++i) {
        hi += p5[i];
    }


    digits.clear();
    --L;
    while (L) {
        digits.push_back(L % 10);
        L /= 10;
    }
    reverse(all(digits));
    ll lo = count(1);
    debug(lo);
    for (int i=1; i<sz(digits); ++i) {
        lo += p5[i];
    }


    debug(lo, hi);
    cout << "Case #" << testcase << ": " << hi - lo << endl;
}
        
        
int main() {
    setIO();
    
    p5[0] = 1;
    for (int i=1; i<20; ++i) {
        p5[i] = p5[i-1] * 5;
    }

    ll T = 1;
    cin >> T;
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}
/*
3
5 15
120 125
779 783

1
1 1
*/
