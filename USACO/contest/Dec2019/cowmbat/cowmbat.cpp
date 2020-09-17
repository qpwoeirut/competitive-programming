/*
 * cowmbat.cpp
 *
 *  Created on: Dec 15, 2019
 *      Author: Stanley
 */


#include <fstream>
#include <algorithm>
#include <string>

using namespace std;

typedef long long ll;

const ll INIT = 1e10;
const int MAXN = 100001;

ll N, M, K;
ll cur[26][MAXN];
inline ll between(int L, int R) {
	ll ret = INIT;
	for (int i=0; i<M; i++) {
		ret = min(ret, cur[i][L] - cur[i][R]);
	}
	return ret;
}

int main() {
	ifstream fin("cowmbat.in");
	ofstream fout("cowmbat.out");

	fin >> N >> M >> K;

	string moves;
	int dist[26][26];

	fin >> moves;
	for (int i=0; i<M; i++) {
		for (int j=0; j<M; j++) {
			fin >> dist[i][j];
		}
	}
	if (K == 1) {
		fout << 0 << endl;
		return 0;
	}

	for (int i=0; i<M; i++) {
		for (int j=0; j<M; j++) {
			for (int k=0; k<M; k++) {
				if (dist[j][k] > dist[j][i] + dist[i][k]) {
					dist[j][k] = dist[j][i] + dist[i][k];
				}
			}
		}
		cur[i][N] = 0;
	}

	ll mem[MAXN];
	fill(mem, mem+N, INIT);

	for (int i=N-1; i>=0; i--) {
		for (int j=0; j<M; j++) {
			cur[j][i] = cur[j][i+1] + dist[moves[i] - 'a'][j];
		}
	}
	mem[N] = 0;
	for (int i=N; i>0; i--) {
		if (mem[i] == INIT) continue;
		for (int j=i-K; j>=K; j--) {
			mem[j] = min(mem[j], mem[i] + between(j, i));
		}
		mem[0] = min(mem[0], mem[i] + between(0, i));
	}

	ll ans = mem[0];
	fout << ans << endl;

	return 0;
}
