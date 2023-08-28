//1472e.cpp created at 01/04/21 06:56:44

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

//template <class T> bool chmn(T& a, const T& b) {return ((a>b) ? ((a=b) || true) : false);}
bool chmn(pll& a, const pll& b) {
    if (a>b) {
        a=b;
        return true;
    }
    return false;
}
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
pll A[MN];
pll BIT[MN];
int ans[MN];
//ll G[MN][MN];
//set<ll> adj[MN];

void upd(int idx, const pll& val) {
    for (; idx<=N+N; idx+=(idx & -idx)) chmn(BIT[idx], val);
}
pll query(int idx) {
    pll ret(INIT, INIT);
    for (; idx>0; idx-=(idx & -idx)) chmn(ret, BIT[idx]);
    return ret;
}

void solve(int testcase) {
    fill(BIT, BIT+ N + N + 5, pll(INIT, INIT));
    vector<int> num;
    for (int i=0; i<N; ++i) {
        num.push_back(A[i].FI);
        num.push_back(A[i].SE);
    }
    sort(all(num));
    num.resize(unique(all(num)) - num.begin());
    for (int i=0; i<N; ++i) {
        A[i].FI = (lower_bound(all(num), A[i].FI) - num.begin()) + 1;
        A[i].SE = (lower_bound(all(num), A[i].SE) - num.begin()) + 1;
        upd(A[i].FI, pll(A[i].SE, i+1));
        upd(A[i].SE, pll(A[i].FI, i+1));
    }

    for (int i=0; i<N; ++i) {
        pll cur = query(A[i].FI - 1);
        if (cur.FI < A[i].SE) {
            ans[i] = cur.SE;
        } else {
            cur = query(A[i].SE - 1);
            if (cur.FI < A[i].FI) {
                ans[i] = cur.SE;
            } else {
                ans[i] = -1;
            }
        }
    }
}

bool check() {
    for (int i=0; i<N; ++i) {
        if (ans[i] != -1) {
            if (!((A[ans[i] - 1].FI < A[i].FI && A[ans[i] - 1].SE < A[i].SE) || (A[ans[i] - 1].SE < A[i].FI && A[ans[i] - 1].FI < A[i].SE))) return false;
        } else {
            for (int j=0; j<N; ++j) {
                if (!((A[j].FI >= A[i].FI || A[j].SE >= A[i].SE) && (A[j].SE >= A[i].FI || A[j].FI >= A[i].SE))) return false;
            }
        }
    }
    return true;
}

void test() {
    for (N=1; N<=20; ++N) {
        debug(N);
        for (int t=0; t<1000000; ++t) {
            for (int i=0; i<N; ++i) {
                A[i].FI = (rand() % MN) + 1;
                A[i].SE = (rand() % MN) + 1;
            }

            solve(t);
            if (!check()) {
                debug(N);
                debug1(A, N);
                debug1(ans, N);
                assert(false);
            }
        }
    }
}
        
        
int main() {
    setIO();
    
    //test(); return 0;
    ll T = 1;
    cin >> T;
    
    for (int t=1; t<=T; t++) {
        cin >> N;
        for (int i=0; i<N; ++i) {
            cin >> A[i].FI >> A[i].SE;
        }
        solve(t);
        for (int i=0; i<N; ++i) {
            if (i) cout << ' ';
            cout << ans[i];
        }
        cout << '\n';
    }
    
    return 0;
}
/*
1
3
1 2
5 6
3 4
*/
