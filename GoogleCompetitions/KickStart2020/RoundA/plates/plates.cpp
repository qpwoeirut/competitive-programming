/*
 * plates.cpp
 *
 *  Created on: Mar 21, 2020
 *      Author: Stanley
 */


#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;

void chmx(int& a, const int& b) {if (a<b) a=b;}

const int MN = 51;
const int MK = 31;
const int MP = MN * MK;
const int INIT = -(MP * 101);

void setIO() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
}

int N, K, P;
int plates[MN][MK];
int mem[MN][MP];
int dp(int idx, int used) {
	if (idx == N) {
		if (used == P) {
			return 0;
		}
		return INIT;
	}
	if (used > P) {
		return INIT;
	}
	if (mem[idx][used] != INIT) {
		return mem[idx][used];
	}

	mem[idx][used] = dp(idx+1, used);
	int sum = 0;
	for (int i=0; i<K; i++) {
		sum += plates[idx][i];
		chmx(mem[idx][used], sum + dp(idx+1, used+i+1));
	}

//	cout << idx << " " << used << " " << mem[idx][used] << endl;
	return mem[idx][used];
}

int main() {
	setIO();

	int T;
	cin >> T;

	for (int tc=1; tc<=T; tc++) {
		cin >> N >> K >> P;

		for (int i=0; i<N; i++) {
			for (int j=0; j<=P; j++) {
				mem[i][j] = INIT;
			}
			for (int j=0; j<K; j++) {
				cin >> plates[i][j];
			}
		}

		cout << "Case #" << tc << ": " << dp(0, 0) << endl;
	}

	return 0;
}
