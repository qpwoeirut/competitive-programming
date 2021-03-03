//solve.cpp created at 02/25/21 10:54:25

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

#define pb push_back
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

struct Street {
    int start, finish;
    string name;
    int length;

    Street() {
        start = finish = length = 0;
        name = "";
    }
    Street(int _start, int _finish, const string& _name, int _length) {
        start = _start;
        finish = _finish;
        name = _name;
        length = _length;
    }
};

ll d,n,m,v,f;
//d - duration
//n - nr of intersections
//m - nr of streets
//v - nr of cars
//f - bonus points for each car that reaches destination at a time<=d
Street e[MN];
map<string, Street> street;

vector<Street> adj[MN], radj[MN];
vector<string> car[MN];

map<string, int> weight;

vector<pair<string,int>> ans[MN];

inline const bool cmp_weight(const Street& a, const Street& b) {
    return weight[a.name] > weight[b.name];
}

void solve(const string& dataset) {
    assert(dataset.size() == 1 && 'a' <= dataset[0] && dataset[0] <= 'f');
    ifstream fin(dataset + ".txt");
    ofstream fout("ans_" + dataset + ".txt");
    fin.tie(0)->sync_with_stdio(0);
    
    fin >> d >> n >> m >> v >> f;

    street.clear();
    for (int i=0; i<n; i++) {
        adj[i].clear();
        radj[i].clear();
        ans[i].clear();
    }
    weight.clear();

    for (int i = 0; i < m; i++) {
        fin >> e[i].start >> e[i].finish >> e[i].name >> e[i].length;
        street[e[i].name] = e[i];
        adj[e[i].start].pb(e[i]);
        radj[e[i].finish].pb(e[i]);
    }

    for (int i = 0; i < v; i++) {
        int x;
        fin >> x;
        while (x--) {
            string S;
            fin >> S;
            car[i].pb(S);
            ++weight[S];
        }
    }

    debug(d);
    int answer_count = 0;
    for (int i=0; i<n; i++) {
        sort(all(radj[i]), cmp_weight);
        for (const Street& s: radj[i]) {
            if (weight[s.name] > 0) {
                ans[i].emplace_back(s.name, 1);
            }
        }
        if (ans[i].size() > 0) ++answer_count;
    }

    fout << answer_count << '\n';
    for (int i = 0; i < n; i++) {
        if (ans[i].empty()) continue;
        fout << i << '\n';
        fout << ans[i].size() << '\n';
        for (auto& p: ans[i]) fout << p.FI << " " << p.SE << '\n';
    }

    fout.close();
}

int main() {
    string dataset;
    cout << "Enter dataset ID: "; cout.flush();
    cin >> dataset;

    if (dataset == "all") {
        solve("b");
        solve("c");
        solve("d");
        solve("e");
        solve("f");
    } else {
        solve(dataset);
    }

    return 0;
}

