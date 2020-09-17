/*
 * 1344b.cpp
 *
 *  Created on: May 2, 2020
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

int chr[4] = {-1, 0, 1, 0};
int chc[4] = {0, 1, 0, -1};

const ll MOD = 1e9+7; // 998244353;
const int INIT = 1001001001;
const int MN = 1001;

void setIO() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
}

int N, M;
pii row[MN], col[MN];
string grid[MN];

bool full_row(int r, int c1, int c2) {
	for (; c1<=c2; c1++) {
		if (grid[r][c1] != '#') return false;
	}
	return true;
}
bool full_col(int c, int r1, int r2) {
	for (; r1<=r2; r1++) {
		if (grid[r1][c] != '#') return false;
	}
	return true;
}

void dfs(int r, int c) {
	if (r < 0 || r >= N || c < 0 || c >= M || grid[r][c] != '#') return;
	grid[r][c] = '*';
	dfs(r + 1, c);
	dfs(r, c + 1);
	dfs(r - 1, c);
	dfs(r, c - 1);
}

int islands() {
	int ans = 0;
	for (int i=0; i<N; i++) {
		for (int j=0; j<M; j++) {
			if (grid[i][j] == '#') {
				ans++;
				dfs(i, j);
			}
		}
	}
	return ans;
}

void solve() {
	cin >> N >> M;
	
	fill(row, row+N, pii(MN, -1));
	fill(col, col+M, pii(MN, -1));
	for (int i=0; i<N; i++) {
		cin >> grid[i];
		for (int j=0; j<M; j++) {
			if (grid[i][j] == '#') {
				chmn(row[i].first, j);
				chmx(row[i].second, j);
				chmn(col[j].first, i);
				chmx(col[j].second, i);
			}
		}
	}

	bool ok = true;
	bool erow = false, ecol = false;
	for (int i=0; i<N; i++) {
		if (row[i].first != MN) {
			ok &= full_row(i, row[i].first, row[i].second);
		}
		else {
			erow = true;
		}
	}
	for (int i=0; i<M; i++) {
		if (col[i].first != MN) {
			ok &= full_col(i, col[i].first, col[i].second);
		}
		else {
			ecol = true;
		}
	}

	if ((erow && !ecol) || (!erow && ecol)) {
		ok = false;
	}

	if (!ok) {
		cout << -1 << endl;
	}
	else {
		cout << islands() << endl;
	}
}

int main() {
	setIO();

	ll T = 1;
//	cin >> T;

	while (T--) solve();

	return 0;
}
