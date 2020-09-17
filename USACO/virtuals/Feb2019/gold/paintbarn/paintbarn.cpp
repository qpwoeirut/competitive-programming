/*
 * paintbarn.cpp
 *
 *  Created on: Mar 27, 2020
 *      Author: Stanley
 */


#include <fstream>
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
#include <map>
#include <queue>
#include <string>
#include <set>
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
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<int,bool> pib;
typedef pair<ll,bool> plb;
typedef vector<set<int> > vsi;
typedef vector<vector<int> > vvi;
typedef vector<set<pii> > vspi;
typedef vector<vector<pii> > vvpi;
typedef map<int,int> mii;
typedef map<ll,ll> mll;
typedef map<char, int> mci;
typedef map<string,int> msi;
typedef map<string,string> mss;

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

void setIO(const string& name) {
    ios_base::sync_with_stdio(0);
	cin.tie(nullptr); cout.tie(nullptr);
    freopen((name+".in").c_str(), "r", stdin);
    freopen((name+".out").c_str(), "w", stdout);
}

void chmn(int& a, const int& b) {if (a>b) a=b;}
void chmn(ll& a, const ll& b) {if (a>b) a=b;}
void chmx(int& a, const int& b) {if (a<b) a=b;}
void chmx(ll& a, const ll& b) {if (a<b) a=b;}

int chr[4] = {-1, 0, 1, 0};
int chc[4] = {0, 1, 0, -1};

const ll MOD = 1e9+7; // 998244353;
const ll INF = 1e18;
const int INIT = 1001001001;
const int MN = 100001;

struct Side {
	int r1, r2;
	int c;
	bool start;
	Side(int _r1, int _r2, int _c, bool s) {
		r1 = _r1;
		r2 = _r2;
		c = _c;
		start = s;
	}
};

struct cmp_side {
	inline const bool operator()(const Side& a, const Side& b) {
		if (a.c == b.c) {
			return a.start;
		}
		return a.c < b.c;
	}
};
struct cmp_pib {
	inline const bool operator()(const pib& a, const pib& b) {
		if (a.FI == b.FI) {
			return a.SE;
		}
		return a.FI < b.FI;
	}
};

int main() {
	setIO("paintbarn");

	int N, K;
	cin >> N >> K;

	set<Side, cmp_side> sides;
	int c1, r1, c2, r2;
	for (int i=0; i<N; i++) {
		cin >> c1 >> r1 >> c2 >> r2;
		sides.insert(Side(r1, r2, c1, true));
		sides.insert(Side(r1, r2, c2, false));
	}

	int prev = 0;
	int ct[2] = {0, 0};
	int active[202];
	fill(active, active+201, 0);
	for (set<Side>::iterator it=sides.begin(); it!=sides.end(); it++) {
		int cur = 0;
		for (int i=0; i<=200; i++) {
			cur += active[i];
			if (cur == K) {
				ct[1] += it->c - prev;
			}
			else if (cur == K-1) {
				ct[0] += it->c - prev;
			}
		}
		assert(cur == 0);
		if (it->start) {
			active[it->r1]++;
			active[it->r2]--;
		}
		else {
			active[it->r1]--;
			active[it->r2]++;
		}

		prev = it->c;
	}

	if (ct[1] == 0) {
		cout << ct[0] << endl;
	}
	else if (ct[0] <= 2) {
		cout << (ct[1] + ct[0]) << endl;
	}
	else {
		cout << max(ct[0], ct[1] + (ct[0] / 2) + 2) << endl;
	}

	return 0;
}
