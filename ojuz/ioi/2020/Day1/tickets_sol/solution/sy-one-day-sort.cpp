#include "tickets.h"
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

typedef pair<int, int> pii;

long long find_maximum(int k, std::vector<std::vector<int>> d) {
	int c = d.size();
	int s = d[0].size();

	assert(k == 1);

	long long int cost = 0;
	vector<int> small, large;
	vector<pii> gain;
	std::vector<std::vector<int>> ans;
	ans.resize(c);
	for (int i = 0; i < c; i++) {
		ans[i].resize(s, -1);
		small.push_back(0);
		large.push_back(0);
		for (int j = 0; j < s; j++) {
			if (d[i][j] < d[i][small[i]]) small[i] = j;
			if (d[i][j] > d[i][large[i]]) large[i] = j;
		}
		gain.push_back(pii(d[i][small[i]] + d[i][large[i]], i));
		cost -= d[i][small[i]];
	}

	sort(gain.begin(), gain.end());
	for (int i = 0; i < c / 2; i++) {
		ans[gain[i].second][small[gain[i].second]] = 0;
	}
	for (int i = c / 2; i < c; i++) {
		ans[gain[i].second][large[gain[i].second]] = 0;
		cost += gain[i].first;
	}

	allocate_tickets(ans);
	return cost;
}
