/*
 * 284d.cpp
 *
 *  Created on: Mar 27, 2020
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
const int INIT = -2;
const int MN = 200001;

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
int a[MN];
ll mem[MN];
bool visited[MN];
ll dp(int x) {
	if (x<=0 || x>N) {
		return 0;
	}
	if (mem[x] != INIT) {
		return mem[x];
	}
	if (visited[x]) {
		mem[x] = -1;
		return mem[x];
	}
	int idx = x;

	ll y = a[x-1];
	x += a[x-1];
	if (x > N) {
		mem[idx] = y;
		return mem[idx];
	}

	y += a[x-1];
	x -= a[x-1];
	if (x <= 0) {
		mem[idx] = y;
		return mem[idx];
	}

	visited[idx] = true;
	mem[idx] = dp(x);
	visited[idx] = false;
	if (mem[idx] != -1) {
		mem[idx] += y;
	}
	return mem[idx];
}

int main() {
	setIO();

	cin >> N;
	for (int i=1; i<N; i++) {
		cin >> a[i];
	}

	for (int i=0; i<=N; i++) {
		mem[i] = INIT;
		visited[i] = false;
	}
	mem[0] = 0;
	mem[1] = -1;
	for (int i=1; i<N; i++) {
		ll x = i+1;
		ll y = i;
		y += a[x-1];
		x -= a[x-1];
		ll ret = dp(x);
		if (ret != -1) {
			ret += y;
		}
		cout << ret << endl;
	}

	return 0;
}
