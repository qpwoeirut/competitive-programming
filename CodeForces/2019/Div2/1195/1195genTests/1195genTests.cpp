/*
 * 1195getTests.cpp
 *
 *  Created on: Jul 17, 2019
 *      Author: Stanley
 */

#include <fstream>

using namespace std;

int main() {
	int N = 20000;
	ofstream fout("1195tests");
	fout << N << endl;
	for (int i=0; i<N; i++) {
		fout << 1000000000 << " ";
	}


	return 0;
}

