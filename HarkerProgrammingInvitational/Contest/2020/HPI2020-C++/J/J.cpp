#include <iostream>
#include <algorithm>
#include <set>
#include <vector>

using namespace std;

void chmn(int& a, const int& b) {if (a>b) a=b;}

int main() {
	int N, K;
	cin >> N >> K;

	int dist[20][20];
	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
			dist[i][j] = 1001001001;
		}
		dist[i][i] = 0;
	}
	int u, v;
	for (int i=0; i<K; i++) {
		cin >> u >> v;
		u--; v--;

		dist[u][v] = 1;
	}


	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
			for (int k=0; k<N; k++) {

			}
		}
	}

	cout << min(N, 2) << endl;

	return 0;
}
