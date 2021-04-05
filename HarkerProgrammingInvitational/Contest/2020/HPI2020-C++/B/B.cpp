#include <iostream>

using namespace std;

int main() {
	int N, M;
	cin >> N >> M;

	int sum = 0, tmp;
	for (int i=0; i<N; i++) {
		cin >> tmp;
		sum += (M - tmp);
	}

	cout << sum << endl;

	return 0;
}
