/*
 * angry.cpp
 *
 *  Created on: Dec 6, 2019
 *      Author: Stanley
 */

#include <fstream>

using namespace std;

int main() {
	ifstream fin("angry.in");
	ofstream fout("angry.out");

	int N;
	fin >> N;

	int a[50001];
	for (int i=0; i<N; i++) {
		fin >> a[i];
	}



	return 0;
}
