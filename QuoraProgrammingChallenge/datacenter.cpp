//datacenter.cpp created at 02/06/21 17:20:52

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
pll A[MN];
//ll G[MN][MN];
//set<ll> adj[MN];

struct Point {
    ll x, y;
    int idx;
};

string to_string(const Point& p) {
    return '(' + to_string(p.idx) + ' ' + to_string(p.x) + ' ' + to_string(p.y) + ')';
}

inline const bool cmp_x(const Point& a, const Point& b) {
    return a.x < b.x;
}
inline const bool cmp_y(const Point& a, const Point& b) {
    return a.y < b.y;
}

Point B[MN];
ll x_dist[MN], y_dist[MN];
int solve(int testcase) {
    fill(x_dist, x_dist+N, 0);
    fill(y_dist, y_dist+N, 0);
    for (int i=0; i<N; ++i) {
        const ll yy = A[i].FI - A[i].SE;
        B[i].x = A[i].FI * 2 - yy;
        B[i].y = yy;
        B[i].idx = i;
    }

    for (int j=0; j<2; ++j) {
        sort(B, B+N, cmp_x);
        if (j) reverse(B, B+N);
        ll cur = 0;
        ll prev = B[0].x;
        for (int i=0; i<N; ++i) {
            cur += abs(B[i].x - prev) * i;
            x_dist[B[i].idx] += cur;
            prev = B[i].x;
        }

        sort(B, B+N, cmp_y);
        if (j) reverse(B, B+N);
        cur = 0;
        prev = B[0].y;
        for (int i=0; i<N; ++i) {
            cur += abs(B[i].y - prev) * i;
            y_dist[B[i].idx] += cur;
            prev = B[i].y;
        }
    }

    pll best(INF, -1);
    for (int i=0; i<N; ++i) {
        chmn(best, pll(x_dist[i] + y_dist[i], i+1));
    }
    //debug1(B, N); debug1(x_dist, N); debug1(y_dist, N);
    return best.SE;
}

#define x first
#define y second
int brute() {
    pll best(INF, -1);
    for (int i=0; i<N; ++i) {
        ll cur = 0;
        for (int j=0; j<N; ++j) {
            cur += max(abs(A[i].x - A[j].x), abs(A[i].y - A[j].y));
        }
        chmn(best, pll(cur, i+1));
    }
    return best.SE;
}

void test() {
    for (N=1; N<=100; ++N) {
        cout << N << endl;
        for (int t=0; t<1e5; ++t) {
            for (int i=0; i<N; ++i) {
                A[i].x = rand() % 1000;
                A[i].y = rand() % 1000;
            }
            int bans = brute();
            int sans = solve(t);
            if (sans != bans) {
                cout << sans << ' ' << bans << endl;
                cout << N << endl;
                for (int i=0; i<N; ++i) {
                    cout << A[i].x << ' ' << A[i].y << endl;
                }
            }
            assert(sans == bans);
        }
    }
}
        
int main() {
    //test(); return 0;
    setIO();
    
    ll T = 1;
    
    for (int t=1; t<=T; ++t) {
        cin >> N;
        for (int i=0; i<N; ++i) {
            cin >> A[i].x >> A[i].y;
        }
        cout << solve(t) << '\n';
    }
    
    return 0;
}
/*
3
1 4
3 1
5 3

3
6 3
4 4
2 5
*/
