//hen_hackers.cpp created at 11/11/20 14:38:48

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
//ll A[MN];
//ll G[MN][MN];
//set<ll> adj[MN];

bool flag;
char query(char c) {
    cout << c << endl;
    char resp;
    cin >> resp;
    if (resp == 'C') flag = true;
    return resp;
}
char query(char c1, char c2) {
    cout << c1 << c2 << endl;
    char resp;
    cin >> resp;
    if (resp == 'C') flag = true;
    return resp;
}

bool cmp(char a, char b) {
    if (flag) return true;
    char resp = query(a, b);
    return resp != 'N';
}

void solve(int testcase) {
    string s;
    flag = false;
    for (char c='a'; c<='z'; ++c) {
        if (flag) break;
        char resp = query(c);
        if (resp != 'N') s.push_back(c);
    }
    for (char c='A'; c<='Z'; ++c) {
        if (flag) break;
        char resp = query(c);
        if (resp != 'N') s.push_back(c);
    }
    for (char c='0'; c<='9'; ++c) {
        if (flag) break;
        char resp = query(c);
        if (resp != 'N') s.push_back(c);
    }

    sort(all(s), cmp);
    if (!flag) {
        cout << s << endl;
    }
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}
