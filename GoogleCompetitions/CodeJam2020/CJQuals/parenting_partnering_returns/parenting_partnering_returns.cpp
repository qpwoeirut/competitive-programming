/*
 * parenting_partnering_returns.cpp
 *
 *  Created on: Apr 4, 2020
 *      Author: Stanley
 */


#include <iostream>
#include <algorithm>
#include <cassert>
#include <string>

using namespace std;

typedef long long ll;

const int MN = 1001;

struct Activity {
	int start, end;
	int idx;
};
inline const bool cmp_start(const Activity& a, const Activity& b) {
	return a.start < b.start;
}

Activity activities[MN];
void solve(int tc) {
	int N;
	cin >> N;

	for (int i=0; i<N; i++) {
		cin >> activities[i].start >> activities[i].end;
		activities[i].idx = i;
	}
	sort(activities, activities+N, cmp_start);

	string ans(N, '*');
	int cameron = -1, jamie = -1;
	for (int i=0; i<N; i++) {
		if (cameron <= activities[i].start) {
			cameron = activities[i].end;
			ans[activities[i].idx] = 'C';
		}
		else if (jamie <= activities[i].start) {
			jamie = activities[i].end;
			ans[activities[i].idx] = 'J';
		}
		else {
			ans = "IMPOSSIBLE";
			break;
		}
	}

	cout << "Case #" << tc << ": " << ans << endl;
}

int main() {
	int T;
	cin >> T;

	for (int i=1; i<=T; i++) {
		solve(i);
	}

	return 0;
}
