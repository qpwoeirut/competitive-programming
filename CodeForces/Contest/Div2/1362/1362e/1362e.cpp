/*
 * 1362e.cpp
 *
 *  Created on: Jun 3, 2020
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
const int MN = 1005001;

int N, P;
int A[MN];
mii ct[2];
set<int> diffs;

bool exists(const mii m, const int k) {
	return m.find(k) != m.end();
}

void add(int idx) {
	if (diffs.empty()) {
		ct[0][idx]++;
		diffs.INS(idx);
//		debug(ct[0]);debug(ct[1]);debug(diffs);
		while (exists(ct[0], idx) && ct[0][idx] == P) {
			ct[0].erase(idx);
			ct[0][++idx]++;
			diffs.INS(idx);
		}
	}
	else {
		int diff = *diffs.rbegin();
//		debug(diff);
		if (ct[0][diff] < ct[1][diff]) {
			ct[0][idx]++;
//			debug(ct[0]);debug(ct[1]);debug(diffs);
			if (exists(ct[0], idx) && exists(ct[1], idx) && ct[0][idx] == ct[1][idx]) {
				ct[0].erase(idx);
				ct[1].erase(idx);
				diffs.erase(idx);
			}
			else {
				diffs.insert(idx);
			}

			while (exists(ct[0], idx) && ct[0][idx] == P) {
				ct[0].erase(idx);
				ct[0][++idx]++;
				if (exists(ct[1], idx) && ct[1][idx] == 0) {
					ct[0].erase(idx);
					ct[1].erase(idx);
					diffs.erase(idx);
				}
				else {
					diffs.insert(idx);
				}
			}
		}
		else {
			ct[1][idx]++;
//			debug(ct[0]);debug(ct[1]);debug(diffs);
			if (exists(ct[0], idx) && exists(ct[1], idx) && ct[0][idx] == ct[1][idx]) {
				ct[0].erase(idx);
				ct[1].erase(idx);
				diffs.erase(idx);
			}
			else {
				diffs.insert(idx);
			}

			while (exists(ct[1], idx) && ct[1][idx] == P) {
				ct[1].erase(idx);
				ct[1][++idx]++;
				if (exists(ct[0], idx) && ct[0][idx] == 0) {
					ct[0].erase(idx);
					ct[1].erase(idx);
					diffs.erase(idx);
				}
				else {
					diffs.insert(idx);
				}
			}
		}
	}
}

void solve() {
	cin >> N >> P;

	for (int i=0; i<N; i++) {
		cin >> A[i];
	}

	if (P == 1) {
		cout << N%2 << endl;
		return;
	}

	diffs = set<int>();
	ct[0] = mii();
	ct[1] = mii();
	
	sort(A, A+N, greater<int>());
	for (int i=0; i<N; i++) {
//		debug(ct[0]);debug(ct[1]);debug(diffs);cout << endl;
		add(A[i]);
	}

//	debug(ct[0]);debug(ct[1]);debug(diffs);

	if (diffs.empty()) {
		cout << 0 << endl;
		return;
	}

	ll sum1 = 0, sum2 = 0;
	for (mii::iterator it=ct[0].begin(); it!=ct[0].end(); it++) {
		sum1 = (sum1 + (it->SE * binpow(P, it->FI, MOD)) % MOD) % MOD;
	}
	for (mii::iterator it=ct[1].begin(); it!=ct[1].end(); it++) {
		sum2 = (sum2 + (it->SE * binpow(P, it->FI, MOD)) % MOD) % MOD;
	}

	int diff = *diffs.rbegin();
	if (ct[0][diff] < ct[1][diff]) {
		swap(sum1, sum2);
	}

	cout << ((sum1 - sum2 + MOD + MOD) % MOD) << endl;
}

int main() {
	setIO();

	ll T = 1;
	cin >> T;

	while (T--) solve();

	return 0;
}
