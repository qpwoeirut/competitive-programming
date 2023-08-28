/*
 * 3a.cpp
 *
 *  Created on: May 27, 2019
 *      Author: Stanley
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
	pair<char, int> cur, end;
	cin >> cur.first >> cur.second >> end.first >> end.second;

	vector<string> moves;
	while (cur != end) {
		moves.push_back("");
		if (cur.first < end.first) {
			moves.back().push_back('R');
			cur.first++;
		}
		else if (cur.first > end.first) {
			moves.back().push_back('L');
			cur.first--;
		}

		if (cur.second < end.second) {
			moves.back().push_back('U');
			cur.second++;
		}
		else if (cur.second > end.second) {
			moves.back().push_back('D');
			cur.second--;
		}
	}

	cout << moves.size() << endl;
	for (int i=0; i<moves.size(); i++) {
		cout << moves[i] << endl;
	}

	return 0;
}
