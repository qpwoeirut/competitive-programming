/*
 * 1178c.cpp
 *
 *  Created on: Jul 20, 2019
 *      Author: Stanley
 */

#include <iostream>

using namespace std;

typedef long long LL;

const int MOD = 998244353;
int F[1001][1001];

int M, N;
LL ways(int r, int c) {
	bool p[4] = {true, true, true, true};
	//            */    o/    \*    \o
	//            /o    /*    o\    *\

}

int main() {
	cin >> M >> N;

	for (int i=0; i<N; i++) {
		for (int j=0; j<M; j++) {
			F[i][j] = 0;
		}
	}

	cout << ways(0, 0) << endl;

	return 0;
}
