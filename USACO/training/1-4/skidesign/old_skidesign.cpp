/*
ID: zhongbr1
TASK: skidesign
LANG: C++11
*/

#include <iostream>

#include <fstream>
#include <algorithm>

using namespace std;

int amain() {
	cout << "old" << endl;
	ifstream fin("skidesign.in");
	ofstream fout("skidesign.out");

	int hill_c;
	fin >> hill_c;

	int height[1000];
	int change[1000];
	for (int i=0; i<hill_c; i++) {
		fin >> height[i];
		change[i] = 0;
	}
	sort(height, height+hill_c);

	int shorten, heighten;
	int lowest, shorten_count, tallest, heighten_count;
	while (height[hill_c-1] - height[0] > 17) {
		heighten = 0;
		lowest = height[0];
		heighten_count = 0;
		for (int i=0; i<hill_c; i++) {
			if (height[i] == lowest) {
				heighten += (change[i]+1) * (change[i]+1);
				heighten_count++;
			}
			else {
				break;
			}
		}

		shorten = 0;
		tallest = height[hill_c - 1];
		shorten_count = 0;
		for (int i=hill_c-1; i >= 0; i--) {
			if (height[i] == tallest) {
				shorten += (change[i]+1) * (change[i]+1);
				shorten_count++;
			}
			else {
				break;
			}
		}

		if (shorten <= heighten) {
			for (int i=hill_c-1; shorten_count > 0; i--) {
				change[i]++;
				height[i]--;
				shorten_count--;
			}
		}
		else {
			for (int i=0; heighten_count > 0; i++) {
				change[i]++;
				height[i]++;
				heighten_count--;
			}
		}
	}

	int total_cost = 0;
	for (int i=0; i<hill_c; i++) {
		total_cost += change[i] * change[i];
	}

	fout << total_cost << endl;
	cout << total_cost << endl;

	return 0;
}
