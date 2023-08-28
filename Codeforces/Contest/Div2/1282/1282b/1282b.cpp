/*
 * 1282b.cpp
 *
 *  Created on: Dec 24, 2019
 *      Author: Stanley
 */


#include <iostream>
#include <algorithm>
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
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

#define MP make_pair

#define PF push_front
#define PB push_back
#define I insert

#define F first
#define S second
#define B begin
#define E end

#define LB lower_bound
#define UB upper_bound

#define PRS(A, N) for (int i=0; i<N; i++) cout << A[i] << " ";
#define PRL(A, N) for (int i=0; i<N; i++) cout << A[i] << endl;
#define PISET(A) for (set<int>::iterator it=A.B(); it!=A.E(); it++) cout << *it << " ";
#define PSSET(A) for (set<string>::iterator it=A.B(); it!=A.E(); it++) cout << *it << " ";

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,bool> pib;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

typedef map<int,int> mii;
typedef map<ll,ll> mll;
typedef map<char, int> mci;
typedef map<string,int> msi;

ll gcd(ll a, ll b) {return b ? gcd(b, a%b) : a;}

const ll MOD = 1e9+7; // 998244353;
const ll INF = 1e18;
const int MAXN = 200002;
const int INIT = 2001001001;

int goods[MAXN];
ll price[MAXN];
void solve() {
	ll N, P, K;
	cin >> N >> P >> K;

	for (int i=0; i<N; i++) {
		cin >> goods[i];
		price[i] = INIT;
	}
	sort(goods, goods+N);
//	PRS(goods, N); cout << endl;
//	PRS(price, N+1); cout << endl;

	int best = 0;
	price[0] = 0;
	price[N] = INIT;
	for (int i=0; i+1<=N; i++) {
		if (i+K <= N) price[i+K] = min(price[i+K], price[i] + goods[i+K-1]);
		price[i+1] = min(price[i+1], price[i] + goods[i]);
		if (price[i] <= P) {
			best = i;
		}
	}
//	PRS(price, N+1); cout << endl;
	if (price[N] <= P) best = N;

	cout << best << endl;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int T;
	cin >> T;
	while (T > 0) {
		T--;
		solve();
	}

	return 0;
}
