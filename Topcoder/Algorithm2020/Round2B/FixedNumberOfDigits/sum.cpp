/*
 * sum.cpp
 *
 *  Created on: Jul 18, 2020
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

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<set<int> > vsi;

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

int chr[8] = {-1, 0, 1, 0, -1, -1, 1, 1};
int chc[8] = {0, 1, 0, -1, -1, 1, -1, 1};

const ll MOD = 1e9+7; // 998244353;
const int INIT = 1001001001;
const int MN = -1;

class FixedNumberOfDigits {
private:
public:
	FixedNumberOfDigits() {

	}
	int sum(ll start, ll step, ll n) {
		ll tmp = start;
		ll p = 1;
		ll d = 0;
		while (tmp > 0) {
			tmp /= 10;
			p *= 10;
			++d;
		}
		chmx(p, 10LL);
		chmx(d, 1LL);
//		debug(d);
//		debug(p);
//		debug(((p - start + step - 1) / step) * d);

		while (n > ((p - start + step - 1) / step) * d) {
			n -= ((p - start + step - 1) / step) * d;
			start = ((p + step - 1) / step) * step;
			p *= 10;
			++d;
//			debug(start);
//			debug(n);
//			debug(d);
//			debug(p);
//			debug(((p - start + step - 1) / step) * d);
		}

//		debug(start);
//		debug(step);
//		debug(n);
//		debug(d);
		ll lo = 0, hi = n;
		while (lo < hi) {
			ll mid = (lo + hi + 1) / 2;
			if (mid * d < n) {
				lo = mid;
			}
			else {
				hi = mid - 1;
			}
		}
		start += step * lo;
//		debug(n);debug(lo);

		p = 1;
		for (ll j = n-(lo*d); j<d; j++) {
			p *= 10;
		}
//		debug(p);
		return start / p;
	}
};

int main() {
	FixedNumberOfDigits* obj = new FixedNumberOfDigits();
	cout << to_string(obj->sum(47, 10, 7)) << endl << endl;
	cout << to_string(obj->sum(98, 1, 10)) << endl << endl;
	cout << to_string(obj->sum(0, 1, 7)) << endl << endl;
	cout << to_string(obj->sum(123456789, 10, 5)) << endl << endl;
	cout << to_string(obj->sum(123456789, 10, 17)) << endl << endl;
	cout << to_string(obj->sum(1000000000, 10, 1e16)) << endl << endl;
	return 0;
}

#undef debug3
#undef debug2
#undef debug1
#undef debug
