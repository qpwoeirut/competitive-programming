/*
 * 1191c.cpp
 *
 *  Created on: Jul 12, 2019
 *      Author: Stanley
 */

#include <iostream>
#include <queue>

using namespace std;

typedef long long LL;

int main() {
	LL N, del, size;
	cin >> N >> del >> size;

	queue<LL> special;
	LL tmp;
	for (int i=0; i<del; i++) {
		cin >> tmp;
		special.push(tmp-1);
	}
	if (size == 1) {
		cout << del << endl;
		return 0;
	}
	cout << "start" <<endl;

	LL ops = 0;
	LL cur = 0, end = size;
	while (special.size() > 0) {
		ops++;

		if (special.size() > 0 && special.front() >= end) {
			end += size * (1 + ((special.front() - end) / size));
		}

		cur = end;
		while (special.size() > 0 && special.front() < end) {
			special.pop();
			cur++;
		}
		end = cur;
	}

	cout << ops << endl;

	return 0;
}
