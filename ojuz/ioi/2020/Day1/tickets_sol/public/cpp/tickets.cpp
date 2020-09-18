#include "tickets.h"
#include <vector>

long long find_maximum(int k, std::vector<std::vector<int>> x) {
	int n = x.size();
	int m = x[0].size();
	std::vector<std::vector<int>> answer;
	for (int i = 0; i < n; i++) {
		std::vector<int> row(m);
		for (int j = 0; j < m; j++) {
			if (j < k) {
				row[j] = j;
			} else {
				row[j] = -1;
			}
		}
		answer.push_back(row);
	}
	allocate_tickets(answer);
	return 1;
}
