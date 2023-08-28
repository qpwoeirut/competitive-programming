/*
 * 1199c.cpp
 *
 *  Created on: Jul 30, 2019
 *      Author: Stanley
 */

#include <iostream>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

typedef long long LL;

int main() {
	int p2[31];
	p2[0] = 1;
	for (int i=1; i<31; i++) {
		p2[i] = p2[i-1] + p2[i-1];
	}

	int N, I;
	cin >> N >> I;

	map<int, int> ct;
	int tmp;
	for (int i=0; i<N; i++) {
		cin >> tmp;
		ct[tmp]++;
	}

	int sz = (I * 8) / N;

	vector<int> sum;
	sum.push_back(0);
	for (map<int,int>::iterator it=ct.begin(); it!=ct.end(); it++) {
		sum.push_back(sum.back() + it->second);
	}
	int L = p2[min(sz, 20)];
	if (L >= ct.size()) {
		cout << 0 << endl;
		return 0;
	}

	int best = 0;
	for (int i=0; i+L<sum.size(); i++) {
		best = max(best, sum[i+L] - sum[i]);
	}

	cout << sum.back() - best << endl;

	return 0;
}
