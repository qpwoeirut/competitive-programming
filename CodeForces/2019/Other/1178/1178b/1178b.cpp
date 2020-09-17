/*
 * 1178b.cpp
 *
 *  Created on: Jul 20, 2019
 *      Author: Stanley
 */

#include <iostream>
#include <vector>

using namespace std;

int main() {
	string s;
	cin >> s;

	long long ct = 0;
	vector<long long> V;
	for (int i=0; i<s.size(); i++) {
		if (s[i] == 'o') {
			V.push_back(ct);
		}
		else if (i > 0 && s[i-1] == 'v'){
			ct++;
		}
	}

	long long sum = 0;
	for (int i=0; i<V.size(); i++) {
		sum += V[i] * (ct - V[i]);
	}

	cout << sum << endl;

	return 0;
}
