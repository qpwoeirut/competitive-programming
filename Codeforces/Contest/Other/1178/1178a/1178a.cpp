/*
 * 1178a.cpp
 *
 *  Created on: Jul 20, 2019
 *      Author: Stanley
 */

#include <iostream>
#include <vector>

using namespace std;

int main() {
	int N;
	cin >> N;

	int alice;
	cin >> alice;

	int sum = alice, a = alice;
	int tmp;
	vector<int> part;
	part.push_back(1);
	for (int i=1; i<N; i++) {
		cin >> tmp;
		if (alice >= tmp*2) {
			a += tmp;
			part.push_back(i+1);
		}

		sum += tmp;
	}

	if (sum >= a*2) {
		cout << 0 << endl;
	}
	else {
		cout << part.size() << endl;
		for (int i=0; i+1<part.size(); i++) {
			cout << part[i] << " ";
		}
		cout << part.back() << endl;
	}

	return 0;
}
