/*
 * colors.cpp
 *
 *  Created on: Jul 28, 2020
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
const int MN = -1; //200001;

ll N, M, K;
//int A[MN];
//int G[MN][MN];
//set<int> adj[MN];
//ll X;
//ll last = -1;
char c;
bool query(ll center, ll mid) {
	ll left = center - mid;
	ll right = center + mid;

	cout << "? " << left << endl;
	cin >> c;
	cout << "? " << right << endl;
//	last = right;
	cin >> c;

//	if (right - left >= X) {
//		c = '1';
//	}
//	else {
//		c = '0';
//	}
//	cout << c << endl;
	return c == '1';
}

void solve() {
	cin >> N;

	if (N > 125) {
		ll center = (N+1) / 2;
		ll lo = 1, hi = N;
		ll mid = center;
		while (lo + 4 < hi) {
			mid = (lo + hi + 3) / 4;
//			mid = (mid + 1) >> 1;
			if (query(center, mid)) {
				hi = mid;
			}
			else {
				lo = mid + 1;
			}
		}

		if (c == '1') {
			cout << "? " << center - mid + 1 << endl;
			cin >> c;
			if (c == '1') {
				cout << "?" << center + mid - 1 << endl;
				cin >> c;
				if (c == '1') {
					cout << "= " << mid * 2 - 2 << endl;
				}
				else {
					cout << "= " << mid * 2 - 1 << endl;
				}
			}
			else {
				cout << "= " << mid * 2 << endl;
			}
		}
		else {
			cout << "? " << center - mid - 1 << endl;
			cin >> c;
			if (c == '1') {
				cout << "? " << center + mid + 1 << endl;
				cin >> c;
				if (c == '1') {
					cout << "= " << mid * 2 + 2 << endl;
				}
				else {
					cout << "= " << mid * 2 + 1 << endl;
				}
			}
			else {
				cout << "= " << mid * 2 << endl;
			}
		}
	}
	else {
		if (N == 2) {
			cout << "? 1" << endl;
			cin >> c;

			cout << "? 2" << endl;
			cin >> c;

			if (c == '1') {
				cout << "= 1" << endl;
			}
			else {
				cout << "= 2" << endl;
			}
			return;
		}



		ll cur = (N+1)/2;
		cout << "? " << cur << endl;
		cin >> c;
		ll m = 1;
		ll ans = 2;
		for (; cur + m*ans > 0 && cur + m*ans <= N; ans+=2) {
			cur += m*ans;
			m = -m;

			cout << "? " << cur << endl;
			cin >> c;

			if (c == '1') {
				ll check = cur + m*(ans - 1);
				cout << "? " << check << endl;
				cin >> c;

				if (c == '1') {
					cout << "= " << ans-1 << endl;
				}
				else {
					cout << "= " << ans << endl;
				}
				return;
			}
		}

		if (ans - 1 == N) {
			cout << "= " << N << endl;
			return;
		}

	//	debug(cur);
	//	debug(m);
	//	debug(ans);
		if (m == 1) {
			cout << "? " << N << endl;
			cin >> c;
			bool x = c == '1';

			if (cur == 1) {
				if (x) {
					cout << "= " << N-1 << endl;
				}
				else {
					cout << "= " << N << endl;
				}
				return;
			}

			cout << "? 1" << endl;
			cin >> c;
			if (c == '0') {
				cout << "= " << N << endl;
			}
			else if (x == false) {
				cout << "= " << N-1 << endl;
			}
			else {
				cout << "= " << N-2 << endl;
			}
		}
		else {
			cout << "? " << 1 << endl;
			cin >> c;
			bool x = c == '1';

			if (cur == N) {
				if (x) {
					cout << "= " << N-1 << endl;
				}
				else {
					cout << "= " << N << endl;
				}
				return;
			}

			cout << "? " << N << endl;
			cin >> c;

			if (c == '0') {
				cout << "= " << 1 << endl;
			}
			else if (x == false) {
				cout << "= " << 2 << endl;
			}
			else {
				cout << "= " << 3 << endl;
			}
		}
	}
}

int main() {
	setIO();

	ll T = 1;
	cin >> T;

	while (T-- > 0) solve();

	return 0;
}
