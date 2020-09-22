/*
 * hps.cpp
 *
 *  Created on: Nov 22, 2019
 *      Author: Stanley
 */

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int main() {
	ifstream fin("hps.in");
	ofstream fout("hps.out");

	int N, K;
	fin >> N >> K;

	int a[100001];
	char tmp;
	for (int i=0; i<N; i++) {
		fin >> tmp;
		if (tmp == 'H') {
			a[i] = 0;
		}
		else if (tmp == 'P') {
			a[i] = 1;
		}
		else {
			a[i] = 2;
		}
	}

	int dp[2][21][3];
	for (int i=0; i<=N; i++) {
		for (int j=0; j<=K; j++) {
			for (int k=0; k<3; k++) {
				if (i == 0) {
					dp[i%2][j][k] = 0;
				}
				else if (j == 0) {
					dp[i%2][j][k] = dp[(i+1)%2][j][k];
				}
				else {
					dp[i%2][j][k] = max(dp[(i+1)%2][j][k],
								  max(dp[(i+1)%2][j-1][(k+1)%3], dp[(i+1)%2][j-1][(k+2)%3]));
				}

				if (i < N && k == a[i]) {
					dp[i%2][j][k]++;
				}

//				cout << dp[i%2][j][k] << " ";
			}
//			cout << "     ";
		}
//		cout << endl;
	}

	int ans = 0;
	for (int j=0; j<=K; j++) {
		for (int k=0; k<3; k++) {
			ans = max(ans, dp[N%2][j][k]);
//			cout << dp[i][N%2][k] << endl;
		}
	}

//	cout << ans << endl;
	fout << ans << endl;

	return 0;
}
