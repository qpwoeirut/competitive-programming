/*
 * cardgame.cpp
 *
 *  Created on: Feb 28, 2019
 *      Author: Stanley
 */

// Got 5/15 with list and list.remove to get bessie's cards
// Got 15/15 with deque and tmp array for bessie's cards

#include <fstream>
#include <deque>
#include <queue>
#include <vector>

using namespace std;

bool elsie[100001];

int main() {
	ifstream fin("cardgame.in");
	ofstream fout("cardgame.out");

	int card_c;
	fin >> card_c;

	priority_queue<int> h1;
	priority_queue<int, vector<int>, greater<int> > h2;
	int tmp;
	for (int i=0; i<card_c/2; i++) {
		fin >> tmp;
		h1.push(tmp);
		elsie[tmp] = true;
	}
	for (int i=0; i<card_c/2; i++) {
		fin >> tmp;
		h2.push(tmp);
		elsie[tmp] = true;
	}

	deque<int> bessie;
	for (int i=1; i<=card_c*2; i++) {
		if (elsie[i] == false) {
			bessie.push_back(i);
		}
	}

	int ans = 0;
	while (h1.size() > 0) {
		if (h1.top() < bessie.back()) {
			ans++;
			bessie.pop_back();
		}
		h1.pop();
	}
	while (h2.size() > 0) {
		if (h2.top() > bessie.front()) {
			ans++;
			bessie.pop_front();
		}
		h2.pop();
	}

	fout << ans << endl;

	return 0;
}
