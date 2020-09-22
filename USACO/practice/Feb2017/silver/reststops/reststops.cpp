/*
 * reststops.cpp
 *
 *  Created on: Sep 2, 2018
 *      Author: Stanley
 *
 * 1/10 due to int overflow
 * 3/10 after downloading test cases
 *
 * The idea was correct, but the implementation was not.
 *
 */

#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Stop {
	int pos; // One-indexed
	int taste_pts;
};

bool comp_taste(Stop a, Stop b) {
	return a.taste_pts < b.taste_pts;
}

bool comp_pos(Stop a, Stop b) {
	return a.pos < b.pos;
}

int main() {
	ifstream fin("reststops.in");
	ofstream fout("reststops.out");

	int len, stop_num;
	int fj_rate, bes_rate;

	fin >> len >> stop_num >> fj_rate >> bes_rate;

	vector<Stop> stops_left;

	int temp_pos, temp_taste;
	cout << stop_num << endl;
	for (int s=0; s<stop_num; s++) {
		fin >> temp_pos >> temp_taste;
		Stop temp_stop;
		temp_stop.pos = temp_pos;
		temp_stop.taste_pts = temp_taste;
		stops_left.push_back(temp_stop);
	}

	unsigned long long taste_units = 0;
	int last_stop_pos = 0, cur_stop_pos;
	unsigned long long fj_time, bes_time;
	long long time_diff;
	int pos_diff;

	while (stops_left.size() > 0) {
		vector<Stop>::iterator best_stop_iter = max_element(stops_left.begin(), stops_left.end(), comp_taste);
		// max_element gives first item if multiple are tied
		cur_stop_pos = best_stop_iter->pos;

		pos_diff = cur_stop_pos - last_stop_pos;
		fj_time = pos_diff * fj_rate;
		bes_time = pos_diff * bes_rate;
		time_diff = fj_time - bes_time;
		taste_units += (best_stop_iter->taste_pts * time_diff);
		cout << "fj, bes time: " << fj_time << " " << bes_time << endl;
		cout << "stop pos, taste: " << best_stop_iter->pos << " " << best_stop_iter->taste_pts << endl;
		cout << "pos, time diff: " << pos_diff << " " << time_diff << endl;
		cout << "taste: " << taste_units << endl;

		last_stop_pos = cur_stop_pos;

		stops_left.erase(stops_left.begin(), best_stop_iter+1);
	}

	fout << taste_units;
	cout << "ans: " << taste_units;

	return 0;
}

