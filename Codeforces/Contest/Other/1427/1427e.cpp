//1427e.cpp created at 10/10/20 01:17:57

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

bool is_p2(ll n) {
    if (n == 0) return false;
    while (n) {
        if (n > 1 && (n & 1)) return false;
        n >>= 1;
    }
    return true;
}

struct Op {
    ll a, b;
    bool plus;

    Op(ll _a, ll _b, bool _plus) {
        a = _a;
        b = _b;
        plus = _plus;
    }
};

void solve(int testcase) {
    cin >> N;
    //N = testcase + testcase + 1;

    vector<Op> ans;

    set<ll> nums[2];
    nums[1].INS(N);
    ll p2 = -1;
    bool idx = 0;
    while (p2 == -1) {
        nums[idx].INS(all(nums[!idx]));
        debug1(nums, 2);
        for (auto it=nums[idx].begin(); it!=nums[idx].end(); ++it) {
            for (auto jt=it; jt!=nums[idx].end(); ++jt) {
                if (*it != *jt) {
                    if (is_p2(*it ^ *jt)) {
                        p2 = *it ^ *jt;
                        ans.PB(Op(*it, *jt, false));
                        break;
                    }
                    bool added = nums[!idx].INS(*it ^ *jt).second;
                    if (added) {
                        ans.PB(Op(*it, *jt, false));
                    }
                }
                bool added = nums[!idx].INS(*it + *jt).second;
                if (added) {
                    ans.PB(Op(*it, *jt, true));
                }
            }
            if (p2 != -1) break;
        }
        idx = !idx;
    }
    debug(N, ans.size());
    assert(ans.size() <= 100000);
    //cout << N << ' ' << ans.size() << '\n';
    //return;
    cout << ans.size() << endl;
    for (int i=0; i<ans.size(); ++i) {
        cout << ans[i].a << (ans[i].plus ? " + " : " ^ ") << ans[i].b << endl;
    }
}
        
        
int main() {
    setIO();
    
    //ll T = 1000000;
    ll T = 1;
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}
/*
24579
*/
