/*
 * wandering_robot.cpp
 *
 *  Created on: Apr 18, 2020
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
#include <cfloat>

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

int chr[4] = {-1, 0, 1, 0};
int chc[4] = {0, 1, 0, -1};

const ll MOD = 1e9+7; // 998244353;
const int INIT = 1001001001;
const int MN = 100005;

void setIO() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
}

double paths(int r, int c) {
	double ret = 1;
	for (int i=c; i<r + c - 1; i++) {
		ret *= i;
		ret /= (i - c + 1);
	}
	return ret;
}

double prob[300][300];
void solve(int tc) {
	int W, H, L, U, R, D;
	cin >> W >> H >> L >> U >> R >> D;


	for (int i=1; i<=H; i++) {
		for (int j=1; j<=W; j++) {
			if (i == 1 && j == 1) prob[i][j] = 1;
			else {
				prob[i][j] = 0;
				if (i == H) {
					prob[i][j] += prob[i][j-1];
				}
				else {
					prob[i][j] += prob[i][j-1] / 2;
				}

				if (j == W) {
					prob[i][j] += prob[(i-1)][j];
				}
				else {
					prob[i][j] += prob[(i-1)][j] / 2;
				}
			}
//			cout << prob[i][j] << " ";
		}
//		cout << endl;
	}

	double fall = 0;
	double cur = paths(U, L-1) / pow(2, U+(L-1) - 2);
	if (L > 1) {
		if (D == H) {
			cur = paths(U, 1) / pow(2, U - 1);
			for (double n=U, k=1; k<L; n++, k++) {
				cout << int(n) << " " << L-1 << " " << cur << " " << prob[int(n)][int(1)] << endl;
				fall += cur;
				cur *= (n+1)/((k+1)*2);
			}
		}
		else {
			for (double n=U, k=L-1; n<=D; n++, k++) {
				cout << int(n) << " " << L-1 << " " << cur << " " << prob[int(n)][int(L-1)] << endl;

				if (n < H) {
					fall += cur/2;
				}
				else {
					fall += cur;
				}

				cur *= (n+1)/((k+1) * 2);
			}
		}
	}
	if (U > 1) {
		if (R == W) {
			cur = paths(L, 1) / pow(2, L - 1);
			for (double n=L, k=1; k<U; n++, k++) {
				cout << U-1 << " " << int(n) << " " << cur << " " << prob[int(U-1)][int(n)] << endl;
				fall += cur;
				cur *= (n+1)/((k+1)*2);
			}
		}
		else {
			cur = paths(U-1, L) / pow(2, L + (U-1) - 2);
			for (double n=L, k=U-1; n<=R; n++, k++) {
				cout << U-1 << " " << int(n) << " " << cur << " " << prob[int(U-1)][int(n)] << endl;

				if (n < W) {
					fall += cur/2;
				}
				else {
					fall += cur;
				}

				cur *= (n+1)/((k+1) * 2);
			}
		}
	}

	cout << "Case #" << tc << ": " << 1 - fall << endl;
}

int main() {
	setIO();

	int T;
	cin >> T;

	cout << fixed << setprecision(6);
	for (int t=1; t<=T; t++) {
		solve(t);
	}
	

	return 0;
}
//
//1
//4 7 3 3 4 6
