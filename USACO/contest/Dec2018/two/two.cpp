/*
 * two.cpp
 *
 *  Created on: Dec 16, 2018
 *      Author: Stanley
 */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>

using namespace std;

struct Cow {
	int arrival, eating, rank;
};

struct comp_time {
	const bool operator () (const Cow& a, const Cow& b) {
		return a.arrival > b.arrival;
	}
};

struct comp_rank {
	const bool operator () (const Cow& a, const Cow& b) {
		return a.rank > b.rank;
	}
};

int main() {
	ifstream fin("convention2.in");
	ofstream fout("convention2.out");

	int cow_c;
	fin >> cow_c;

	Cow cows[cow_c];
	priority_queue<Cow, vector<Cow>, comp_time> arrivals;
	for (int c=0; c<cow_c; c++) {
		fin >> cows[c].arrival >> cows[c].eating;
		cows[c].rank = c;
		arrivals.push(cows[c]);
	}

	priority_queue<Cow, vector<Cow>, comp_rank> line;
	int time = 0;
	int longest_wait = 0;
	Cow cur;
	while (arrivals.size() > 0 || line.size() > 0) {
		while (arrivals.size() > 0 && arrivals.top().arrival <= time) {
			line.push(arrivals.top());
			cout << "arrived rank, time, eat: " << arrivals.top().rank <<" " << arrivals.top().arrival << " " << arrivals.top().eating << endl;
			arrivals.pop();
		}
		if (line.size() == 0) {
			time = arrivals.top().arrival;
			continue;
		}
		cur = line.top();
		line.pop();
		longest_wait = max(longest_wait, time - cur.arrival);
		time += cur.eating;
		cout << "time, wait: " << time << " " << longest_wait << endl;
		cout << "cur rank, time, eat: " << cur.rank <<" " << cur.arrival << " " << cur.eating << endl;

	}

	fout << longest_wait;

	return 0;
}
