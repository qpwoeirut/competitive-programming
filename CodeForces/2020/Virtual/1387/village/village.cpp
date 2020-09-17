/*
 * village.cpp
 *
 *  Created on: Jul 29, 2020
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

const ll MOD = 1e9+7; //998244353;
const int INIT = 1001001001;
const int MN = 100001;

ll N, M, K;
//int A[MN];
//int G[MN][MN];
set<int> adj[MN];
int ans[MN];
ll dist = 0;

int other[MN];
void solve1() {
	cin >> N;
	
	dist = 0;

	for (int i=0; i<N-1; i++) {
		int u, v;
		cin >> u >> v;

		--u;--v;

		adj[u].INS(v);
		adj[v].INS(u);
	}
	if (N == 2) {
		cout << 2 << endl;
		cout << 2 << ' ' << 1 << endl;
		return;
	}

	fill(other, other+N, 0);
	priority_queue<pii, vector<pii>, cmpf<int,int> > pq(true);
	for (int i=0; i<N; i++) {
		if (adj[i].size() == 1) continue;
		for (set<int>::iterator it=adj[i].begin(); it!=adj[i].end(); it++) {
			if (adj[*it].size() > 1) ++other[i];
		}
		pq.push(pii(other[i], i));
	}

	fill(ans, ans+N, -1);

	while (pq.size() > 0) {
		pii cur = pq.top();
		pq.pop();
//		debug(cur);
//		debug1(ans, N);

		if (ans[cur.SE] != -1) continue;

//		assert(cur.FI <= 1);

		vector<int> ones;
		for (set<int>::iterator it=adj[cur.SE].begin(); it!=adj[cur.SE].end(); it++) {
			if (adj[*it].size() == 1) {
				ones.PB(*it);
			}
		}
		if (ones.empty()) continue;

		for (set<int>::iterator it=adj[cur.SE].begin(); it!=adj[cur.SE].end(); it = adj[cur.SE].erase(it)) {
			adj[*it].erase(cur.SE);
			if (adj[*it].empty()) {
				ones.PB(*it);
			}
			else {
				pq.push(pii(--other[*it], *it));
			}
		}

		while (ones.size() > 2) {
			int x = ones.back();
			ones.pop_back();
			int y = ones.back();
			ones.pop_back();

			ans[x] = y;
			ans[y] = x;

			dist += 4;
		}

		if (ones.size() == 2) {
			int x = ones.back();
			ones.pop_back();
			int y = ones.back();
			ones.pop_back();
			ans[cur.SE] = x;
			ans[x] = y;
			ans[y] = cur.SE;
			dist += 4;
		}
		else {
			int x = ones.back();
			ones.pop_back();
			int y = cur.SE;

			ans[x] = y;
			ans[y] = x;

			dist += 2;
		}
	}

	cout << dist << endl;
	for (int i=0; i<N; i++) {
		if (i) cout << ' ';
		cout << ans[i] + 1;
	}
	cout << endl;
}

void solve2() {
	cin >> N;

	for (int i=0; i<N-1; i++) {
		int u, v;
		cin >> u >> v;

		--u;--v;

		adj[u].INS(v);
		adj[v].INS(u);
	}
	if (N == 2) {
		cout << 2 << endl;
		cout << 2 << ' ' << 1 << endl;
		return;
	}

	if (N > 10) {
		return;
	}

	int dist[10][10];
	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) dist[i][j] = INIT;
	}
	for (int i=0; i<N; i++) {
		for (set<int>::iterator it=adj[i].begin(); it!=adj[i].end(); it++) {
			dist[i][*it] = 1;
		}
	}

	for (int k=0; k<N; k++) {
		for (int i=0; i<N; i++) {
			for (int j=0; j<N; j++) {
				chmn(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}
	for (int i=0; i<N; i++) {
		for (int k=0; k<N; k++) {
			for (int j=0; j<N; j++) {
				chmn(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}
	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
			for (int k=0; k<N; k++) {
				chmn(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}

	vector<int> perm(N);
	for (int i=0; i<N; i++) {
		perm[i] = i+1;
	}

	ll best = INIT;
	vector<int> ans;
	do {
		ll cur = 0;
		for (int i=0; i<N; i++) {
			cur += dist[i][perm[i] - 1];
			if (i == perm[i]-1) cur += INIT;
		}
//		debug(perm);
//		debug(cur);
		if (cur < best) {
			best = cur;
			ans = perm;
		}
	}
	while (next_permutation(all(perm)));

	cout << best << endl;
	for (int i=0; i<N; i++) {
		if (i) cout << ' ';
		cout << ans[i];
	}
	cout << endl;
}

int main() {
	setIO();

	ll T = 1;
//	cin >> T;

	while (T-- > 0) solve1();
//	while (T-- > 0) solve2();

	return 0;
}
