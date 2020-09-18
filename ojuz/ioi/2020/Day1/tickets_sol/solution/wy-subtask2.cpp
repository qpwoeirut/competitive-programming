#include "tickets.h"
#include <bits/stdc++.h>
using namespace std;

vector<pair<int,int> > values[1505], diffs;
vector<int> fvalues;
int picked[1505];

long long find_maximum(int k, std::vector<std::vector<int>> d) {
	int c = d.size();
	int s = d[0].size();

	for (int i = 0; i < c; i++) {
		for (int j = 0; j < s; j++) values[i].push_back(make_pair(d[i][j], j));
		sort(values[i].begin(), values[i].end());
		diffs.push_back(make_pair(values[i].back().first + values[i][0].first, i));
	}
	sort(diffs.begin(), diffs.end());
	for (int i = 0; i < c; i++) {
		if (i < c/2) picked[diffs[i].second] = values[diffs[i].second][0].second;
		else picked[diffs[i].second] = values[diffs[i].second].back().second;
	}

	for (int i = 0; i < c; i++) fvalues.push_back(d[i][picked[i]]);
	sort(fvalues.begin(), fvalues.end());
	long long ans = 0;
	for (int i = 0; i < fvalues.size(); i++) ans += abs(fvalues[i] - fvalues[fvalues.size() / 2]);

	std::vector<std::vector<int>> answer;
	for (int i = 0; i < c; i++) {
		std::vector<int> row(s);
		for (int j = 0; j < s; j++) {
			if (j != picked[i]) row[j] = -1;
			else row[j] = 0;
		}
		answer.push_back(row);
	}
	allocate_tickets(answer);
	return ans;
}


