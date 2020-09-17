/*
 * 520d.cpp
 *
 *  Created on: Jul 27, 2020
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
typedef vector<set<int> > vsi;

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
void setIO(const string& filename) {
	setIO();
	freopen((filename + ".in").c_str(), "r", stdin);
	freopen((filename + ".out").c_str(), "w", stdout);
}

int chr[8] = {-1, 0, 1, 0, -1, -1, 1, 1};
int chc[8] = {0, 1, 0, -1, -1, 1, -1, 1};

const ll MOD = 1e9+9; //998244353;
const int INIT = 1001001001;
const int MN = 100001;

struct Cube {
	int x, y;
	int val;

	Cube(int a, int b, int c) {
		x = a;
		y = b;
		val = c;
	}
};

struct cmp_val {
	inline const bool operator()(const Cube& a, const Cube& b) const {
		return a.val < b.val;
	}
};

inline const bool cmp_y(const Cube& a, const Cube& b) {
	if (a.y == b.y) {
		return a.x < b.x;
	}
	return a.y < b.y;
}

ll N, M, K;
mii cubes[MN];
//int G[MN][MN];
set<int> adj[MN], radj[MN];

void solve() {
	cin >> N;
	
	for (int i=0; i<N; i++) {
		int x, y;
		cin >> x >> y;
		cubes[y][x] = i;
	}

	for (int y=0; y<N; y++) {
		for (mii::iterator it=cubes[y].begin(); it!=cubes[y].end(); it++) {
			mii::iterator above = cubes[y+1].lower_bound(it->FI-1);
			while (above != cubes[y+1].end() && above->FI <= it->FI + 1) {
				adj[it->SE].INS(above->SE);
				radj[above->SE].INS(it->SE);
				++above;
			}
		}
	}

	set<int> cur;
	for (int i=0; i<N; i++) {
		bool ok = true;
		for (set<int>::iterator it=adj[i].begin(); it!=adj[i].end(); it++) {
			if (radj[*it].size() == 1) {
				ok = false;
				break;
			}
		}
		if (ok) {
			cur.INS(i);
		}
	}

	vector<int> ans;
	for (int i=0; i<N; i++) {
		assert(cur.size() > 0);
//		debug(cur);
		if (i & 1) {
			ans.PB(*cur.begin());
			cur.erase(cur.begin());
		}
		else {
			ans.PB(*cur.rbegin());
			set<int>::iterator it=cur.end(); --it;
			cur.erase(it);
		}
//		debug(ans);
//		debug1(adj, N);
//		debug1(radj, N);

		int val = ans.back();
		for (set<int>::iterator it=adj[val].begin(); it!=adj[val].end(); it=adj[val].erase(it)) {
			radj[*it].erase(val);
			if (radj[*it].size() == 1) {
				cur.erase(*radj[*it].begin());
			}
		}
		for (set<int>::iterator it=radj[val].begin(); it!=radj[val].end(); it=radj[val].erase(it)) {
//			debug(*it);
			bool ok = true;
			adj[*it].erase(val);
			for (set<int>::iterator ait=adj[*it].begin(); ait!=adj[*it].end(); ait++) {
				if (radj[*ait].size() == 1) {
					ok = false;
					break;
				}
			}
			if (ok) {
				cur.INS(*it);
			}
		}
	}


	assert(ans.size() == N);

	ll x = 0;
	for (ll i=0; i<ans.size(); i++) {
		x = (x * N) % MOD;
		x = (x + ans[i]) % MOD;
	}

	cout << x << endl;
}

int main() {
	setIO();

	ll T = 1;
//	cin >> T;

	while (T-- > 0) solve();

	return 0;
}
