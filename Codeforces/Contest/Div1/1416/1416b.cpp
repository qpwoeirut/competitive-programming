//1416b.cpp created at 09/27/20 00:37:57

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
ll A[MN];
//ll G[MN][MN];
//set<ll> adj[MN];

ll ai[MN], aj[MN], ax[MN], ans;

void op(ll i, ll j, ll x) {
    assert(x >= 0);
    ai[ans] = i;
    aj[ans] = j;
    ax[ans] = x;
    A[i-1] -= i * x;
    assert(A[i-1] >= 0);
    A[j-1] += i * x;
    ++ans;

    debug1(A, N);
}

void solve(int testcase) {
    cin >> N;
    ll sum = 0;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
        sum += A[i];
    }

    if (sum % N != 0) {
        cout << -1 << endl;
        return;
    }
    ans = 0;
    ll target = sum / N;
    for (ll i=1; i<N; ++i) {
        debug(i+1, A[i]);
        if (A[i] % (i+1) > 0) {
            op(1, i+1, (i+1) - (A[i] % (i+1)));
        }
        op(i+1, 1, A[i] / (i+1));
    }

    for (ll i=1; i<N; ++i) {
        if (A[i] != target) {
            op(1, i+1, target - A[i]);
        }
        assert(A[i] == target);
    }

    cout << ans << endl;
    for (int i=0; i<ans; ++i) {
        cout << ai[i] << ' ' << aj[i] << ' ' << ax[i] << '\n';
    }
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    cin >> T;
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}
/*
4

5
1 1 1 3 4

8
1 1 1 2 2 2 3 4

6
1 12 1 1 1 2

9
1 3 5 7 1 1 1 1 16
*/
