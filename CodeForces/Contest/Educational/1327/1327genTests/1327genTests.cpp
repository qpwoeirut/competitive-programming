/*
 * 1327genTests.cpp
 *
 *  Created on: Mar 23, 2020
 *      Author: Stanley
 */


#include <iostream>
#include <fstream>

using namespace std;

const int MT = 100000;
const int MN = 100000;

void setIO() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
}

int main() {
	setIO();
	
//	ofstream fout("1327B1.txt");

	int T = 1;
	int N = MN;
	cout << T << endl;
	for (int i=0; i<T; i++) {
		cout << N << endl;
		for (int j=0; j<N; j++) {
//			if (j+1 == N) {
//				cout << N;
//				for (int k=1; k<=N; k++) cout << " " << k;
//				cout << endl;
//				continue;
//			}
			cout << "1 1" << endl;
		}
	}

	return 0;
}
