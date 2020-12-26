//day23.cpp created at 12/22/20 21:16:14

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
//const int MN = 9;
const int MN = 1000000;

ll N, M, K;
ll A[MN];
//ll G[MN][MN];
//set<ll> adj[MN];

list<int>::iterator iter[MN + 1];

//const int MOVES = 100;
const int MOVES = 10000000;

int a[3];
void solve(int testcase) {
    //list<int> nums = {3,8,9,1,2,5,4,6,7};
    list<int> nums = {6,1,4,7,5,2,8,3,9};
    for (int i=10; i<=MN; ++i) {
        nums.push_back(i);
    }
    for (auto it=nums.begin(); it!=nums.end(); ++it) {
        iter[*it] = it;
    }

    for (int i=0; i<MOVES; ++i) {
        if ((i & 65535) == 0) {
            cout << i << endl;
            //for (const int x: nums) {
            //    cout << x << ' ';
            //} cout << endl;
            //cout << a[0] << ' ' << a[1] << ' ' << a[2] << endl;
        }
        int cur = nums.front();
        nums.pop_front();
        for (int j=0; j<3; ++j) {
            a[j] = nums.front();
            nums.pop_front();
        }

        int dest = cur - 1;
        if (dest < 1) dest += MN;
        while (dest == a[0] || dest == a[1] || dest == a[2]) {
            if (--dest < 1) dest += MN;
        }

        auto it = iter[dest];
        auto it2 = it;
        ++it2;
        nums.insert(it2, a, a+3);
        for (int j=0; j<4; ++j) {
            iter[*it] = it;
            ++it;
        }
        nums.push_back(cur);
        it = nums.end(); --it;
        iter[cur] = it;
    }
    for (const int x: nums) {
        cout << x << ' ';
    } cout << endl;

    auto it = iter[1];
    ++it;
    ll x = *it;
    ++it;
    ll y = *it;
    cout << x * y << endl;
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}
