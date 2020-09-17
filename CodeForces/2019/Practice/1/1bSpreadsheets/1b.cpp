/*
 * 1b.cpp
 *
 *  Created on: May 25, 2019
 *      Author: Stanley
 */

#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>

using namespace std;

string to_letters(string num) {
	int n = atoi(num.c_str());
	string str;
	while (n > 0) {
		str.push_back(((n - 1) % 26) + 'A');
		n = (n-1) / 26;
	}

	reverse(str.begin(), str.end());
	return str;
}

int from_letters(string str) {
	int m = 1;
	char c;
	int num = 0;
	while (str.size() > 0) {
		c = str.back();
		str.pop_back();

		num += (c - 'A' + 1) * m;
		m *= 26;
	}

	return num;
}

int main() {
	int N;
	cin >> N;

	string coord;
	int end1, end2;
	string row, col;
	for (int i=0; i<N; i++) {
		cin >> coord;
		end1 = -1;
		end2 = -1;
		for (int j=1; j<coord.size(); j++) {
			if (isalpha(coord[j-1]) && isdigit(coord[j])) {
				if (end1 == -1) {
					end1 = j;
				}
				else {
					end2 = j;
					col = coord.substr(end1, end2 - end1 - 1);
					row = coord.substr(end2);

					cout << to_letters(row) << col << endl;
					break;
				}
			}
		}

		if (end2 == -1) {
			col = coord.substr(0, end1);
			row = coord.substr(end1);
			cout << 'R' << row << 'C' << from_letters(col) << endl;
		}
	}

	return 0;
}

