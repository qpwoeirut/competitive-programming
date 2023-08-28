//1416a.cpp created at 09/27/20 00:37:56

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
ll A[MN], gap[MN];
vector<ll> pos[MN];
//ll G[MN][MN];
//set<ll> adj[MN];
ll ans[MN];
bool in[MN];
void solve(int testcase) {
    cin >> N;

    for (int i=0; i<=N; ++i) {
        pos[i] = vector<ll>();
        pos[i].push_back(-1);
        ans[i] = INIT;
    }

    for (int i=0; i<N; ++i) {
        cin >> A[i];
        pos[A[i]].push_back(i);
        in[A[i]] = true;
    }

    for (ll i=1; i<=N; ++i) {
        pos[i].push_back(N);
        if (!in[i]) continue;
        gap[i] = 0;
        for (int j=1; j<pos[i].size(); ++j) {
            chmx(gap[i], pos[i][j] - pos[i][j-1]);
        }
        chmn(ans[gap[i]], i);
    }
    debug1(gap, N+1);   

    ll cur = INIT;
    for (int k=1; k<=N; ++k) {
        chmn(cur, ans[k]);
        cout << (cur == INIT ? -1 : cur);
        if (k < N) cout << ' ';
    }
    cout << endl;

}
        
        
int main() {
    setIO();
    
    ll T = 1;
    cin >> T;
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}
