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

ll binpow(const ll& x, const ll& p, const ll& mod) {assert(mod>0);
	if (p == 0) return 1;
	if (p == 1) return x % mod;
	if (p & 1) return (binpow((x*x) % mod, p/2, mod) * x) % mod;
	return binpow((x*x) % mod, p/2, mod) % mod;
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
const int MN = 20; //200001;

ll N, M, K, Q;
int A[1 << MN];
bool rev[20];
//int G[MN][MN];
//set<int> adj[MN];

struct Node {
    int lvl;
    int sum;
    int l, r;
    int md;
    bool swapped;
    Node* left;
    Node* right;

    Node(int a, int b, int c) {
        lvl = a;
        l = b;
        r = c;
        md = (l + r) >> 1;
        swapped = false;

        if (lvl == 0) {
            sum = A[l];
        } else {
            left = new Node(lvl - 1, l, md);
            right = new Node(lvl - 1, md + 1, r);
            sum = left->sum + right->sum;
        }
    }

    ll get_sum(int ql, int qr) {
        if (l > qr || r < ql) return 0;
        if (l >= ql && r <= qr) {
            return sum;
        }

        if (rev[lvl] != swapped) {
            swap_children();
            swapped = !swapped;
        }

        assert(lvl > 0);

        cout << "sum " << l << ' ' << r << ' ' << ql << ' ' << qr << ' ' << left->get_sum(ql, min(qr, md)) + right->get_sum(max(ql, md + 1), qr) << endl;
        return left->get_sum(ql, min(qr, md)) + right->get_sum(max(ql, md + 1), qr);
    }

    void replace(int pos, int val) {
        if (lvl == 0) {
            sum = val;
        } else {
            if (rev[lvl] != swapped) {
                swap_children();
                swapped = !swapped;
            }
            if (pos <= md) {
                left->replace(pos, val);
            } else {
                right->replace(pos, val);
            }
            sum = left->sum + right->sum;
        }
    }
    void swap_children() {
        swap(left, right);
        swap(left->l, right->l);
        swap(left->r, right->r);
    }
    void print() {
        if (lvl == 0) {
            cout << sum << ' ';
        } else {
            left->print();
            right->print();
        }
    }
};

void solve(int t) {
    cin >> N >> Q;
    for (int i=0; i<(1 << N); i++) {
        cin >> A[i];
    }
    fill(rev, rev+N+1, false);

    Node* root = new Node(N, 0, (1 << N) - 1);

    for (int i=0; i<Q; i++) {
        int type, x, k, l, r;
        cin >> type;
        if (type == 1) {
            cin >> x >> k;
            root->replace(x-1, k);
        } else if (type == 2) {
            cin >> k;
            for (int j=k; j>=0; j--) {
                rev[j] = !rev[j];
            }
        } else if (type == 3) {
            cin >> k;
            ++k;
            rev[k] = !rev[k];
        } else if (type == 4) {
            cin >> l >> r;
            --l; --r;
            cout << root->get_sum(l, r) << endl;
        } else assert(false);
        root->print();
        cout << endl;
    }
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}
