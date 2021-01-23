//1474d.cpp created at 01/19/21 00:04:40

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
typedef map<int,int> mii;
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

template <class T> bool chmn(T& a, const T& b) {return (greater<T>()(a, b) ? (a=b, true) : false);}
template <class T> bool chmx(T& a, const T& b) {return (less<T>()(a, b) ? (a=b, true) : false);}

void setIO(const string& filename = "") {
    if (filename.size() > 0) {
        freopen((filename + ".in").c_str(), "r", stdin);
        freopen((filename + ".out").c_str(), "w", stdout);
    }
	cin.tie(0)->sync_with_stdio(0);
}

int chr[8] = {-1, 0, 1, 0, -1, -1, 1, 1};
int chc[8] = {0, 1, 0, -1, -1, 1, -1, 1};

const ll MOD = 1e9+7; //998244353 //1e9+9 //1e9+21 // 1e9+33;
const int INIT = 1001001001;
const int MN = 1001001;
const ll INF = 2e18 + 1;

ll N, M, K, Q;
ll A[MN], B[MN], C[MN], D[MN];
//ll G[MN][MN];
//set<ll> adj[MN];

bool check(bool r) {
    copy(C, C+N, A);
    if (r) reverse(A, A+N);
    for (int i=0; i+1<N; ++i) {
        const ll x = min(A[i], A[i+1]);
        A[i] -= x;
        A[i+1] -= x;
        
        if (A[i] > 0) return false;
    }

    return A[N-1] == 0;
}

bool check() {
    copy(A, A+N, C);
    return check(false) || check(true);
}

bool check2() {
    copy(D, D+4, C);
    debug1(D, 4);
    bool ok = true;
    for (int i=0; i+1<4; ++i) {
        const ll x = min(C[i], C[i+1]);
        C[i] -= x;
        C[i+1] -= x;
        if (C[i] > 0) {
            ok = false;
            break;
        }
    }
    ok &= C[3] == 0;
    if (ok) return true;
    ok = true;
    copy(D, D+4, C);
    reverse(C, C+4);
    for (int i=0; i+1<4; ++i) {
        const ll x = min(C[i], C[i+1]);
        C[i] -= x;
        C[i+1] -= x;
        if (C[i] > 0) {
            ok =  false;
            break;
        }
    }
    ok &= C[3] == 0;
    return ok;
}

ll pref[MN], suff[MN];
bool solve(int testcase) {
    if (N == 2) return B[0] == B[1];
    copy(B, B+N, A);

    fill(pref, pref+N, -1);
    for (int i=0; i+1<N; ++i) {
        pref[i] = A[i];
        const ll x = min(A[i], A[i+1]);
        A[i] -= x;
        A[i+1] -= x;
        if (A[i] > 0) {
            break;
        }
    }
    copy(B, B+N, A); reverse(A, A+N);
    fill(suff, suff+N, -1);
    for (int i=0; i+1<N; ++i) {
        suff[i] = A[i];
        const ll x = min(A[i], A[i+1]);
        A[i] -= x;
        A[i+1] -= x;
        if (A[i] > 0) {
            break;
        }
    }
    reverse(suff, suff+N);
    debug1(pref, N);
    debug1(suff, N);

    for (int i=0; i+1<N; ++i) {
        D[0] = i > 0 ? pref[i-1] : 0;
        D[1] = A[i];
        D[2] = A[i+1];
        D[3] = i+2 < N ? suff[i+2] : 0;

        if (D[0] == -1 || D[3] == -1) continue;
        if (check2()) return true;
        swap(D[1], D[2]);
        if (check2()) return true;
    }
    return false;
}
        
bool brute() {
    copy(B, B+N, A);
    if (check()) return true;
    for (int i=0; i+1<N; ++i) {
        copy(B, B+N, A);
        swap(A[i], A[i+1]);
        if (check()) return true;
    }
    copy(B, B+N, A);
    reverse(A, A+N);
    if (check()) return true;
    for (int i=0; i+1<N; ++i) {
        copy(B, B+N, A);
        reverse(A, A+N);
        swap(A[i], A[i+1]);
        if (check()) return true;
    }
    return false;
}

void test() {
    for (N=2; N<=10000; ++N) {
        if ((N & 63) == 0) {
            debug(N);
        }
        for (int t=0; t<10000; ++t) {
            for (int i=0; i<N; ++i) {
                B[i] = ((rand()) % 10) + 1;
            }
            bool a1 = brute(), a2 = solve(0);
            if (a1 != a2) {
                cout << N << endl;
                for (int i=0; i<N; ++i) {
                    if (i) cout << ' ';
                    cout << B[i];
                }
                cout << endl;
                cout << a1 << ' ' << a2 << endl;
            }
            assert(a1 == a2);
        }
    }
}
        
int main() {
    setIO();

    test(); return 0;
    
    ll T = 1;
    cin >> T;
    
    for (int t=1; t<=T; ++t) {
        cin >> N;
        for (int i=0; i<N; ++i) {
            cin >> B[i];
        }
        cout << (solve(t) ? "YES\n" : "NO\n");
    }
    
    return 0;
}
/*
1
5
1 3 2 5 1

1
9
1 1 2 4 8 4 2 1 1

1
4
5 4 6 3
*/
