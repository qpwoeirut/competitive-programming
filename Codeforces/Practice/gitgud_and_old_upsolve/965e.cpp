//965e.cpp created at 01/03/21 20:02:54

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
const int MN = 1001001;

struct Node {
    char val;
    int ct;
    int depth;
    map<int,int,greater<int>> len;
    Node* child[26];

    Node(const char _val, const int _ct, const int _depth) {
        val = _val;
        ct = _ct;
        depth = _depth;
        fill(child, child+26, nullptr);
    }
};

ll N, M, K;
string A[MN];
//ll G[MN][MN];
//set<ll> adj[MN];

void recurse(Node* node) {
    for (int i=0; i<26; ++i) {
        if (node->child[i]) {
            recurse(node->child[i]);

            if (node->len.size() < node->child[i]->len.size()) {
                swap(node->len, node->child[i]->len);
            }
            for (const pii& p: node->child[i]->len) {
                node->len[p.FI] += p.SE;
            }
        }
    }
    if (node->depth > 0) {
        if (node->ct > 0) {
            node->len[node->depth] += node->ct;
        } else {
            if (--node->len.begin()->SE == 0) {
                node->len.erase(node->len.begin());
            }
            ++node->len[node->depth];
        }
    }
    debug(node->val, node->ct, node->depth, node->len);
}

void solve(int testcase) {
    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }
    
    Node* root = new Node('$', 0, 0);
    for (int i=0; i<N; ++i) {
        Node* cur = root;
        for (int j=0; j<A[i].size(); ++j) {
            if (cur->child[A[i][j] - 'a'] == nullptr) {
                cur->child[A[i][j] - 'a'] = new Node(A[i][j], 0, j+1);
            }
            cur = cur->child[A[i][j] - 'a'];
        }
        ++cur->ct;
    }

    recurse(root);

    int ans = 0;
    for (const pii& x: root->len) ans += x.FI * x.SE;
    cout << ans << endl;
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}
