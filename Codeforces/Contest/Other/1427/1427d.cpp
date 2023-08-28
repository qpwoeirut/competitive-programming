//1427d.cpp created at 10/10/20 01:17:55

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
int pos[MN];
vector<vector<int>> ans;
void solve(int testcase) {
    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }

    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            pos[A[j]] = j;
        }

        vector<int> op;
        if ((N-i) & 1) {
            op.PB(pos[i+1]);
            op.PB(N - i - pos[i+1]);
            for (int j=0; j<i; ++j) {
                op.PB(1);
            }
        } else {
            for (int j=0; j<i; ++j) {
                op.push_back(1);
            }
            op.PB(pos[i+1] - i + 1);
            op.PB(N - pos[i+1] - 1);
        }
        vector<int> clean;
        for (int i=0; i<op.size(); ++i) {
            if (op[i] > 0) clean.PB(op[i]);
        }
        if (clean.size() <= 1) continue;
        ans.PB(clean);

        vector<vector<int>> parts;
        int idx = 0;
        for (int j=0; j<clean.size(); ++j) {
            parts.PB(vector<int>());
            for (int k=0; k<clean[j]; ++k) {
                parts.back().PB(A[idx++]);
            }
        }
        reverse(all(parts));
        idx = 0;
        for (int j=0; j<parts.size(); ++j) {
            for (int k=0; k<parts[j].size(); ++k) {
                A[idx++] = parts[j][k];
            }
        }
        debug1(A, N);
    }

    cout << ans.size() << endl;
    for (int i=0; i<ans.size(); ++i) {
        cout << ans[i].size();
        for (int j=0; j<ans[i].size(); ++j) {
            cout << ' ' << ans[i][j];
        }
        cout << endl;
    }

}
        
        
int main() {
    setIO();
    
    ll T = 1;
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}
/*
5
4 2 3 1 5
*/
