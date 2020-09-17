#include <iostream>
#include <algorithm>

using namespace std;

int T;
int N, M, X, Y;
int main() {
	cin >> T;

	while (T-- > 0) {
		cin >> N >> M >> X >> Y;	

		if (X + X <= Y) {
			cout << N * M * X << endl;
		} else if (N == 1 && M == 1) {
			cout << X << endl;
		} else {
			X = min(X, Y);
			int Z = min(X, Y-X);
			cout << (((N * M) + 1) / 2) * X + ((N * M) / 2 * Z) << endl;
		}
	}
	return 0;
}
