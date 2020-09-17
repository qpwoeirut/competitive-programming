/*
 * MINOPS.cpp
 *
 *  Created on: Apr 20, 2020
 *      Author: Stanley
 */


#include <iostream>
#include <algorithm>
#include <cassert>
#include <queue>
#include <string>

using namespace std;

typedef long long ll;

const ll MOD = 1e9+7; // 998244353;
const int INIT = 1001001001;
const int MN = 1000001;

void setIO() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
}

string S, R;
void solve() {
	cin >> S;
	cin >> R;
	ll N = S.size();
	assert(N == S.size());
	assert(N == R.size());

	ll moves = 0;
	ll reps = 0;
	assert(moves == 0);
	assert(reps == 0);
	for (ll i=0; i<N; i++) {
		if (S[i] != R[i]) {
			reps++;
			if (i==0 || S[i-1] == R[i-1]) {
				moves++;
			}
		}
	}
	assert(0 <= moves);
	assert(moves <= reps);
	assert(0 <= reps);
	assert(reps <= N);
	assert(N < MN);
	if (reps == 0) assert(moves == 0);
//	debug(moves);
//	debug(reps);

	priority_queue<ll, vector<ll>, greater<ll> > pq;
	assert(pq.empty());
	ll start = -1;
	assert(start == -1);
	for (ll i=0; i<N; i++) {
		if (S[i] == R[i] && (i==0 || S[i-1] != R[i-1])) {
			start = i;
		}
		else if (S[i] != R[i] && start != -1) {
			if (start != 0) {
				pq.push(i - start);
			}
			start = -1;
		}
	}
	assert(pq.size() <= (N/2) + 1);

	ll cur = moves * reps;
	assert(cur >= 0);
	while (pq.size() > 0) {
		ll gap = pq.top();
		pq.pop();
		assert(0 < gap);
		assert(gap < N);
		if (pq.size() > 0) assert(gap <= pq.top());
//		debug(gap);

		if (cur >= (moves-1) * (reps+gap)) {
			moves--;
			reps += gap;
			cur = moves * reps;

			assert(moves > 0);
			assert(reps <= N);
			assert(moves <= reps);
			assert(cur > 0);
		}
		else {
			break;
		}
	}

//	debug(moves);
//	debug(reps);
	assert(cur >= 0);
	cout << cur << endl;
}

int main() {
	setIO();

	int T;
	cin >> T;

	while (T>0) {
		T--;
		solve();
	}

	return 0;
}
