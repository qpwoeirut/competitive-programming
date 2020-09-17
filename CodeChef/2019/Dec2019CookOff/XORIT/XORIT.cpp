/*
 * XORIT.cpp
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

ll xpr(ll N) {
	ll cur = N;
	ll sub = 1;
	while (cur > 0 && N > sub) {
		if (cur & 1) {
//			cout << N << ": " << sub << endl;
			return N - sub;
		}
		cur >>= 1;
		sub <<= 1;
	}

//	cout << N << " :" << -1 << endl;
	return -1;
}

ll brute(ll L, ll R) {

	ll ans = 0;
	for (ll i=L; i<=R; i++) {
		ans += xpr(i);
	}

	return ans;
}

void solve() {
	ll L, R;
	cin >> L >> R;
//	ll brans = brute(L, R);
//	cout << "brute: " << brans << endl;

	int ct[33];
	fill(ct, ct+33,0);

	ll ans = ((R-L+1) * (R+L)) / 2;
	for (int t=0; (1<<t)<=R; t++) {
		ll cur = 1 << t;
		ct[t] = (R / cur) - (L / cur);
		if (L % cur == 0) ct[t]++;
	}

	for (int i=32; i>=0; i--) {
		for (int j=0; j<i; j++) {
			ct[j] -= ct[i];
		}
	}

//	cout << "orig ans: " << ans <<endl;
	for (ll i=0; i<=30; i++) {
//		cout << "i,ct,pow: " << i << " " << ct[i] << " " << (1 << i) << endl;
		if ((L <= (1 << i)) && ((1 << i) <= R)) {
			ans -= (1 << i) + 1;
			ct[i]--;
		}
		ans -= ct[i] * (1 << (i));
	}

	cout << ans << endl;
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
