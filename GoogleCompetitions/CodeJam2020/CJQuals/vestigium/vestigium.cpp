/*
 * vestigium.cpp
 *
 *  Created on: Apr 4, 2020
 *      Author: Stanley
 */


#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;

const int MN = 101;

void setIO() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
}

int mat[MN][MN];
int ct_row[MN][MN];
int ct_col[MN][MN];
bool row[MN], col[MN];
void solve(int tc) {
	int N;
	cin >> N;

	for (int i=0; i<N; i++) {
		row[i] = false;
		col[i] = false;
		for (int j=0; j<=N; j++) {
			ct_row[i][j] = ct_col[i][j] = 0;
		}
	}
	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
			cin >> mat[i][j];
			if (++ct_row[i][mat[i][j]] > 1) {
				row[i] = true;
			}
			if (++ct_col[j][mat[i][j]] > 1) {
				col[j] = true;
			}
		}
	}

	int trace = 0;
	int uniq_row = 0, uniq_col = 0;
	for (int i=0; i<N; i++) {
		trace += mat[i][i];
		uniq_row += row[i];
		uniq_col += col[i];
	}

	cout << "Case #" << tc << ": " << trace << " " << uniq_row << " " << uniq_col << endl;
}

int main() {
	setIO();

	int T;
	cin >> T;

	for (int i=0; i<T; i++) {
		solve(i+1);
	}
	

	return 0;
}
