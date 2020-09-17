/*
 * 1373e.cpp
 *
 *  Created on: Jun 24, 2020
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
const int MN = 1e6;

ll solve0(ll N) {
	ll ret = 0;
	if ((N % 9) != 0) {
		ret += (N % 9);
		N -= (N % 9);
	}
	while (N > 0) {
		ret *= 10;
		ret += 9;
		N -= 9;
	}

	return ret;
}

ll f(ll num) {
	ll ret = 0;
	while (num > 0) {
		ret += num % 10;
		num /= 10;
	}
	return ret;
}

ll A[MN];
void solve(int t) {
	ll N, K;
	cin >> N >> K;
//	N = t; K = 1;
//	cout << N << ' ' << K << endl;

	if (K == 0) {
		cout << solve0(N) << endl;
		return;
	}
	else if (K == 1) {
		if (N & 1) {
			ll ans = solve0((N + 1) / 2);
			assert(ans % 10 != 0);
			ans--;
			cout << ans << endl;
			return;
		}
		else {
			ll best = 1e18;
			for (ll i=0; i<N; i++) {
				for (ll j=0; j<N; j++) {
					ll x = solve0(i + j);
					ll a = x < MN ? A[x] : f(x);
					ll b = x+1 < MN ? A[x+1] : f(x+1);
					if (a + b == N) {
						chmn(best, x);
					}
				}
			}

			ll nines = N/9;
			ll others = N % 9;
			if (others < 9) {
				nines--;
				others += 9;
			}
			if (nines % 2 == 1) {
				ll cur = 0;
				while (nines > 1) {
					nines -= 2;
					cur *= 10;
					cur += 9;
				}
				assert(nines == 1);
				cur *= 10;
				cur += others / 2;
				cur *= 10;
				cur += 9;

				if (f(cur) + f(cur + 1) == N) {
					chmn(best, cur);
				}
			}


			if (best != 1e18) {
				cout << best << endl;
				return;
			}
		}
	}
	else {
		ll cur = 0;
		for (int i=0; i<=K; i++) {
			cur += A[i];
		}
		for (int i=0; i<MN; i++) {
			if (cur == N) {
				cout << i << endl;
				return;
			}
			cur += A[i+K+1] - A[i];
		}
	}

	cout << -1 << endl;
}

int main() {
	setIO();

	ll T = 1;
	cin >> T;

	for (int i=0; i<MN; i++) {
		A[i] = f(i);
	}

	while (T--) solve(T);

	return 0;
}

/*
28 1
15 3
44 1
 */
