//calendars.cpp created at 11/14/20 09:19:59

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
ll A[MN], B[MN];
ll pa[MN], pb[MN];
//ll G[MN][MN];
//set<ll> adj[MN];

ll sum(const multiset<ll>& ms) {
    ll ret = 0;
    for (auto it=ms.begin(); it!=ms.end(); ++it) ret += abs(*it);
    return ret;
}
ll sum(const multiset<ll, greater<ll>>& ms) {
    ll ret = 0;
    for (auto it=ms.begin(); it!=ms.end(); ++it) ret += abs(*it);
    return ret;
}

void solve(int testcase) {
    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
        pa[A[i]] = i;
    }
    for (int i=0; i<N; ++i) {
        cin >> B[i];
        pb[B[i]] = i;
    }

    multiset<ll, greater<ll>> neg;
    multiset<ll> pos;
    for (int i=1; i<=N; ++i) {
        if (pa[i] - pb[i] >= 0) {
            pos.insert(pa[i] - pb[i]);
        } else {
            neg.insert(pa[i] - pb[i]);
        }
    }
    ll ans = sum(neg) + sum(pos);
    debug(ans);

    ll cur = sum(neg) + sum(pos);
    debug(cur, neg, pos);

    for (int i=1; i<N; ++i) {
        while (neg.size() > 0 && *neg.begin() > -i) {
            pos.insert(*neg.begin());
            neg.erase(neg.begin());
        }

        ll rot = pa[B[i-1]] - pb[B[i-1]];
        debug(i, B[i-1], rot, pa[B[i-1]]);
        if (rot > -i) {
            pos.erase(pos.find(rot));
        } else {
            neg.erase(neg.find(rot));
        }
        cur -= abs(pa[B[i-1]]);
        cur += abs(N - pa[B[i-1]] - 1);
        debug(cur, neg, pos);
        cur += sz(pos) - sz(neg);
        neg.insert(rot - N);
        chmn(ans, cur);
        debug(cur, neg, pos);
    }

    cout << ans << endl;
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}
/*
4
1 4 2 3
2 4 3 1
*/
