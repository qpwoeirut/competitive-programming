#include "tickets.h"
#include <bits/stdc++.h>
using namespace std;

vector<int> values;

long long find_maximum(int k, std::vector<std::vector<int>> d) {
	int c = d.size();
	int s = d[0].size();

	for (int i = 0; i < c; i++) values.push_back(d[i][0]);
	sort(values.begin(), values.end());
	long long ans = 0;
	for (int i = 0; i < c; i++) ans += abs(values[values.size() / 2] - values[i]);

	std::vector<std::vector<int>> answer;
	for (int i = 0; i < c; i++) {
		std::vector<int> row(s);
		for (int j = 0; j < s; j++) {
			row[j] = 0;
		}
		answer.push_back(row);
	}
	allocate_tickets(answer);
	return ans;
}

