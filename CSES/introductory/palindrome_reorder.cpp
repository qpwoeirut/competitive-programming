//palindrome_reorder.cpp created at 09/05/20 12:28:47

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

ll binpow(const ll& x, const ll& p, const ll& mod) {assert(mod>0);
	if (p == 0) return 1;
	if (p == 1) return x % mod;
	if (p & 1) return (binpow((x*x) % mod, p/2, mod) * x) % mod;
	return binpow((x*x) % mod, p/2, mod) % mod;
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
//ll A[MN];
//ll G[MN][MN];
//set<ll> adj[MN];

void solve(int testcase) {
    string s;
    cin >> s;

    N = sz(s);

    mci ct;
    for (int i=0; i<sz(s); i++) {
        ct[s[i]]++;
    }

    char odd = '*';
    string t(sz(s), '*');
    int L = 0, R = sz(s) - 1;
    for (mci::iterator it=ct.begin(); it!=ct.end(); it++) {
        if (it->SE & 1) {
            if (N & 1) {
                if (odd != '*') {
                    cout << "NO SOLUTION" << endl;
                    return;
                }
                odd = it->FI;
                --it->SE;
            } else {
                cout << "NO SOLUTION" << endl;
                return;
            }
        }
        for (int i=0; i<it->SE; i++) {
            if (i & 1) {
                t[R--] = it->FI;
            } else {
                t[L++] = it->FI;
            }
        }
    }

    if (N & 1) {
        if (odd == '*') {
            cout << "NO SOLUTION" << endl;
            return;
        }
        assert(L == R);
        t[L] = odd;
    }

    cout << t << endl;
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}
