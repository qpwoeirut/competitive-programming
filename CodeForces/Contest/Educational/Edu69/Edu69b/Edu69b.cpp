/*
 * Edu69b.cpp
 *
 *  Created on: Jul 22, 2019
 *      Author: Stanley
 */

#include <iostream>
#include <queue>

using namespace std;

typedef long long LL;

int main() {
	int N;
	cin >> N;

	int pillars[200001];
	int mi = -1;
	int mv = -1;
	for (int i=0; i<N; i++) {
		cin >> pillars[i];
		if (mv < pillars[i]) {
			mv = pillars[i];
			mi = i;
		}
	}

	queue<int> left, right;
	for (int i=mi-1; i>=0; i--) {
		left.push(pillars[i]);
	}

	for (int i=mi+1; i<N; i++) {
		right.push(pillars[i]);
	}

	bool ans = true;
	int cur = mv;
	while (cur > 1) {
		if (left.size() > 0 && left.front() == cur-1) {
			left.pop();
			cur--;
		}
		else if (right.size() > 0 && right.front() == cur-1) {
			right.pop();
			cur--;
		}
		else {
			ans = false;
			break;
		}
	}

	cout << (ans ? "YES" : "NO") << endl;

	return 0;
}
