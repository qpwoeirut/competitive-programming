/*
 * 1363e.cpp
 *
 *  Created on: May 30, 2020
 *      Author: Stanley
 */


#include <iostream>
#include <algorithm>
#include <cassert>
#include <queue>
#include <set>
#include <string>
#include <vector>
#include <map>
#include <deque>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <utility>
#include <bitset>
#include <forward_list>
#include <list>
#include <stack>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

#define PF push_front
#define PB push_back
#define INS insert

#define FI first
#define SE second
#define all(obj) begin(obj), end(obj)
#define rall(obj) (obj).rbegin(), (obj).rend()

#define LB lower_bound
#define UB upper_bound

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<set<ll> > vsi;

typedef unsigned long long ull;
typedef pair<int,bool> pib;
typedef pair<ll,bool> plb;
typedef vector<vector<int> > vvi;
typedef vector<set<pii> > vspi;
typedef vector<vector<pii> > vvpi;
typedef map<int,int> mii;
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

string to_string(const char& c){return string(1, c);}
string to_string(const string& s){return '"'+s+'"';}
string to_string(const char* s){return to_string((string)s);}
string to_string(const bool& b){return (b?"true":"false");}
string to_string(const vector<bool>& v,const string& sep=" ") {
	string s = "[";
	for (int i=0; i<v.size(); i++) {if (i){s += sep;} s += to_string(v[i]);}
	return s + "]";
}
template <size_t N> string to_string(const bitset<N>& v) {
	string s = "[";
	for (size_t i=0; i<N; i++) s += v[i] ? '1' : '0';
	return s + "]";
}
template <class T1,class T2> string to_string(const pair<T1, T2>& p, const string& sep=",");
template <class T> string to_string(const T& v, const string& sep=" ") {
	bool first = true; string s = "{";
	for (const auto &x: v) {
		if (!first) s += sep;
		else first = false;
		s += to_string(x);
	}
	return s + "}";
}
template <class T> string to_string(const T& v, const int& sz, const string& sep=" ") {
	string s = "[";
	for (int i=0; i<sz; i++) {if (i){s += sep;} s += to_string(v[i]);}
	return s + "]";
}
template <class T1,class T2> string to_string(const pair<T1,T2>& p, const string& sep) {return "(" + to_string(p.first) + sep + to_string(p.second) + ")";}

#define debug(obj) cout << #obj << ": " << to_string(obj) << endl;
#define debug1(obj, sz) cout << #obj << ": " << to_string(obj, sz) << endl;
#define debug2(obj, sz1, sz2) cout << "-----" << #obj << "-----\n"; for (int i=0; i<sz1; i++) cout << to_string(obj[i], sz2) << " "; cout << endl;
#define debug3(obj, sz1, sz2, sz3) cout << "-----" << #obj << "-----\n"; for (int i=0; i<sz1; i++) {for (int j=0; j<sz2; j++) cout << to_string(obj[i][j], sz3) << " "; cout << endl;} cout << endl;

ll binpow(const ll& x, const ll& p, const ll& mod) {assert(mod>0);
	if (p == 0) return 1;
	if (p == 1) return x % mod;
	if (p & 1) return (binpow((x*x) % mod, p/2, mod) * x) % mod;
	return binpow((x*x) % mod, p/2, mod) % mod;
}

template <class T> void chmn(T& a, const T& b) {if (a>b) a=b;}
template <class T> void chmx(T& a, const T& b) {if (a<b) a=b;}

void setIO() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
}

int chr[8] = {-1, 0, 1, 0, -1, -1, 1, 1};
int chc[8] = {0, 1, 0, -1, -1, 1, -1, 1};

const ll MOD = 1e9+7; // 998244353;
const int INIT = 1001001001;
const int MN = 200001;

ll A[MN], B[MN], C[MN];
pll ctb[MN], ctc[MN];
ll diff[MN];

void add(pll& a, const pll& b) {
	a.FI += b.FI;
	a.SE += b.SE;
}
bool eq(const pll& a, const pll& b) {
	return a.FI == b.FI && a.SE == b.SE;
}
bool sum_eq(const pll& a, const pll& b) {
	return a.FI + a.SE == b.FI + b.SE;
}

vsi adj;
void dfs(ll cur, ll par) {
	diff[cur] = (B[cur] == C[cur] ? 0 : 1);
	for (set<ll>::iterator it=adj[cur].begin(); it!=adj[cur].end(); it++) {
		if (*it == par) continue;
		dfs(*it, cur);
		add(ctb[cur], ctb[*it]);
		add(ctc[cur], ctc[*it]);
		diff[cur] += diff[*it];
	}
}


pll rec(ll cur, ll par, ll a) {
	pll ret(0,0);
	if (adj[cur].size() == 1 && par != -1) {
//		cout << cur << " " << par << " " << a << " " << to_string(ret) << endl;
		return ret;
	}

	for (set<ll>::iterator it=adj[cur].begin(); it!=adj[cur].end(); it++) {
		if (*it == par) continue;
		pll done = rec(*it, cur, min(a, A[*it]));
		add(ret, done);
	}

	if (eq(ctb[cur], ctc[cur])) {
		ret.FI += a * (diff[cur] - ret.SE);
		ret.SE = diff[cur];
	}


//	cout << cur << " " << par << " " << a << " " << to_string(ret) << endl;
	return ret;
}


void solve() {
	int N;
	cin >> N;

	for (int i=0; i<N; i++) {
		cin >> A[i] >> B[i] >> C[i];
		if (B[i] == 0) {
			ctb[i] = pii(1, 0);
		}
		else {
			ctb[i] = pii(0, 1);
		}

		if (C[i] == 0) {
			ctc[i] = pii(1, 0);
		}
		else {
			ctc[i] = pii(0, 1);
		}
	}
	
	adj = vsi(N, set<ll>());
	ll u, v;
	for (int i=0; i<N-1; i++) {
		cin >> u >> v;
		u--; v--;
		adj[u].insert(v);
		adj[v].insert(u);
	}

	dfs(0, -1);

//	debug1(ctb, N);
//	debug1(ctc, N);
//	debug1(diff, N);

	pll ans = rec(0, -1, A[0]);
	if (ans.SE != diff[0]) {
		cout << -1 << endl;
	}
	else {
		cout << ans.FI << endl;
	}
}

int main() {
	setIO();

	ll T = 1;
//	cin >> T;

	while (T--) solve();

	return 0;
}

/*
5
100 0 0
10 1 0
1 0 1
10 1 0
1 0 1
1 2
2 3
1 4
4 5

A=40

5
100 0 0
10 1 0
1 0 1
10 1 1
1 0 0
1 2
2 3
1 4
4 5

A=20

7
33 0 1
1000 1 1
1511 0 0
12 1 1
1 1 0
10 1 0
1 0 1
1 2
2 3
3 4
4 6
6 7
3 5

A = 86

2
10 1 0
1 0 1
1 2

A = 20


5
1 0 1
10 1 1
1 1 0
2 0 1
2 1 0
1 2
2 3
3 4
4 5

 */
