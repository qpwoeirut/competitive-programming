/*
 * expectedComparisons.cpp
 *
 *  Created on: Apr 24, 2020
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
#include <stack>

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

class SpeedingUpBozosort {
private:
	int chr[4] = {-1, 0, 1, 0};
	int chc[4] = {0, 1, 0, -1};

	ll MOD = 1e9+7; // 998244353;
	int INIT = 1001001001;
	int MN = 1000;

	int to_num(const vector<int>& vec) {
		int n = 0;
		for (int i=0; i<vec.size(); i++) {
			n *= 8;
			n += vec[i];
		}
		return n;
	}
	vector<int> from_num(int n) {
		vector<int> ret;
		while (n > 0) {
			ret.push_back(n % 8);
			n /= 8;
		}
		reverse(all(ret));
		return ret;
	}
	bool sorted(const vector<int>& vec) {
		for (int i=0; i+1<vec.size(); i++) {
			if (vec[i] > vec[i+1]) return false;
		}
		return true;
	}
	double exp[20][300000];
	double dp(vector<int>& v, int total, int rem, double chp) {

		int as_num = to_num(v);
		if (rem == 0) {
			if (sorted(v)) {
				return v.size() - 1;
			}
			rem = total;
		}
		else if (exp[rem][as_num] != -1) {
			return exp[rem][as_num];
		}
//		cout << to_string(v) << " " << total << " " << rem << " " << chp << endl;

		exp[rem][as_num] = 0;
		for (int i=0; i<v.size(); i++) {
			for (int j=i+1; j<v.size(); j++) {
				if (v[i] == v[j]) continue;
				swap(v[i], v[j]);

				exp[rem][as_num] += dp(v, total, rem-1, chp) / chp;

				swap(v[i], v[j]);
			}
		}

//		cout << rem << " " << to_string(v) << " " << exp[rem][as_num] << endl;
		return exp[rem][as_num];
	}
public:
	SpeedingUpBozosort() {

	}
	double expectedComparisons(vector<int> A, int numSwaps) {
		int chp = (A.size() * (A.size() - 1)) / 2;
		numSwaps %= chp;
		for (int i=0; i<=numSwaps; i++) {
			for (int j=0; j<300000; j++) {
				exp[i][j] = -1;
			}
		}
		vector<int> ordered(A.begin(), A.end());
		sort(all(ordered));
		int cur = 0;
		for (int i=0; i<ordered.size(); i++) {
			if (i+1 < ordered.size() && ordered[i] == ordered[i+1]) continue;
			for (int j=0; j<A.size(); j++) {
				if (ordered[i] == A[j]) {
					A[j] = cur;
				}
			}
			cur++;
		}

		return dp(A, numSwaps, numSwaps, chp);
	}
};

int main() {
	SpeedingUpBozosort* obj = new SpeedingUpBozosort();
	int a[4] = {1,2,3,4};
	cout << (obj->expectedComparisons(vector<int>(a,a+4), 3)) << endl;
	int b[5] = {1,1,2,2,2};
	cout << (obj->expectedComparisons(vector<int>(b,b+5), 5)) << endl;
	int c[2] = {10, 0};
	cout << (obj->expectedComparisons(vector<int>(c,c+2), 1)) << endl;
	int d[2] = {7,4};
	cout << (obj->expectedComparisons(vector<int>(d,d+2), 47)) << endl;
//	int e[5] = {5,3,1,4,2};
//	cout << (obj->expectedComparisons(vector<int>(e,e+5), 1)) << endl;
//	cout << (obj->expectedComparisons(vector<int>(e,e+5), 3)) << endl;
//	int f[5] = {1,1,2,1};
//	cout << (obj->expectedComparisons(vector<int>(f,f+4), 4)) << endl;

	return 0;
}

#undef debug3
#undef debug2
#undef debug1
#undef debug

#undef UB
#undef LB

#undef rall
#undef all
#undef SE
#undef FI

#undef INS
#undef PB
#undef PF
