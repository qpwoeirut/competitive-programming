/*
 * Edu68genTests.cpp
 *
 *  Created on: Jul 14, 2019
 *      Author: Stanley
 */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
//	ofstream fout("Edu68testCase.txt");
	int N = 25000;
//	for (int i=0; i<300; i++) {
////		cout << string(100, 'a');
//		for (int j=0; j<100; j++) {
//			cout << char((j%26) + 97);
//		}
//		cout << endl;
//	}

	cout << N << endl;
//	fout << N << endl;
	for (int i=0; i<N; i++) {
		int n = 2;
		int m = 8; //4
		cout << n << " " << m << endl;
//		fout << n << " " << m << endl;
		for (int j=0; j<n; j++) {
			cout << string(m, '.') << endl;
//			fout << string(m, '.') << endl;
		}
	}


	return 0;
}
