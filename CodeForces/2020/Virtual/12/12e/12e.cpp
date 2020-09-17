/*
 * 12e.cpp
 *
 *  Created on: Jul 6, 2020
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
const int MN = 1001;

set<int> row[MN], col[MN];
int G[MN][MN];
void solve() {
	int N;
	cin >> N;
	
	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
			G[i][j] = -1;
			row[i].insert(j);
			col[i].insert(j);
		}
	}

	for (int i=0; i<N; i++) {
		for (int j=0; i+j<N; j++) {
			if (i == j) {
				G[i][j] = 0;
			}
			else {
				G[i][j] = i+j;
			}
			row[i].erase(G[i][j]);
			col[j].erase(G[i][j]);
		}
	}
	int start;
	for (int i=1; i<N; i++) {
		for (int j=N-i; j<N; j++) {
			if (i == j) {
				G[i][j] = 0;
			}
			else if (G[j][i] != -1) {
				G[i][j] = G[j][i];
			}
			else {
				start = (i+j + (N/2)) & 1;
				set<int>::iterator rit = row[i].begin();
				set<int>::iterator cit = col[j].begin();
				while (*rit != *cit) {
					if (*rit < *cit) {
						++rit;
					}
					else {
						++cit;
					}
					assert(rit != row[i].end());
					assert(cit != col[j].end());
				}
				G[i][j] = *rit;
			}
			row[i].erase(G[i][j]);
			col[j].erase(G[i][j]);
		}
	}

	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
			if (j) cout << ' ';
			cout << G[i][j];
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

/*
0 1
1 0

0 1 2 3
1 0 3 2
2 3 0 1
3 2 1 0

0 1 2 3 4 5
1 0 3 4 5 2
2 3 0 5 1 4
3 4 5 0 2 1
4 5 1 2 0 3
5 2 4 1 3 0

0 1 2 3 4 5 6 7
1 0 3 4 5 6 7 2
2 3 0 5 6 7 4 1
3 4 5 0 7 2 1 6
4 5 6 7 0 1 2 3
5 6 7 2 1
 */
