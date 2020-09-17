/*
ID: zhongbr1
TASK: money
LANG: C++11
*/

#include <fstream>
#include <iostream>

using namespace std;

typedef long long ll;

ll coins[26];
int V, N;
ll ways[26][10001];

ll dp(int idx, int cur) {
	if (cur == 0) {
		return 1;
	}
	if (idx == V) {
		return 0;
	}
	if (ways[idx][cur] != -1) {
		return ways[idx][cur];
	}

	ways[idx][cur] = dp(idx+1, cur);
	if (cur >= coins[idx]) {
		ways[idx][cur] += dp(idx, cur - coins[idx]);
	}

	return ways[idx][cur];
}

int main() {
	ifstream fin("money.in");
	ofstream fout("money.out");

	fin >> V >> N;

	for (int i=0; i<V; i++) {
		fin >> coins[i];
		for (int j=0; j<=N; j++) {
			ways[i][j] = -1;
		}
	}

	ll ans = dp(0, N);
	fout << ans << endl;
//	cout << ans << endl;

	return 0;
}
