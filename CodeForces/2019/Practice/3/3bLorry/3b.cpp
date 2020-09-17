/*
 * 3b.cpp
 *
 *  Created on: May 27, 2019
 *      Author: Stanley
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

typedef pair<int, int> pii;

bool comp_first(const pii& a, const pii& b) {
	return a.first < b.first;
}

int main() {
	int N, V;
	cin >> N >> V;

	vector<pii> k, c;
	int tmp_t, tmp_sz;
	for (int i=0; i<N; i++) {
		cin >> tmp_t >> tmp_sz;
		if (tmp_t == 1) {
			k.push_back(make_pair(tmp_sz, i+1));
		}
		else {
			c.push_back(make_pair(tmp_sz, i+1));
		}
	}
	sort(k.begin(), k.end(), comp_first);
	sort(c.begin(), c.end(), comp_first);

	int cap = 0;
	set<int> taken;
	if ((V & 1) && !k.empty()) {
		cap += k.back().first;
		taken.insert(k.back().second);
		k.pop_back();
		V--;
	}


	while (V > 1 && (!k.empty() || !c.empty())) {
		pii ksz1 = make_pair(0, 0), ksz2 = make_pair(0, 0), csz = make_pair(0, 0);
		if (!k.empty()) {
			ksz1 = k.back();
			if (k.size() > 1) {
				ksz2 = k[k.size() - 2];
			}
		}
		if (!c.empty()) {
			csz = c.back();
		}

		if (ksz1.first + ksz2.first > csz.first) {
			cap += ksz1.first + ksz2.first;
			taken.insert(ksz1.second);
			k.pop_back();
			V--;
			if (ksz2.second > 0) {
				taken.insert(ksz2.second);
				k.pop_back();
				V--;
			}
		}
		else {
			cap += csz.first;
			taken.insert(csz.second);
			c.pop_back();
			V -= 2;
		}
	}

	cout << cap << endl;
	for (set<int>::iterator it=taken.begin(); it!=taken.end(); it++) {
		cout << *it << endl;
	}

	return 0;
}
