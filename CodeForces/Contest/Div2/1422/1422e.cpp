//1422e.cpp created at 10/04/20 09:04:37

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

typedef pair<string,string> pss;

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

const int ML = 15;

bool cmp(const pss& a, const pss& b) {
    for (int i=0; i<a.FI.size() && i<b.FI.size(); ++i) {
        if (a.FI[i] != b.FI[i]) {
            return a.FI[i] < b.FI[i];
        }
    }
    return (a.SE.size() > 0 && b.SE.size() > 0);
}

ll N, M, K;
//ll A[MN];
//ll G[MN][MN];
//set<ll> adj[MN];
ll len[MN];
pss ans[MN];
void solve(int testcase) {
    string s;
    cin >> s;

    N = s.size();

    if (N == 1) {
        cout << "1 " << s << endl;
        return;
    }

    string ending = s.substr(N-2, 2);

    ans[0] = pss("", "");
    ans[1] = pss(string(1, (char)s.back()), "");
    len[1] = 1;
    for (int i=2; i<=N; ++i) {
        int idx = N-i;
        ans[i] = pss(s[idx] + ans[i-1].FI, ans[i-1].SE);
        debug(ans[i]);
        len[i] = len[i-1] + 1;
        if (s[idx] == s[idx+1]) {
            if (!cmp(ans[i], ans[i-2])) {
                ans[i] = ans[i-2];
                len[i] = len[i-2];
            }
        }
        if (ans[i].FI.size() > ML) {
            if (ans[i].SE.empty()) {
                ans[i].SE = ans[i].FI.substr(ans[i].FI.size() - 2, 2);
            }
            while (ans[i].FI.size() > ML) {
                ans[i].FI.pop_back();
            }
        }
    }

    for (int i=N; i>0; --i) {
        cout << len[i] << ' ';
        if (len[i] > 10) {
            string last = ans[i].SE;
            if (last.empty()) {
                last = ans[i].FI.substr(ans[i].FI.size() - 2, 2);
            }
            cout << ans[i].FI.substr(0, 5) << "..." << last << '\n';
        } else {
            cout << ans[i].FI << '\n';
        }
    }
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}
