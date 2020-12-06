//525e.cpp created at 12/03/20 11:07:20

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
const int MN = 27;

ll N, K, S;
ll A[MN], fact[MN];

mll m[MN][2];
void solve(int testcase) {
    cin >> N >> K >> S;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }

    fact[0] = 1;
    for (int i=1; i<=18; ++i) fact[i] = fact[i-1] * i;

    m[0][0][0] = m[0][1][0] = 1;
    for (int i=0; i<N; ++i) {
        const int idx = i >= (N >> 1);
        for (int j=K; j>=0; --j) {
            mll tmp;
            for (auto it=m[j][idx].begin(); it!=m[j][idx].end(); ++it) {
                if (it->FI + A[i] <= S) {
                    tmp[it->FI + A[i]] += it->SE;
                    if (j<K && A[i] <= 18 && it->FI + fact[A[i]] <= S) {
                        m[j+1][idx][it->FI + fact[A[i]]] += it->SE;
                    }
                }
            }
            for (auto it=tmp.begin(); it!=tmp.end(); ++it) {
                m[j][idx][it->FI] += it->SE;
            }
        }
    }
    for (int i=0; i<K; ++i) {
        for (auto it=m[i][1].begin(); it!=m[i][1].end(); ++it) {
            m[i+1][1][it->FI] += it->SE;
        }
    }

    ll ans = 0;
    for (int i=0; i<=K; ++i) {
        for (auto it1=m[i][0].begin(); it1!=m[i][0].end(); ++it1) {
            auto it2 = m[K-i][1].find(S - it1->FI);
            if (it1 == m[K-i][1].end()) continue;
            ans += it1->SE * it2->SE;
        }
    }

    cout << ans << endl;
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}
