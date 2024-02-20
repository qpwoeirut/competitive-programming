/*
 * haircut.cpp
 *
 *  Created on: Mar 30, 2020
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

void chmn(int& a, const int& b) {if (a>b) a=b;}
void chmn(ll& a, const ll& b) {if (a>b) a=b;}
void chmx(int& a, const int& b) {if (a<b) a=b;}
void chmx(ll& a, const ll& b) {if (a<b) a=b;}

int chr[4] = {-1, 0, 1, 0};
int chc[4] = {0, 1, 0, -1};

void setIO(const string& name) {
    ios_base::sync_with_stdio(0);
	cin.tie(nullptr); cout.tie(nullptr);
    freopen((name+".in").c_str(), "r", stdin);
    freopen((name+".out").c_str(), "w", stdout);
}

const ll MOD = 1e9+7; // 998244353;
const ll INF = 1e18;
const int INIT = 1001001001;
const int MN = 100005;


int N;
int rev[MN];

ll BIT[MN*4];
void inc(int i) {
	for (; i<=N+2; i+=(i & -i)) {
//		cout << "inc i: " << i << endl;
		BIT[i]++;
	}
}
ll sum(int i) {
	ll ret = 0;
//	cout << "i, sum: " << i << " ";
	for (; i>0; i-=(i & -i)) {
//		cout << "sum i: " << i << endl;
		ret += BIT[i];
	}
//	cout << ret << endl;
	return ret;
}

ll total = 0;
ll ans[MN];
int main() {
	setIO("haircut");

	cin >> N;

	for (int i=N-1; i>=0; i--) {
		cin >> rev[i];
	}

	for (int i=N-1; i>=0; i--) {
//		PRS(BIT, N+2); cout << endl;
		ans[rev[i]+1] += total - sum(rev[i]+1);
		inc(rev[i]+1);
		total++;
//		cout << rev[i] << ": "; PRS(ans, N); cout << endl << endl;
	}

	ll cur = 0;
	for (int i=0; i<N; i++) {
		cur += ans[i];
		cout << cur << endl;
	}

	return 0;
}
