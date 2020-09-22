/*
 * piepie.cpp
 *
 *  Created on: Jun 12, 2019
 *      Author: Stanley
 */

#include <fstream>

using namespace std;

int main() {
	ifstream fin("piepie.in");
	ofstream fout("piepie.out");

	int N, D;
	fin >> N >> D;

	pair<int, int> pies[200000];
	for (int i=0; i<2*N; i++) {
		fin >> pies[i].first >> pies[i].second;
	}



	return 0;
}
