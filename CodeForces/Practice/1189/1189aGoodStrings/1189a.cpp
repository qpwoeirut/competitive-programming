/*
 * 1189a.cpp
 *
 *  Created on: Jul 10, 2019
 *      Author: Stanley
 */

#include <iostream>
#include <string>

using namespace std;

int main() {
	int len;
	string str;

	cin >> len >> str;

	if (len & 1) {
		cout << 1 << endl;
		cout << str << endl;
		return 0;
	}

	int count = 0;
	for (int i=0; i<len; i++) {
		count += (str[i] == '0' ? 1 : 0);
	}

	if (count * 2 != len) {
		cout << 1 << endl;
		cout << str << endl;
		return 0;
	}

	char last = str.back(); str.pop_back();
	cout << 2 << endl;
	cout << str << " " << last << endl;

	return 0;
}
