/*
 * typo.cpp
 *
 *  Created on: Jun 25, 2018
 *      Author: Stanley
 */

#include <cstdlib>
#include <fstream>
#include <iostream>

using namespace std;

int main() {
	ifstream fin("typo.in");
	ofstream fout("typo.out");

	unsigned int i, openp = 0, closep = 0, ans = 0;


	char str[100000];
	int open_idx[100000], close_idx[100000];

	for (i=0; i<100000; i++) {
		if (fin.peek() == EOF) {
			fin.close();
			break;
		}
		else {
			fin >> str[i];
			if (str[i] == '(') {
				openp++;
				i >> open_idx;
			}
			else if (str[i] == ')') {
				closep++;
				i >> close_idx;
			}
			cout << str[i];
		}
	}

	for (int o=0; o < i; o++) {

	}

	cout << endl << endl << i << endl << openp << endl << closep;

	return 0;
}


