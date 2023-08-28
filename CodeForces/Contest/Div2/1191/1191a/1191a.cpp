/*
 * 1191a.cpp
 *
 *  Created on: Jul 12, 2019
 *      Author: Stanley
 */

#include <iostream>

using namespace std;

int main() {
	int hp;
	cin >> hp;

	if (hp % 4 == 1) {
		cout << "0 A" << endl;
	}
	else if (hp % 4 == 2) {
		cout << "1 B" << endl;
	}
	else if (hp % 4 == 3) {
		cout << "2 A" << endl;
	}
	else {
		cout << "1 A" << endl;
	}

	return 0;
}
