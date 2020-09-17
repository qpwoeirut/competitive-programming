/*
 * lemonade.cpp
 *
 *  Created on: Jul 27, 2018
 *      Author: Stanley
 *
 * Submitted 12:25am Jul 28, 2018
 * 10/10
 */

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

bool reverse_comp(int a, int b) {
	return a > b;
}

int main() {
	ifstream fin("lemonade.in");
	ofstream fout("lemonade.out");

	int cow_count;
	fin >> cow_count;

	int cows[cow_count];
	for (int c=0; c<cow_count; c++) {
		fin >> cows[c];
	}
	fin.close();

	sort(cows, cows+cow_count, reverse_comp);

	int cows_in_line = 0;
	for (int c=0; c<cow_count; c++) {
		if (cows[c] >= cows_in_line) cows_in_line++;
		else break;
	}

	fout << cows_in_line;
	fout.close();

	return 0;
}
