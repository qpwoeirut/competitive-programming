/*
ID: zhongbr1
TASK: skidesign
LANG: C++11
*/

#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
	ifstream fin("skidesign.in");
	ofstream fout("skidesign.out");
	int hill_c;
	fin >> hill_c;

	int height[1000], change[1000];
	for (int i=0; i<hill_c; i++) {
		fin >> height[i];
		change[i] = 0;
	}
	sort(height, height+hill_c);

	int lowest, highest;
	int total_cost = 0;
	int heighten_cost, shorten_cost, already_spent;
	int increase_count = 0, decrease_count = 0;
	while ((height[hill_c-1] - height[0]) > 17) {
		heighten_cost = 0;
		shorten_cost = 0;
		increase_count = 0;
		decrease_count = 0;
		lowest = height[0];
		highest = height[hill_c - 1];

		for (int i=0; i<hill_c; i++) {
			if (height[i] == lowest) {
				already_spent = change[i] * change[i];
				heighten_cost += ((change[i] + 1) * (change[i] + 1)) - already_spent;
				increase_count++;
			}
			else {
				break;
			}

		}

		for (int i=hill_c-1; i>=0; i--) {
			if (height[i] == highest) {
				already_spent = change[i] * change[i];
				shorten_cost += ((change[i] + 1) * (change[i] + 1)) - already_spent;
				decrease_count++;
			}
			else {
				break;
			}

		}

		if (heighten_cost <= shorten_cost) {
			for (int i=0; increase_count > 0; i++) {
				height[i]++;
				change[i]++;
				increase_count--;
			}
			total_cost += heighten_cost;
		}
		else {
			for (int i=hill_c - 1; decrease_count > 0; i--) {
				height[i]--;
				change[i]++;
				decrease_count--;
			}
			total_cost += shorten_cost;
		}
	}

	fout << total_cost << endl;
	cout << total_cost << endl;

	return 0;
}

