/*
 * bphoto.cpp
 *
 *  Created on: Nov 22, 2019
 *      Author: Stanley
 */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
	ifstream fin("bphoto.in");
	ofstream fout("bphoto.out");
	int N;
	fin >> N;

	int a[100001];
	for (int i=0; i<N; i++) {
		fin >> a[i];
	}

	vector<int> prev;
	int left[100001], right[100001];
	for (int i=0; i<N; i++) {
		vector<int>::iterator it=lower_bound(prev.begin(), prev.end(), a[i]);
		left[i] = prev.end() - it;
		prev.insert(it, a[i]);
	}

	prev.clear();
	for (int i=N-1; i>=0; i--) {
		vector<int>::iterator it=lower_bound(prev.begin(), prev.end(), a[i]);
		right[i] = prev.end() - it;
		prev.insert(it, a[i]);
	}

	int ans = 0;
	for (int i=0; i<N; i++) {
//		cout << a[i] << ": " << left[i] << " " << right[i] << endl;
		if (min(left[i], right[i]) * 2 < max(left[i], right[i])) {
			ans++;
		}
	}

//	cout << ans << endl;
	fout << ans << endl;
	fout.close();

	return 0;
}
