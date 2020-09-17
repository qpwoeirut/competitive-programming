/*
 * security_update.cpp
 *
 *  Created on: May 16, 2020
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
typedef vector<multiset<pii> > vspi;
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
const int MN = 101;

void setIO() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
}

vspi adj;
int mat[MN][MN];
int X[MN];
int dist[MN];

void solve(int tc) {
	int V, E;
	cin >> V >> E;
	assert(V < MN);

	X[0] = 0;
	for (int i=1; i<V; i++) {
		cin >> X[i];
		X[i] = -X[i];
		assert(X[i] > 0);
		dist[i] = INIT;
	}

	for (int i=0; i<V; i++) {
		for (int j=0; j<V; j++) {
			mat[i][j] = INIT;
		}
	}

	adj = vspi(V, multiset<pii>());
	int u, v;
	for (int i=0; i<E; i++) {
		cin >> u >> v;

		u--; v--;
		adj[u].insert(pii(v, i));
		adj[v].insert(pii(u, i));
		mat[u][v] = 1;
		mat[v][u] = 1;
	}

	priority_queue<pii, vector<pii>, cmps<int,int> > pq(true);
	pq.push(pii(0, 0));
	dist[0] = 0;

	int rec = 0, tm = 0, waiting = 0;
	while (pq.size() > 0) {
		pii cur = pq.top();
		pq.pop();

		if (tm < cur.SE) {
			tm = cur.SE;
			rec += waiting;
			waiting = 0;
		}
		assert(tm == cur.SE);

//		debug(cur);
//		debug(rec);
//		debug(tm);
//		debug(X[cur.FI]);

		if (X[cur.FI] > rec) {
			int cdist = INIT;
			int nxt = 1e5;
			if (pq.size() > 0) {
				nxt = pq.top().SE;
			}
			for (multiset<pii>::iterator it=adj[cur.FI].begin(); it!=adj[cur.FI].end(); it++) {
				if (dist[it->FI] == INIT) continue;
				mat[cur.FI][it->FI] = nxt - dist[it->FI] + 1;
				mat[it->FI][cur.FI] = mat[cur.FI][it->FI];
				chmn(cdist, dist[it->FI] + mat[cur.FI][it->FI]);
			}
			assert(cdist > cur.SE);
			dist[cur.FI] = cdist;
			pq.push(pii(cur.FI, cdist));
//			debug(pii(cur.FI, cdist));
			continue;
		}

		for (multiset<pii>::iterator it=adj[cur.FI].begin(); it!=adj[cur.FI].end(); it++) {
			if (dist[it->FI] > dist[cur.FI] + mat[cur.FI][it->FI]) {
				dist[it->FI] = dist[cur.FI] + mat[cur.FI][it->FI];
				pq.push(pii(it->FI, dist[it->FI]));
			}
		}

		++waiting;
	}
	rec += waiting;
	assert(rec == V);

	int edges[1001];
	for (int i=0; i<V; i++) {
		for (multiset<pii>::iterator it=adj[i].begin(); it!=adj[i].end(); it++) {
			edges[it->SE] = mat[i][it->FI];
			assert(mat[i][it->FI] <= 1e6);
		}
	}

	for (int i=0; i<V; i++) {
		for (int j=0; j<V; j++) {
			assert(mat[i][j] == mat[j][i]);
		}
	}

	cout << "Case #" << tc << ":";
	for (int i=0; i<E; i++) {
		cout << ' ' << edges[i];
	}
	cout << endl;
}

int main() {
	setIO();

	int T;
	cin >> T;

	for (int t=1; t<=T; t++) {
		solve(t);
	}
	

	return 0;
}
