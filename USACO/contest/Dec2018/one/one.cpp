/*
 * one.cpp
 *
 *  Created on: Dec 16, 2018
 *      Author: Stanley
 */

#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
	ifstream fin("convention.in");
	ofstream fout("convention.out");

	int cow_c, bus_c, bus_sz;
	fin >> cow_c >> bus_c >> bus_sz;

	int arrivals[cow_c];
	for (int i=0; i<cow_c; i++) {
		fin >> arrivals[i];
	}
	sort(arrivals, arrivals+cow_c);

	int longest_wait = 1001001000;
	if (bus_c >= cow_c) {
		longest_wait = 0;
	}
	else {
		int diff[cow_c];
		for (int i=0; i<cow_c; i++) {
			if (i + bus_sz - 1 >= cow_c) {
				diff[i] = arrivals[cow_c - 1] - arrivals[i];
			}
			else {
				diff[i] = arrivals[i + bus_sz - 1] - arrivals[i];
			}
		}

		int extra_buses = ((bus_c * bus_sz) - cow_c) / bus_sz;
		vector<int> waits[bus_sz];
		for (int i=0; i<bus_sz; i++) {
			for (int j=i; j<cow_c; j+=bus_sz) {
				if (j < bus_sz && j > 0) {
					waits[i].push_back(arrivals[j-1] - arrivals[0]);
				}
				waits[i].push_back(diff[j]);
			}
			for (int k=0; k<extra_buses; k++) {
				waits[i].erase(max_element(waits[i].begin(), waits[i].end()));
			}
			longest_wait = min(longest_wait, *max_element(waits[i].begin(), waits[i].end()));

		}
	}

	fout << longest_wait;

	return 0;
}