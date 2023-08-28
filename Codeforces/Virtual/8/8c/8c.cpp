/*
 * 8c.cpp
 *
 *  Created on: Apr 1, 2020
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
const int MN = 105;

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
pii thing[MN];
int to_bag[MN];
int dist[MN][MN];

inline const int get_dist(const pii& a, const pii& b) {
	return ((a.FI - b.FI) * (a.FI - b.FI)) + ((a.SE - b.SE) * (a.SE - b.SE));
}

int states[(1 << 25)];
vector<int> ans, ord;
int best = INIT;
void rec(const int& idx, const int& cost, int done) {
	if (best <= cost) return;
	if (idx >= N) {
		if (best > cost) {
			best = cost;
			ans = ord;
		}
		return;
	}
	if (done & (1 << idx)) {
		rec(idx+1, cost, done);
		return;
	}
	done |= (1 << idx);
//	if (states[done] < cost) {
//		return;
//	}

	ord.PB(0);
	ord.PB(idx+1);

	for (int i=idx+1; i<N; i++) {
		if (done & (1 << i)) continue;
		if (to_bag[idx] + dist[idx][i] + to_bag[i] < 2 * (to_bag[idx] + to_bag[i])) {
			ord.PB(i+1);
			rec(idx + 1, cost + to_bag[idx] + dist[idx][i] + to_bag[i], done | (1 << i));
			ord.pop_back();
		}
	}

	rec(idx+1, cost + to_bag[idx] + to_bag[idx], done);
	states[done] = cost;
	ord.pop_back(); ord.pop_back();
}

int main() {
	setIO();

	pii bag;
	cin >> bag.FI >> bag.SE;

	cin >> N;
	for (int i=0; i<N; i++) {
		cin >> thing[i].FI >> thing[i].SE;
		to_bag[i] = get_dist(bag, thing[i]);
	}
	
	for (int i=0; i<N; i++) {
		for (int j=i+1; j<N; j++) {
			dist[i][j] = get_dist(thing[i], thing[j]);
			dist[j][i] = dist[i][j];
		}
		dist[i][i] = 0;
	}
	for (int i=0; i<(1<<(N+1)); i++) {
		states[i] = INIT;
	}

	rec(0, 0, 0);

	cout << best << endl;
	for (int i=0; i<ans.size(); i++) {
		cout << ans[i] << ' ';
	}
	cout << '0' << endl;

	return 0;
}
