/*
 * 1364d.cpp
 *
 *  Created on: Jun 12, 2020
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

const ll MOD = 1e9+7; // 998244353;
const int INIT = 1001001001;
const int MN = 100001;

vsi adj;
int mark[MN], par[MN];
vector<int> cycle, nx;
void dfs(int node) {
	bool c = false;
	mark[node] = 1;
	for (set<int>::iterator it=adj[node].begin(); it!=adj[node].end(); it++) {
		if (*it == par[node]) continue;
		if (mark[*it] == 0) {
			par[*it] = node;
			dfs(*it);
		}
		else if (mark[*it] == 1) {
			c=  true;
			break;
		}
	}
	mark[node] = 2;

	if (c) {
		while (node != -1) {
			nx.PB(node);
			node = par[node];
		}
		if (cycle.empty() || nx.size() < cycle.size()) {
			cycle = nx;
		}
	}
}

//int A[MN];
void solve() {
	int N, M, K;
	cin >> N >> M >> K;

	adj = vsi(N, set<int>());
	int u, v;
	for (int i=0; i<M; i++) {
		cin >> u >> v;
		u--; v--;
		adj[u].INS(v);
		adj[v].INS(u);
	}

	fill(par, par+N, -1);
	fill(mark, mark+N, 0);
	for (int i=0; i<N; i++) {
		if (mark[i] == 0) {
			par[i] = -1;
			dfs(i);
		}
	}

//	debug(cycle);

//	mii rev;
//	for (int i=0; i<cycle.size(); i++) {
//		rev[cycle[i]] = i;
//	}
//	for (int i=0; i<cycle.size(); i++) {
//		for (set<int>::iterator it=adj[cycle[i]].begin(); it!=adj[cycle[i]].end(); it++) {
//			if (*it == cycle[(i+cycle.size()-1)%cycle.size()] || *it == cycle[(i+1)%cycle.size()]) continue;
//			if (rev.find(*it) != rev.end()) {
//				vector<int> new_cycle;
//				if ((i + (cycle.size() / 2)) % cycle.size() > rev[*it]) {
//					for (int j=0; j+i<rev[*it]; j++) {
//						new_cycle.PB(cycle[i+j]);
//					}
//				}
//				else {
//					for (int j=0; (j-i+cycle.size())%cycle.size())
//				}
//			}
//		}
//	}

	if (cycle.size() > 2 && cycle.size() <= K) {
		cout << 2 << endl;
		cout << cycle.size() << endl;
		for (int i=0; i<cycle.size(); i++) {
			if (i) cout << ' ';
			cout << cycle[i] + 1;
		}
		cout << endl;
	}
	else {


		cout << 1 << endl;
		if (cycle.size() > K) {
			for (int i=0; i<=K; i+=2) {
				if (i)cout << ' ';
				cout << cycle[i] + 1;
			}
			cout << endl;
		}
		else {
			int other = -1;
			int idx = -1;
			for (int i=0; i<cycle.size(); i++) {
				if (adj[cycle[i]].size() > 2) {
					for (set<int>::iterator it=adj[cycle[i]].begin(); it!=adj[cycle[i]].end(); it++) {
						if (*it != cycle[(i+cycle.size()-1) %cycle.size()] && *it != cycle[(i+1)%cycle.size()]) {
							other = *it;
							idx = i;
							break;
						}
					}
				}
				if (other != -1) break;
			}
			assert(other != -1);

			cout << other;
			for (int i=0; i<K; i+=2) {
				cout << ' ' << cycle[(idx+i)%cycle.size()] + 1;
			}
			cout << endl;
		}
	}
}

int main() {
	setIO();

	ll T = 1;
//	cin >> T;

	while (T--) solve();

	return 0;
}
