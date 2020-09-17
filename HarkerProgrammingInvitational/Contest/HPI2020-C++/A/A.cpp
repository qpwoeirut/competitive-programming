#include <iostream>

using namespace std;

int main() {
	int N;
	cin >> N;

	int sum = 0, tmp;
	for (int i=0; i<N; i++) {
		cin >> tmp;
		sum += tmp;
	}

	cout << sum << endl;

	return 0;
}
