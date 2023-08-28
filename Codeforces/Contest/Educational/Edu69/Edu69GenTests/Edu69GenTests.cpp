/*
 * Edu68GenTests.cpp
 *
 *  Created on: Jul 22, 2019
 *      Author: Stanley
 */

#include <iostream>
#include <fstream>

using namespace std;

int main() {
	ofstream fout("Edu69Tests.txt");
	int N = 30000;
	cout << N << " " << N-1 << endl;
	fout << N << " " << N-1 << endl;

	for (int i=1; i<=N; i++) {
		cout << i << " ";
		fout << i << " ";
	}

	return 0;
}
