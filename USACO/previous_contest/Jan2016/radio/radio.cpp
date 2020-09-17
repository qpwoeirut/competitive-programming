/*
 * radio.cpp
 *
 *  Created on: Dec 6, 2019
 *      Author: Stanley
 */

#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

ll mem[1002][1002];
ll dist[1002][1002];

int N, M;
int fj[1001], bs[1001];
ll dp(int f, int b) {
	if (mem[f][b] != -1) {
		return mem[f][b];
	}
	if (f == N && b == M) {
		return dist[f][b];
	}
	else if (f == N) {
		mem[f][b] = dist[f][b] + dp(f, b+1);
		return mem[f][b];
	}
	else if (b == M) {
		mem[f][b] = dist[f][b] + dp(f+1, b);
		return mem[f][b];
	}

	mem[f][b] = dist[f][b] + min(dp(f+1, b+1), min(dp(f+1, b), dp(f, b+1)));
	return mem[f][b];
}


int main() {
	ifstream fin("radio.in");
	ofstream fout("radio.out");

	fin >> N >> M;

	int fc, fr;
	fin >> fc >> fr;

	int bc, br;
	fin >> bc >> br;

	char tmp;
	for (int i=0; i<N; i++) {
		fin >> tmp;
		if (tmp == 'N') {
			fj[i] = 0;
		}
		else if (tmp == 'E') {
			fj[i] = 1;
		}
		else if (tmp == 'S') {
			fj[i] = 2;
		}
		else {
			fj[i] = 3;
		}
	}
	for (int i=0; i<M; i++) {
		fin >> tmp;
		if (tmp == 'N') {
			bs[i] = 0;
		}
		else if (tmp == 'E') {
			bs[i] = 1;
		}
		else if (tmp == 'S') {
			bs[i] = 2;
		}
		else {
			bs[i] = 3;
		}
	}

	int chr[4] = {1, 0, -1, 0};
	int chc[4] = {0, 1, 0, -1};

	int sfc = fc, sfr = fr;
	for (int i=0; i<=N; i++) {
		int sbc = bc, sbr = br;
		for (int j=0; j<=M; j++) {
			dist[i][j] = ((sbc - sfc) * (sbc - sfc)) + ((sbr - sfr) * (sbr - sfr));
			sbr += chr[bs[j]];
			sbc += chc[bs[j]];
		}
		sfr += chr[fj[i]];
		sfc += chc[fj[i]];
	}

	for (int i=0; i<=N; i++) {
		for (int j=0; j<=M; j++) {
			mem[i][j] = -1;
		}
	}

	ll ans = min(dp(1, 1), min(dp(0, 1), dp(1, 0)));
	fout << ans << endl;

	return 0;
}
