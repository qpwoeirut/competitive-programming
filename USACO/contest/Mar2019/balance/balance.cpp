/*
 * balance.cpp
 *
 *  Created on: Mar 31, 2019
 *      Author: Stanley
 */
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <vector>

typedef long long LL;

using namespace std;

int N;
bool A[200000];
vector<int> pos[2];
LL diff = 0;
void get_diff() {
	diff = 0;
	int t = 0;
	for (int i=0; i<N; i++) {
		if (A[i] == false) {
			diff += t;
		}
		else {
			t++;
		}
	}

	t = 0;
	for (int i=N; i<N * 2; i++) {
		if (A[i] == false) {
			diff -= t;
		}
		else {
			t++;
		}
	}
}

bool swap_one(const int& start, const int& end, const int& dir) {
	for (int i=start; i != end; i += dir) {
		if ((diff > 0 && A[i-1] == true && A[i] == false) ||
			(diff < 0 && A[i-1] == false && A[i] == true)) {
			A[i] = !A[i];
			A[i - 1] = !A[i - 1];
			cout << "swapped: " << i-1 << " " << i << endl;
			for (int i=0; i<N * 2; i++) {
				if (i == N) {
					cout << "   ";
				}
				cout << A[i] << " ";
			}
			cout << endl;
			return true;
		}
	}
	cout << "no swap s,e,d: " << start << " " << end << " " << dir << endl;
	return false;
}

int main() {
	ifstream fin("balance.in");
	ofstream fout("balance.out");

	fin >> N;

	int amt[2] = {0, 0};
	for (int i=0; i<N * 2; i++) {
		fin >> A[i];
		if (A[i]) {
			amt[i >= N]++;
		}
		pos[A[i]].push_back(i);
	}

	get_diff();

	LL side_swaps = abs(diff);
	cout << "d,ss: " << diff << " " << side_swaps << endl;
	if (side_swaps <= 1) {
		cout << side_swaps << endl;
		fout << side_swaps << endl;
		return 0;
	}

	LL swaps = 0;
	bool front = false;
	while (diff != 0) {
		if ((A[N - 1] == false && A[N] == true &&
				diff == amt[0] - (N - amt[1])) ||
			(A[N - 1] == true && A[N] == false &&
				diff == (N - amt[0]) - amt[1])) {
			swaps++;
			cout << "center swap: " << N-1 << " " << N << endl;
			break;
		}
		else {
			if (front == false && swap_one(N-1, 0, -1)) {
				swaps++;
			}
			else {
				front = true;
				swap_one(N+1, N * 2, 1);
				swaps++;
			}

			if (diff > 0) {
				diff--;
			}
			else {
				diff++;
			}
		}
	}
	cout << "sswaps,swaps: " << side_swaps << " " << swaps << endl;

	LL ans = min(swaps, side_swaps);
	cout << ans << endl;
	fout << ans << endl;

	return 0;
}
