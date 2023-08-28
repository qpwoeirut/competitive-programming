/*
 * 1326d.cpp
 *
 *  Created on: Mar 18, 2020
 *      Author: Stanley
 */


#include <iostream>
#include <algorithm>
#include <cassert>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <utility>
#include <bitset>
#include <deque>
#include <forward_list>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

#define PF push_front
#define PB push_back
#define INS insert

#define FI first
#define SE second
#define BE begin
#define EN end

#define LB lower_bound
#define UB upper_bound

#define PRS(A, N) for (int i=0; i<N; i++) cout << A[i] << " ";
#define PRL(A, N) for (int i=0; i<N; i++) cout << A[i] << endl;
#define PSPR(A, N) for (int i=0; i<N; i++) cout << A[i].FI << "," << A[i].SE << " ";
#define PLPR(A, N) for (int i=0; i<N; i++) cout << A[i].FI << "," << A[i].SE << endl;
#define PSISET(A) for (set<int>::iterator it=A.BE(); it!=A.EN(); it++) cout << *it << " ";
#define PSSSET(A) for (set<string>::iterator it=A.BE(); it!=A.EN(); it++) cout << *it << " ";
#define PLISET(A) for (set<int>::iterator it=A.BE(); it!=A.EN(); it++) cout << *it << endl;
#define PLSSET(A) for (set<string>::iterator it=A.BE(); it!=A.EN(); it++) cout << *it << endl;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,bool> pib;
typedef pair<int,int> pii;
typedef pair<ll,bool> plb;
typedef pair<ll,ll> pll;
typedef vector<set<int> > vsi;
typedef vector<vector<int> > vvi;
typedef vector<set<pii> > vspi;
typedef vector<vector<pii> > vvpi;
typedef map<int,int> mii;
typedef map<ll,ll> mll;
typedef map<char, int> mci;
typedef map<string,int> msi;
typedef map<string,string> mss;

ll gcd(ll a, ll b) {return b ? gcd(b, a%b) : a;}

template <class T1, class T2> struct cmpf {
	bool rev;
	inline bool operator() (const pair<T1,T2>& a, const pair<T1,T2>& b) const {return (a.FI<b.FI)^rev;}
	cmpf(bool b=false) {rev=b;}
};
template <class T1, class T2> struct cmps {
	bool rev;
	inline bool operator() (const pair<T1,T2>& a, const pair<T1,T2>& b) const {return (a.SE<b.SE)^rev;}
	cmps(bool b=false) {rev=b;}
};

void chmn(int& a, const int& b) {if (a>b) a=b;}
void chmn(ll& a, const ll& b) {if (a>b) a=b;}
void chmx(int& a, const int& b) {if (a<b) a=b;}
void chmx(ll& a, const ll& b) {if (a<b) a=b;}

int chr[4] = {-1, 0, 1, 0};
int chc[4] = {0, 1, 0, -1};

const ll MOD = 1e9+7; // 998244353;
const ll INF = 1e18;
const int INIT = 1001001001;
const int MN = 1000001;

void setIO() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
}

ll binpow(const ll& x, const ll& p) {
	if (p == 0) return 1;
	if (p == 1) return x % MOD;
	if (p & 1) return (binpow((x*x) % MOD, p/2) * x) % MOD;
	return binpow((x*x) % MOD, p/2) % MOD;
}

int N;
string s, ans;
bool isPalin(int L, int len) {
	for (int i=0; i<len/2; i++) {
		if (s[L+i] != s[L+len-i-1]) {
			return false;
		}
	}
	return true;
}

struct Node {
	int start, end;
	int len;
	int insEdge[26];
	int sufEdge;

	Node() {}
	Node(int _start, int _len, int idx, int ptr) {
		start = _start;
		len = _len;
		end = start + len - 1;
		fill(insEdge, insEdge+26, 0);
		insEdge[s[idx] - 'a'] = ptr;
		sufEdge = 0;
	}
};

Node root1, root2;
Node ptree[MN];

int cur, ptr;

void insert(int idx) {
	int tmp = cur;
	while (true) {
		int curlen = ptree[tmp].len;
		if (idx - curlen >= 1 && s[idx] == s[idx - curlen - 1]) {
			break;
		}
		tmp = ptree[tmp].sufEdge;
	}
	if (ptree[tmp].insEdge[s[idx] - 'a'] != 0) {
		cur = ptree[tmp].insEdge[s[idx] - 'a'];
		return;
	}
	ptr++;

	ptree[tmp] = Node(idx - ptree[tmp].len - 2, ptree[tmp].len + 2, idx, ptr);

	tmp = ptree[tmp].sufEdge;
	cur = ptr;

	if (ptree[cur].len == 1) {
		ptree[cur].sufEdge = 2;
		return;
	}

	while (true) {
		int curlen = ptree[tmp].len;
		if (idx - curlen >= 1 && s[idx] == s[idx - curlen - 1]) {
			break;
		}
		tmp = ptree[tmp].sufEdge;
	}

	ptree[cur].sufEdge = ptree[tmp].insEdge[s[idx] - 'a'];
}


string palins[MN];
void solve() {
	cin >> s;
	N = s.size();

	if (isPalin(0, N)) {
		cout << s << endl;
		return;
	}


	for (int i=0; i<N; i++) {
		ptree[i] = Node(0, 0, 0, 0);
	}

	root1.len = -1;
	root1.sufEdge = 1;
	root2.len = 0;
	root2.sufEdge = 1;

	ptree[1] = root1;
	ptree[2] = root2;
	ptr = 2;
	cur = 1;

	for (int i=0; i<N; i++) {
		insert(s[i]);
	}

	int L = 0, R = N-1;
	while (L < R) {
		if (s[L] == s[R]) {
			L++; R--;
		}
		else {
			break;
		}
	}
	R++;

	int start = 0, end = 0;
	int cleft = 0, cright = 0;
	for (int i=3; i<=ptr; i++) {
		cout << ptree[i].len << " ";
		if (ptree[i].start == 0 && ptree[i].len > start) {
			chmx(start, ptree[i].len);
		}
		if (ptree[i].end == N-1 && ptree[i].len > end) {
			chmx(end, ptree[i].len);
		}
		if (ptree[i].start == L && ptree[i].len > cleft) {
			chmx(cleft, ptree[i].len);
		}
		if (ptree[i].end == R-1 && ptree[i].len > cright) {
			chmx(cright, ptree[i].len);
		}
	}
	cout << endl;

	cout << start << " " << end << " " << cleft << " " << cright << endl;
	string center;
	if (cleft >= cright) {
		center = s.substr(0, L + cleft) + s.substr(R, string::npos);
	}
	else {
		center = s.substr(0, L) + s.substr(R - cright, string::npos);
	}

	if (start >= end && start >= center.size()) {
		cout << s.substr(0, start) << endl;
		return;
	}
	else if (end >= start && end >= center.size()) {
		cout << s.substr(N-end, string::npos) << endl;
		return;
	}
	else {
		cout << center << endl;
		return;
	}
}


int main() {
	setIO();

	int T;
	cin >> T;

	while (T > 0) {
		T--;
		solve();
	}
	

	return 0;
}
