//1092d.cpp created at 09/22/20 13:22:01

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
int L[MN], R[MN];
bool in[MN];
//ll G[MN][MN];
//set<ll> adj[MN];

void solve(int testcase) {
    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
        A[i] &= 1;
        L[i] = i-1;
        R[i] = i+1;
        in[i] = true;
    }
    L[0] = N;
    R[N-1] = N;
    A[N] = -1;

    L[N] = R[N] = N;
    for (int i=0; i<N;) {
        int j = R[i];
        //cerr << i << ' ' << j << endl;
        if (j == N) break;
        if (A[i] == A[j]) {
            in[i] = in[j] = false;
            //cerr << "match\n";
            L[R[j]] = L[i];
            R[L[i]] = R[j];

            L[j] = L[i];
            R[i] = R[j];

            L[N] = R[N] = N;
            if (L[j] == N) {
                i = R[i];
            } else {
                i = L[j];
            }
        } else {
            i = R[i];
        }
        debug1(L, N);debug1(R, N);debug1(in, N);
    }

    int rem = 0;
    for (int i=0; i<N; ++i) {
        rem += in[i];
    }
    debug(rem);

    if (rem > 1) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
    }
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}
/*
6
0 1 0 0 1 0

4
1 1 1 1
*/

