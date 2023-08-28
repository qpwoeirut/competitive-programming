/*
 * 1066f.cpp
 *
 *  Created on: Jul 16, 2020
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
const int MN = 200001;

bool comp1(const pll& a, const pll& b) {
	if (a.SE == b.SE) {
		return a.FI < b.FI;
	}
	return a.SE > b.SE;
}
bool comp2(const pll& a, const pll& b) {
	if (a.FI == b.FI) {
		return a.SE < b.SE;
	}
	return a.FI > b.FI;
}

ll dist(const pll& a, const pll& b) {
	return abs(a.FI - b.FI) + abs(a.SE - b.SE);
}

int N;
map<int,pair<pll,pll> > key;
ll dp[MN][2];
void solve() {
	cin >> N;
	
	for (int i=0; i<N; i++) {
		pll tmp;
		cin >> tmp.FI >> tmp.SE;

		int k = max(tmp.FI, tmp.SE);

		if (key.find(k) == key.end()) {
			key[k] = make_pair(tmp, tmp);
		}
		else {
			key[k].FI = min(key[k].FI, tmp, comp1);
			key[k].SE = min(key[k].SE, tmp, comp2);
		}
	}
//	debug(key);

	map<int,pair<pll,pll> >::iterator it=key.begin();
	dp[0][0] = dist(it->SE.FI, it->SE.SE) + dist(pii(0,0), it->SE.SE);
	dp[0][1] = dist(it->SE.FI, it->SE.SE) + dist(pii(0,0), it->SE.FI);
	pair<pll,pll> prev = it->SE;
	it++;

	int M = key.size();
	for (int i=1; i<M; i++) {
//		debug(*it);
		dp[i][0] = dist(it->SE.FI, it->SE.SE) + min(dist(prev.FI, it->SE.SE) + dp[i-1][0], dist(prev.SE, it->SE.SE) + dp[i-1][1]);
		dp[i][1] = dist(it->SE.FI, it->SE.SE) + min(dist(prev.FI, it->SE.FI) + dp[i-1][0], dist(prev.SE, it->SE.FI) + dp[i-1][1]);
		prev = it->SE;
		++it;
	}

	cout << min(dp[M-1][0], dp[M-1][1]) << endl;
//	debug2(dp, M, 2);
}

int main() {
	setIO();

	ll T = 1;
//	cin >> T;

	while (T-- > 0) solve();

	return 0;
}
