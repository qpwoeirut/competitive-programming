//1425f.cpp created at 09/26/20 22:11:47

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

//int secret[6] = {1,4,4,6,7,8};
//int secret[7] = {1,5,3,5,6,3,7};
int query(int L, int R){
    assert(L < R);
    cout << "? " << L << " " << R << endl;
    int resp = 0;
    //for (int i=L-1; i<R; ++i) { resp += secret[i]; } return resp;
    cin >>resp;
    return resp;
}

void answer() {
    cout << '!';
    for (int i=0; i<N; ++i) {
        cout << ' ' << A[i];
    }
    cout << endl;
}

void solve(int testcase) {
    cin >> N;

    if (N == 3) {
        int x = query(1, 2);
        int y = query(2, 3);
        int z = query(1, 3);
        A[0] = z - y;
        A[2] = z - x;
        A[1] = z - (A[0] + A[2]);
        answer();
        return;
    }
        
    int mid = N/2;
    A[mid-1] = query(1, mid);
    int small, large = A[mid-1];
    for (int i=0; i+1<mid; ++i) {
        small = query(i+2, i+mid);
        A[i] = large - small;
        large = query(i+2, i+1+mid);
        A[i + mid] = large - small;
        //debug1(A, N);
    }
    for (int i=0; i+1<mid; ++i) A[mid-1] -= A[i];
    if (N & 1) {
        A[N-2] = query(1, N-1);
        for (int i=0; i+2<N; ++i) A[N-2] -= A[i];
    }

    A[N-1] = query(1, N);
    for (int i=0; i+1<N; ++i) A[N-1] -= A[i];

    answer();
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}
