/*
 * 1372d.cpp
 *
 *  Created on: Jul 10, 2020
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

ll A[MN];
//int L[MN], R[MN];
//bool in[MN];
ll psum[MN][2], ssum[MN][2];
void solve() {
	int N;
	cin >> N;
	
	ll sum = 0;
//	priority_queue<pll, vector<pll>, cmpf<ll,ll> > pq(true);
	for (int i=0; i<N; i++) {
		cin >> A[i];
//		L[i] = (i+N-1) % N;
//		R[i] = (i+1) % N;
//		in[i] = true;

//		pq.push(pll(A[i], i));



		sum += A[i];
	}
	psum[0][0] = A[0];
	psum[0][1] = 0;
	for (int i=1; i<N; i++) {
		psum[i][0] = psum[i-1][0];
		psum[i][1] = psum[i-1][1];

		psum[i][i&1] += A[i];
	}
	ssum[N-1][(N-1)&1] = A[N-1];
	ssum[N-1][N&1] = 0;
	for (int i=N-1; i>=0; i--) {
		ssum[i][0] = ssum[i+1][0];
		ssum[i][1] = ssum[i+1][1];

		ssum[i][i&1] += A[i];
	}

	ll ans = 0;
	for (int i=0; i<N; i++) {
		chmx(ans, psum[i][0] + ssum[i][1]);
		chmx(ans, psum[i][1] + ssum[i][0]);
	}

	cout << ans << endl;


//	while (pq.size() > 0) {
//		pll cur = pq.top();
//		pq.pop();
//
//		if (in[cur.SE] == false) continue;
//
//		while (!in[L[cur.SE]]) {
//			L[cur.SE] = L[L[cur.SE]];
//		}
//		while (!in[R[cur.SE]]) {
//			R[cur.SE] = R[R[cur.SE]];
//		}
//
//		debug(cur);
//		debug(L[cur.SE]);
//		debug(R[cur.SE]);
//
//		if (L[cur.SE] == cur.SE) {
//			assert(R[cur.SE] == cur.SE);
//			break;
//		}
//
//		sum -= cur.FI;
//		A[cur.SE] = A[L[cur.SE]] + A[R[cur.SE]];
//		in[L[cur.SE]] = false;
//		in[R[cur.SE]] = false;
//
//
//		pq.push(pll(A[cur.SE], cur.SE));
//
//		for (int i=0; i<N; i++) {
//			if (in[i]) cout << A[i] << ' ';
//			else cout << "X ";
//		}
//		cout << endl;
//	}
//
//	cout << sum << endl;
}

int main() {
	setIO();

	ll T = 1;
//	cin >> T;

	while (T-- > 0) solve();

	return 0;
}

/*
9
1 2 3 4 5 6 7 8 9
29

5
10 5 4 5 10
24

7
5 3 6 4 9 3 1
23

5
100 10 1 1 100
201

5
100 10 1 100 1
210

 */
