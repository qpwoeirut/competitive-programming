/*
 * pairup.cpp
 *
 *  Created on: Jan 19, 2019
 *      Author: Stanley
 */

#include <iostream>

#include <fstream>
#include <algorithm>
#include <list>

using namespace std;

bool comp_cows(const pair<int, int>& a, const pair<int, int>& b) {
	return a.second < b.second;
}

int main() {
	ifstream fin("pairup.in");
	ofstream fout("pairup.out");

	int line_c, cow_c = 0;
	fin >> line_c;

	list<pair<int, int> > cows;
	pair<int, int> tmp;
	for (int l=0; l<line_c; l++) {
		fin >> tmp.first >> tmp.second;
		cow_c += tmp.first;
		cows.push_back(tmp);
	}
	fin.close();

	cows.sort(comp_cows);

	int longest = 0;
	pair<int, int> cur_small = make_pair(0, 0), cur_large = make_pair(0, 0);
	while (cows.size() > 1) {
		if (cur_small.first == 0) {
			cur_small = cows.front();
			cows.pop_front();
		}
		if (cur_large.first == 0) {
			cur_large = cows.back();
			cows.pop_back();
		}

		if (cur_small.first >= cur_large.first) {
			cur_small.first -= cur_large.first;
			cur_large.first = 0;
		}
		else {
			cur_large.first -= cur_small.first;
			cur_small.first = 0;
		}

		longest = max(longest, cur_small.second + cur_large.second);
	}

	if (cur_small.first > 0) {
		longest = max(longest, cur_small.second + cur_small.second);
	}
	else if (cur_large.first > 0) {
		longest = max(longest, cur_large.second + cur_large.second);
	}

	if (cows.size() == 1) {
		cur_small = cows.front();
		cows.pop_front();
		longest = max(longest, cur_small.second + cur_small.second);
	}

	fout << longest << endl;
	fout.close();

	return 0;
}
