/*
 * 496e.cpp
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
const int MN = 100001;

struct Actor {
	int c, d;
	int k;
	int num;
};

struct Part {
	int a, b;
	int assigned;
	int idx;
};

string to_string(const Actor& p) {
	return to_string(p.c) + '-' + to_string(p.d) + ": " + to_string(p.k) + ',' + to_string(p.num);
}
string to_string(const Part& p) {
	return to_string(p.a) + '-' + to_string(p.b) + ": " + to_string(p.assigned);
}

struct cmp_b {
	inline const bool operator()(const Part& a, const Part& b) const {
		if (a.b == b.b) {
			return a.a < b.a;
		}
		return a.b < b.b;
	}
};
struct cmp_d {
	inline const bool operator()(const Actor& a, const Actor& b) const {
		if (a.d == b.d) {
			return a.c < b.c;
		}
		return a.d < b.d;
	}
};
struct cmp_a {
	inline const bool operator()(const Part& a, const Part& b) const {
		if (a.a == b.a) {
			return a.b < b.b;
		}
		return a.a < b.a;
	}
};
struct cmp_c {
	inline const bool operator()(const Actor& a, const Actor& b) const {
		if (a.c == b.c) {
			return a.d < b.d;
		}
		return a.c < b.c;
	}
};
struct cmp_idx {
	inline const bool operator()(const Part& a, const Part& b) const {
		return a.idx < b.idx;
	}
};

Part part[MN];
Actor actor[MN];
int uses[MN];
void solve() {
	int N, M;
	cin >> N;

	set<int> points;
	for (int i=0; i<N; i++) {
		cin >> part[i].a >> part[i].b;
		part[i].idx = i;
		part[i].assigned = -1;

		points.INS(part[i].a);
		points.INS(part[i].b);
	}
	sort(part, part+N, cmp_a());

	cin >> M;
	for (int i=0; i<M; i++) {
		cin >> actor[i].c >> actor[i].d >> actor[i].k;
		actor[i].num = i+1;

		points.INS(actor[i].c);
		points.INS(actor[i].d);
	}
	sort(actor, actor+M, cmp_c());

	vector<Part> done;
	multiset<Part, cmp_b> aparts;
	multiset<Actor, cmp_d> aactors;
	int pi = 0, ai = 0;
	for (set<int>::iterator it=points.begin(); it!=points.end(); it++) {
		while (pi < N && part[pi].a <= *it) {
			aparts.INS(part[pi++]);
		}
		while (ai < M && actor[ai].c <= *it) {
			aactors.INS(actor[ai++]);
		}
		while (aactors.size() > 0 && aactors.begin()->d < *it) {
			aactors.erase(aactors.begin());
		}
//		debug(ai);
//		debug(pi);
//		debug(aparts);
//		debug(aactors);

		while (aparts.size() > 0) {
			Part cur = *aparts.begin();
			Actor dummy;
			dummy.c = -INIT;
			dummy.d = cur.b;
			multiset<Actor, cmp_d>::iterator choice = aactors.LB(dummy);
			if (choice == aactors.end()) {
				break;
			}

			aparts.erase(aparts.begin());
			cur.assigned = choice->num;
			done.PB(cur);

			if (++uses[choice->num] == choice->k) {
				aactors.erase(choice);
			}
		}

		if (!aparts.empty()) {
			break;
		}
	}
//	debug(done);

	if (done.size() != N) {
		cout << "NO" << endl;
		return;
	}

	sort(all(done), cmp_idx());

	cout << "YES" << endl;
	for (int i=0; i<done.size(); i++) {
		if (i) cout << ' ';
		assert(done[i].idx == i);
		cout << done[i].assigned;
	}
	cout << endl;
}

int main() {
	setIO();

	ll T = 1;
//	cin >> T;

	while (T-- > 0) solve();

	return 0;
}
