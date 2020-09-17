/*
ID: zhongbr1
TASK: nocows
LANG: C++11
*/

#include <iostream>
#include <fstream>

using namespace std;

const int MOD = 9901;

int ways[201][101];
int dp(int nodes, int levels) {
	if (nodes <= 0 || levels <= 0) {
//		cout << nodes << " " << levels << " " << 0 << endl;
		return 0;
	}
	if (ways[nodes][levels] != -1) {
//		cout << nodes << " " << levels << " " << ways[nodes][levels] << endl;
		return ways[nodes][levels];
	}

	ways[nodes][levels] = 0;
	for (int i=1; i<=nodes-2; i+=2) {
		ways[nodes][levels] += dp(i, levels-1) * dp(nodes-i-1, levels-1);
		ways[nodes][levels] %= MOD;
	}
	cout << nodes << " " << levels << " " << ways[nodes][levels] << endl;
	return ways[nodes][levels];
}

int main() {
	ifstream fin("nocows.in");
	ofstream fout("nocows.out");

	int N, K;
	fin >> N >> K;

	for (int i=0; i<=N; i++) {
		for (int j=0; j<=K; j++) {
			ways[i][j] = (i == 1 ? 1 : -1);
		}
	}
	int ans = (dp(N, K) - dp(N, K-1) + MOD) % MOD;
	fout << ans << endl;
	cout << ans << endl;

	return 0;
}
