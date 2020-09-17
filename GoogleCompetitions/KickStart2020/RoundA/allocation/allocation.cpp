/*
 * allocation.cpp
 *
 *  Created on: Mar 21, 2020
 *      Author: Stanley
 */

#include <iostream>
#include <algorithm>

using namespace std;

const int MN = 100001;

int A[MN];

int main() {
	int T;
	cin >> T;

	for (int tc=0; tc<T; tc++) {
		int N, B;
		cin >> N >> B;

		for (int i=0; i<N; i++) {
			cin >> A[i];
		}
		sort(A, A+N);

		int ans = 0;
		for (int i=0; i<N; i++) {
			if (B >= A[i]) {
				B -= A[i];
				ans++;
			}
			else {
				break;
			}
		}

		cout << "Case #" << (tc+1) << ": " << ans << endl;
	}

	return 0;
}
