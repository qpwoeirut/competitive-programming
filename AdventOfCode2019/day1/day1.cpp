/*
 * day1.cpp
 *
 *  Created on: Nov 30, 2019
 *      Author: Stanley
 */

#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

const int N = 100;
int a[100];

ll part1() {
	ll sum = 0;
	for (int i=0; i<N; i++) {
		sum += (a[i] / 3) - 2;
	}

	return sum;
}

ll part2() {
	ll sum = 0;
	for (int i=0; i<N; i++) {
		int cur = a[i];
		while (cur > 0) {
			cur = max(0, (cur/3) - 2);
			sum += cur;
		}
	}

	return sum;
}

int main() {
	ifstream fin("day1.in");
	for (int i=0; i<N; i++) {
		fin >> a[i];
	}

	cout << part1() << endl;
	cout << part2() << endl;
}
