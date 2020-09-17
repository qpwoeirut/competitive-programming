/*
 * 1374e.cpp
 *
 *  Created on: Jun 27, 2020
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

struct Book {
	int num;
	bool a, b;
	ll time;
};
string to_string(const Book& b) {
	return "{" + to_string(b.a) + " " + to_string(b.b) + " " + to_string(b.time) + "}";
}

struct comp_time {
	inline const bool operator()(const Book& a, const Book& b) {
		return a.time > b.time;
	}
};
struct comp_rev_time {
	inline const bool operator()(const Book& a, const Book& b) {
		return a.time < b.time;
	}
};

int get_time(const priority_queue<Book, vector<Book>, comp_time>& pq) {
	if (pq.empty()) return INIT;
	return pq.top().time;
}

Book book[MN];
void solve(bool hard) {
	ll N, M, K;
	if (hard) {
		cin >> N >> M >> K;
	}
	else {
		cin >> N >> K;
	}
	
	char c1, c2;
	for (int i=0; i<N; i++) {
		cin >> book[i].time >> c1 >> c2;
		book[i].a = c1 == '1';
		book[i].b = c2 == '1';
		book[i].num = i+1;
	}

	priority_queue<Book, vector<Book>, comp_time> alice, bob, both, other;
	for (int i=0; i<N; i++) {
		if (book[i].a && book[i].b) {
			both.push(book[i]);
		}
		else if (book[i].a) {
			alice.push(book[i]);
		}
		else if (book[i].b) {
			bob.push(book[i]);
		}
		else {
			other.push(book[i]);
		}
	}
	priority_queue<Book, vector<Book>, comp_rev_time> used_a, used_b, used_both, used_other;

	ll ans = 0;
	int ct = 0;
	int total = 0;
	while (alice.size() + bob.size() + both.size() > 0 && (ct < K)) {
		int ab = INIT;
		if (alice.size() > 0 && bob.size() > 0) {
			ab = alice.top().time + bob.top().time;
		}
		int c = INIT;
		if (both.size() > 0) {
			c = both.top().time;
		}
		if (ab == INIT && c == INIT) {
			ans = -1;
			break;
		}

		if (ab < c) {
			used_a.push(alice.top());
			used_b.push(bob.top());

			alice.pop(); bob.pop();
			ans += ab;
			total += 2;
		}
		else {
			used_both.push(both.top());

			both.pop();
			ans += c;
			total += 1;
		}
		++ct;
	}

	if (ct < K) {
		cout << -1 << endl;
		return;
	}

	if (!hard) {
		cout << ans << endl;
		return;
	}

	int cta = ct, ctb = ct;
	while (total < M) {
		if (alice.size() + bob.size() + both.size() + other.size() == 0) {
			cout << -1 << endl;
			return;
		}
		int opts[] = {get_time(alice), get_time(bob), get_time(both), get_time(other)};
		int idx = min_element(opts, opts+4) - opts;
//		debug1(opts, 4);
//		debug(idx);
//		debug(opts[idx]);

		assert(opts[idx] != INIT);

		ans += opts[idx];
		++total;
		if (idx == 0) {
			used_a.push(alice.top());
			alice.pop();

			++cta;
		}
		else if (idx == 1) {
			used_b.push(bob.top());
			bob.pop();

			++ctb;
		}
		else if (idx == 2) {
			used_both.push(both.top());
			both.pop();
		}
		else if (idx == 3) {
			used_other.push(other.top());
			other.pop();
		}
		else assert(false);

		while (cta > K && used_both.size() > 0 && used_both.top().time > get_time(bob)) {
			ans += bob.top().time - used_both.top().time;
			both.push(used_both.top());
			used_both.pop();

			used_b.push(bob.top());
			bob.pop();

			--cta;
		}
		while (ctb > K && used_both.size() > 0 && used_both.top().time > get_time(alice)) {
			ans += alice.top().time - used_both.top().time;
			both.push(used_both.top());
			used_both.pop();

			used_a.push(alice.top());
			alice.pop();

			--ctb;
		}
	}
	while (total > M) {
		if (used_a.empty() || used_b.empty() || both.empty()) {
			cout << -1 << endl;
			return;
		}
		ans += both.top().time - used_a.top().time - used_b.top().time;
		alice.push(used_a.top());
		used_a.pop();

		bob.push(used_b.top());
		used_b.pop();

		used_both.push(both.top());
		both.pop();

		--total;
	}

	cout << ans << endl;
	while (used_a.size() > 0) {
		cout << used_a.top().num << ' ';
		used_a.pop();
	}
	while (used_b.size() > 0) {
		cout << used_b.top().num << ' ';
		used_b.pop();
	}
	while (used_both.size() > 0) {
		cout << used_both.top().num << ' ';
		used_both.pop();
	}
	while (used_other.size() > 0) {
		cout << used_other.top().num << ' ';
		used_other.pop();
	}
	cout << endl;
}

int main() {
	setIO();

	ll T = 1;
//	cin >> T;

	while (T--) solve(true);

	return 0;
}

/*
3 1
2 1 0
4 0 1
5 1 1


------

3 2 1
4 1 0
5 0 1
8 1 1
 */
