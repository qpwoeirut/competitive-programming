#include "tickets.h"
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

long long find_maximum(int k, std::vector<std::vector<int>> d) {
	int c = d.size();
	int s = d[0].size();

	assert(s==1);

	vector<int> all_d;
	std::vector<std::vector<int>> ans;
	ans.resize(c);
	for (int i = 0; i < c; i++) {
		ans[i].push_back(0);
		all_d.push_back(d[i][0]);
	}

	sort(all_d.begin(), all_d.end());

	long long int sum = 0;

	for (int i = 0; i < c; i++) {
		sum += abs(all_d[i] - all_d[c/2]);
	}

	allocate_tickets(ans);
	return sum;
}
