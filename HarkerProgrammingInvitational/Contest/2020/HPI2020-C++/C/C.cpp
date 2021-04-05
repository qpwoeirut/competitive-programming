#include <iostream>
#include <algorithm>

using namespace std;

int main() {
	int N;
	cin >> N;

	int a[1001];
	for (int i=0; i<N; i++) {
		cin >> a[i];
	}

	sort(a, a+N);
	for (int i=0; i<N; i++) {
		if (a[i] < i) {
			cout << "COLLAPSE" << endl;
			return 0;
		}
	}

	cout << "NO COLLAPSE" << endl;

	return 0;
}
