//1427b.cpp created at 10/10/20 01:17:52

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
typedef pair<int,bool> pib;
typedef pair<ll,bool> plb;
typedef pair<double,double> pdd;
typedef map<ll,ll> mll;
typedef map<char, int> mci;
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

template <class T> void chmn(T& a, const T& b) {if (a>b) a=b;}
template <class T> void chmx(T& a, const T& b) {if (a<b) a=b;}

void setIO(const string& filename = "") {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
}

int chr[8] = {-1, 0, 1, 0, -1, -1, 1, 1};
int chc[8] = {0, 1, 0, -1, -1, 1, -1, 1};

const ll MOD = 1e9+7; //998244353;
const int INIT = 1001001001;
const int MN = 1001001;

ll N, M, K;
bool A[MN];
//ll G[MN][MN];
//set<ll> adj[MN];

inline const bool cmpdiff(const pll& a, const pll& b) {
    if (a.SE - a.FI == b.SE - b.FI) {
        return b.FI < a.FI;
    }
    return a.SE - a.FI < b.SE - b.FI;
}

void solve(int testcase) {
    cin >> N >> K;

    for (int i=0; i<N; ++i) {
        char c;
        cin >> c;
        A[i] = c == 'W';
    }

    vector<pll> gap;
    int len = 0;
    for (int i=0; i<N; ++i) {
        if (A[i]) {
            if (len > 0) {
                gap.PB(pll(i-len, i));
                if (gap.back().FI == 0) gap.back().FI = -INIT;
            }
            len = 0;
        } else {
            ++len;
        }
    }
    if (len > 0) {
        gap.PB(pll(N-len, INIT));
    }

    sort(all(gap), cmpdiff);
    debug(gap);
    for (int i=0; i<gap.size(); ++i) {
        if (gap[i].SE == N+1) --gap[i].SE;
        if (gap[i].FI <= 0) {
            for (int j=min(N, gap[i].SE) - 1; j>=gap[i].FI && j >= 0; --j) {
                if (K-- <= 0) break;
                A[j] = true;
            }
        }
        else {
            for (int j=max(0LL, gap[i].FI); j<N && j<gap[i].SE; ++j) {
                if (K-- <= 0) break;
                A[j] = true;
            }
        }
    }

    int score = 0;
    for (int i=0; i<N; ++i) {
        if (A[i]) {
            ++score;
            if (i > 0 && A[i-1]) {
                ++score;
            }
        }
    }
    debug1(A, N);

    cout << score << endl;        
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    cin >> T;
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}

/*
2
3 1
LWL
6 4
LLLLLW
*/
