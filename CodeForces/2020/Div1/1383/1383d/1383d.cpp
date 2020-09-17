/*
 * 1383d.cpp
 *
 *  Created on: Jul 23, 2020
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

int chr[8] = {-1, 0, 1, 0, -1, -1, 1, 1};
int chc[8] = {0, 1, 0, -1, -1, 1, -1, 1};

const ll MOD = 1e9+7; //998244353;
const int INIT = 1001001001;
const int MN = 300; //200001;

struct Cell {
	int mx;
	int r, c;

	Cell(int _a, int _b, int _c) {
		mx = _a;
		r = _b;
		c = _c;
	}
};

string to_string(const Cell& a) {
	return to_string(a.r) + "," + to_string(a.c) + "=" + to_string(a.mx);
}

inline const bool cmp(const Cell& a, const Cell& b) {
	if (a.r + a.c == b.r + b.c) {
		return a.r > b.r;
	}
	return a.r + a.c > b.r + b.c;
}

ll N, M, K;
//int A[MN];
int G[MN][MN];
//set<int> adj[MN];
int mxr[MN];
int mxc[MN];
int R[MN], C[MN];
int ans[MN][MN];
void solve() {
	cin >> N >> M;

	set<int> nums;
	for (int i=0; i<N; i++) {
		for (int j=0; j<M; j++) {
			cin >> G[i][j];
			chmx(R[i], G[i][j]);
			chmx(C[j], G[i][j]);
		}
	}
	
	for (int i=1; i<=N*M; i++){
		nums.INS(i);
	}

	for (int i=0; i<N; i++) {
		nums.erase(R[i]);
	}
	for (int i=0; i<M; i++) {
		nums.erase(C[i]);
	}

	sort(R, R+N);
	sort(C, C+M);
//	debug1(R, N);
//	debug1(C, M);

	vector<int> same;
	vector<int> dr, dc;
	int r = 0, c = 0;
	R[N] = INIT;
	C[M] = INIT;
	while (r < N || c < M) {
		if (R[r] < C[c]) {
			dr.PB(R[r++]);
		}
		else if (R[r] > C[c]) {
			dc.PB(C[c++]);
		}
		else {
			same.PB(R[r]);
			++r;++c;
		}
	}
	reverse(all(same));
	reverse(all(dr));
	reverse(all(dc));
	debug(same);
	debug(dr);
	debug(dc);

	int rr=1, cc=1;
	for (; rr<=dr.size(); rr++) {
		ans[rr][0] = dr[rr-1];
		mxr[rr] = dr[rr-1];
	}
	for (; cc<=dc.size(); cc++) {
		ans[0][cc] = dc[cc-1];
		mxc[cc] = dc[cc-1];
	}
	debug2(ans, N, M);
	ans[0][0] = same[0];
	mxr[0] = same[0];
	mxc[0] = same[0];
	for (int i=1; i<same.size(); i++, rr++, cc++) {
		ans[rr][cc] = same[i];
		mxr[rr] = same[i];
		mxc[cc] = same[i];
	}
	debug2(ans, N, M);

	vector<Cell> cells;
	for (int i=0; i<N; i++) {
		for (int j=0; j<M; j++) {
			if (ans[i][j] == 0) {
				cells.PB(Cell(min(mxr[i], mxc[j]), i, j));
			}
		}
	}
	sort(all(cells), cmp);
	debug(cells);
	debug(nums);
	set<int>::iterator it=nums.begin();
	for (int i=0; i<cells.size(); i++, it++) {
		int row = cells[i].r;
		int col = cells[i].c;

		ans[row][col] = *it;
		assert(it != nums.end());
	}

	assert(it == nums.end());

	for (int i=0; i<N; i++) {
		for (int j=0; j<M; j++) {
			if (j) cout << ' ';
			cout << ans[i][j];
		}
		cout << endl;
	}
}

int main() {
	setIO();

	ll T = 1;
//	cin >> T;

	while (T-- > 0) solve();

	return 0;
}
