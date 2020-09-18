#include "tickets.h"
#include <bits/stdc++.h>
using namespace std;

vector<int> values;
vector<int> ones[1505], zeros[1505];
int sums[1505];
vector< pair<int, int> > zeroPlace, onePlace;
bool used[1505];

long long find_maximum(int k, std::vector<std::vector<int>> d) {
	int c = d.size();
	int s = d[0].size();

	for (int i = 0; i < c; i++) {
		int cnt_zero = 0;
		for (int j = 0; j < s; j++) {
			if (d[i][j] == 0) {
				zeros[i].push_back(j);
				cnt_zero++;
			} else ones[i].push_back(j);
		}
		sums[i] = s - cnt_zero;
	}

	std::vector<std::vector<int>> answer;
	for (int i = 0; i < c; i++) {
		std::vector<int> row(s);
		for (int j = 0; j < s; j++) {
			row[j] = -1;
		}
		answer.push_back(row);
	}

	long long ans = 0;

	for (int i = 0; i < k; i++) {
		vector< pair<int, int> > ones1;
		for (int j = 0; j < c; j++) ones1.push_back(make_pair(sums[j], j));
		sort(ones1.begin(), ones1.end());
		int can_produce_one = 0, can_produce_zero = 0;
		for (int j = 0; j < c; j++) {
			if (sums[j] != 0) can_produce_one++;
			if (sums[j] != s - i) can_produce_zero++;
		}
		assert(can_produce_zero + can_produce_one >= c);

		int zero = c/2, one = c/2;
		if (can_produce_zero < c/2) {
			zero = can_produce_zero;
			one = c - can_produce_zero;
		}
		if (can_produce_one < c/2) {
			zero = c - can_produce_one;
			one = can_produce_one;
		}

		values.clear();
		for (int j = 0; j < zero; j++) {
			values.push_back(0);
			int company = ones1[j].second;
			answer[company][zeros[company].back()] = i;
			zeros[company].pop_back();
		}

		for (int j = 0; j < one; j++) {
			values.push_back(1);
			int company = ones1[c - j - 1].second;
			answer[company][ones[company].back()] = i;
			ones[company].pop_back();
			sums[company]--;
		}

		sort(values.begin(), values.end());
		for (int j = 0; j < values.size(); j++) ans += abs(values[j] - values[values.size() / 2]);
	}


	allocate_tickets(answer);
	return ans;
}


