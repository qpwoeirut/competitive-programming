/*
 * 1325d.cpp
 *
 *  Created on: Mar 13, 2020
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
const int MN = -1;

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

vector<ll> solve(ll u, ll v) {
	ll y = v - u;
	if ((u > v) || (y & 1)) {
		vector<ll> ans(1);
		ans[0] = -1;
		return ans;
	}
	if (u == 0) {
		if (v == 0) {
			return vector<ll>();
		}
		else {
			vector<ll> ans(2);
			ans[0] = v/2;
			ans[1] = v/2;
			return ans;
		}
	}
	if (u == v) {
		vector<ll> ans(1);
		ans[0] = u;
		return ans;
	}

	bitset<64> X(u);
	bitset<64> A((v-u)/2);
	bitset<64> a, b;
	bool good = true;
	for (int i=0; i<64; i++) {
		if (X[i] == 0 && A[i] == 0) {

		}
		else if (X[i] == 0 && A[i] > 0) {
			a[i] = 1;
			b[i] = 1;
		}
		else if (X[i] > 0 && A[i] == 0) {
			a[i] = 1;
		}
		else {
			good = false;
			break;
		}
	}
	if (good) {
		vector<ll> ans(2);
		ans[0] = a.to_ullong();
		ans[1] = b.to_ullong();
		return ans;
	}

	ll tans = (v - u)/2;
	vector<ll> ans(3);
	ans[0] = tans;
	ans[1] = tans;
	ans[2] = u;
	return ans;
}

int main() {
	setIO();

	ll u, v;
	cin >> u >> v;
	vector<ll> ans = solve(u, v);
	if (ans.size() > 0 && ans.back() == -1) {
		cout << -1 << endl;
		return 0;
	}
	cout << ans.size() << endl;
	for (int i=0; i<ans.size(); i++) {
		cout << ans[i] << " ";
	}
	cout << endl;

	return 0;
}
