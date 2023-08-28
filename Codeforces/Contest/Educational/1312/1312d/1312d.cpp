/*
 * 1312d.cpp
 *
 *  Created on: Mar 8, 2020
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

const ll MOD = 998244353;
const ll INF = 1e18;
const int INIT = 1001001001;
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

int get_degree(ll n) {
	int deg = 0;
	ll u = MOD;

	while (u <= n) {
		deg += n/u;
		u *= MOD;
	}

	return deg;
}

ll choose(ll n, ll k) {
	if (n == k || n == 0 || k == 0) return 1;
	if (n < k) return 0;
	int ndeg = get_degree(n) - get_degree(n-k);
	int ddeg = get_degree(k);

	if (ndeg > ddeg) {
		return 0;
	}

	ll res = 1;
	for (ll i=n; i>n-k; i--) {
		ll ti = i;
		while (ti % MOD == 0) {
			ti /= MOD;
		}
		res = (res * ti) % MOD;
		assert(res >= 0);
	}
	ll den = 1;
	for (ll i=1; i<=k; i++) {
		ll ti = i;
		while (ti % MOD == 0) {
			ti /= MOD;
		}
		den = (den * ti) % MOD;
		assert(den >= 0);
	}

	res = (res * binpow(den, MOD-2)) % MOD;
	assert(res >= 0);
//	cout << n << " choose " << k << " = " << res << endl;
	return res;
}

int main() {
	setIO();

	ll N, M;
	cin >> N >> M;

	if (N == 2) {
		cout << 0 << endl;
		return 0;
	}
	ll ans = 0;
	if (N == 3) {
		for (ll peak=N-1; peak<=M; peak++) {
			ll cur = 0;
			ll sets = ((peak-1) * choose(peak-2, N-3)) % MOD;

			if (sets == 0) continue;

			for (ll pos=1; pos+1<N; pos++) {
				cur += choose(sets, pos);
				cur %= MOD;
			}

			cout << peak << " " << sets << " " << cur << endl;
			ans += cur;
			ans %= MOD;
		}
	}
	else {
		for (ll peak=N-1; peak<=M; peak++) {
			ll cur = 0;
			ll sets = (choose(peak-2, N-2)) % MOD;

			for (ll pos=0; pos<N; pos++) {
				cur += (choose(sets, pos) * (N-3)) % MOD;
				cur %= MOD;
			}

			cout << peak << " " << sets << " " << cur << endl;
			ans += cur;
			ans %= MOD;
		}
	}

	cout << ans << endl;

	return 0;
}
