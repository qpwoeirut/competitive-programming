//HIRINGWO.cpp created at 11/22/20 08:23:18

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

ll N, M, K, X;
ll A[MN];
//ll G[MN][MN];
//set<ll> adj[MN];

ll spf[MN];
vector<ll> teams;

ll ans;
vector<ll> sums;

void recurse(int idx, int k) {
    if (idx == M && k == K-1) {
        ll sum = 0;
        for (int i=0; i<sz(sums); ++i) sum += sums[i];
        if (chmn(ans, sum)) debug(sums);
        return;
    }
    if (idx >= M || k >= K) return;

    sums.back() *= teams[idx];
    recurse(idx+1, k);
    sums.back() /= teams[idx];
    sums.push_back(teams[idx]);
    recurse(idx+1, k+1);
    sums.pop_back();
}

void solve(int testcase) {
    cin >> K >> X;

    teams.clear();
    ans = 0;

    mll factors;
    ll x = X;
    while (x > 1) {
        ++factors[spf[x]];
        x /= spf[x];
    }

    ll sum = 0;
    for (auto it=factors.begin(); it!=factors.end(); ++it) {
        ll cur = binpow(it->FI, it->SE, MOD);
        teams.push_back(cur);
        sum += cur;
    }
    debug(factors);
    debug(teams);

    if (sz(teams) <= K) {
        ans = sum + K - sz(teams);
    } else {
        assert(sz(teams) < 8);
        sort(all(teams));
        M = sz(teams);

        ans = X + K - 1;
        do {
            sums.clear();
            sums.push_back(1);
            recurse(0, 0);
        } while (next_permutation(all(teams)));
    }

    cout << ans << endl;
}
        
        
int main() {
    setIO();

    spf[1] = 1;
    for (int i=2; i<MN; ++i) {
        spf[i] = (i & 1) ? i : 2;
    }
    for (int i=3; i*i<MN; ++i) {
        if (spf[i] == i) {
            for (int j=i*i; j<MN; j+=i) {
                if (spf[j] == j) {
                    spf[j] = i;
                }
            }
        }
    }

    ll T = 1;
    cin >> T;
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}
/*
11
2 32
3 32
2 210
3 210
4 210
5 210
2 510510
3 510510
4 510510
2 3
2 6 6
*/
