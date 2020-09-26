//1404c.cpp created at 09/25/20 18:01:52

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
const int MN = 301001;

ll N, M, K, Q;
ll A[MN];
vector<pii> query[MN];
int ans[MN];

int bit[MN];
void inc(int idx) {
    for (; idx<=N; idx+=idx&-idx) ++bit[idx];
}
int sum(int idx) {
    int ret = 0;
    for (; idx>0; idx-=idx&-idx) ret += bit[idx];
    return ret;
}
int sum_search(int val) {
    int idx = 0, cur = 0;
    for (int i=20; i>=0; --i) {
        if (idx + (1 << i) <= N && cur + bit[idx + (1 << i)] < val) {
            idx += (1 << i);
            cur += bit[idx];
        }
    }
    return idx + 1;
}
void solve(int testcase) {
    cin >> N >> Q;
    for (int i=1; i<=N; ++i) {
        cin >> A[i];
        A[i] = i - A[i];
    }
    debug1(A+1, N);
    for (int i=0; i<Q; ++i) {
        int l, r;
        cin >> l >> r;
        ++l;
        r = N-r;
        query[r].emplace_back(l, i);
    }

    for (int r=1; r<=N; ++r) {
        if (A[r] >= 0) {
            ll idx = sum_search(A[r]);
            idx = max(idx, N-r+1);
            inc(idx);
        }
        //cerr << A[r]; if (A[r] >= 0) cerr << ' ';cerr << ' ' << r << ": ";for (int j=N; j>0; --j) cerr << sum(j) << ' '; cerr << endl;
        for (int i=0; i<query[r].size(); ++i) {
            int l = query[r][i].FI;
            ans[query[r][i].SE] = sum(N-l+1); 
        }
    }
     
    for (int i=0; i<Q; ++i) {
        cout << ans[i] << '\n';
    }
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}
