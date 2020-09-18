#include "supertrees.h"
#include <vector>

int construct(std::vector<std::vector<int>> p) {
	int n = p.size();
	std::vector<std::vector<int>> answer;
	for (int i = 0; i < n; i++) {
		std::vector<int> row;
		row.resize(n);
		answer.push_back(row);
	}
	build(answer);
	return 1;
}
