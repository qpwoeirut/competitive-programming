/*
 * CRSHIT.cpp
 *
 *  Created on: Dec 22, 2019
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
#include <iterator>

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
const int MAXN = 100001;

ll N, Q, K;
vector<ll> d1, d2;
ll bound;
inline bool comp_no_add(ll pos_a, ll pos_b) {
	if (pos_a > pos_b) {
		return true;
	}
	return ((pos_b - pos_a + 1) / 2) < bound;
}
inline bool comp_add(ll pos_a, ll pos_b) {
	if (pos_a < pos_b) {
		return false;
	}
	pos_b += K;
	return ((pos_b - pos_a + 1) / 2) >= bound;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> N >> Q >> K;

	d1 = vector<ll>();
	d2 = vector<ll>();
	pii tmp;
	for (int i=0; i<N; i++) {
		cin >> tmp.F >> tmp.S;
		if (tmp.F == 1) {
			d1.push_back(tmp.S);
		}
		else {
			d2.push_back(tmp.S);
		}
	}

	ll cycle = d1.size() * d2.size();
	sort(d1.begin(), d1.end());
	sort(d2.begin(), d2.end());
//	PRS(d1, d1.size()); cout << endl;
//	PRS(d2, d2.size()); cout << endl;

	ll T;
	for (int i=0; i<Q; i++) {
		cin >> T;

		ll ans = cycle * (T / K);
		bound = T % K;
		cout << "cycle ans,b: " << ans << " " << bound << endl;

		for (int i=0; i<d1.size(); i++) {
			vector<ll>::iterator add=UB(d2.begin(), d2.end(), d1[i], comp_add);
			vector<ll>::iterator no_add=UB(d2.begin(), d2.end(), d1[i], comp_no_add);
			if (add != d2.end()) {
				ans += (add - d2.begin());
			}
			cout << "i,A: " << i << " " << ans << endl;

			if (no_add != d2.end()) {
				ans += (d2.end() - no_add);
				cout << (no_add - d2.begin()) << endl;
			}
			cout << "i,a: " << i << " " << ans << endl;
		}

		cout << ans << endl;
	}

	return 0;
}
