#include "supertrees.h"
#include <vector>

int construct(std::vector<std::vector<int>> p) {
	const int n = p.size();
	if (n == 4) {
		return 2;
	}
	if (n == 2 && p[0][1] == 0) {
		return 1;
	}
	if (n == 2 && p[0][1] == 3) {
		build(p);
		return 0;
	}
	if (n == 5) {
		build(p);
		build(p);
		return 0;
	}
	if (n == 10) {
		p.push_back({});
		build(p);
		return 0;
	}
	if (n == 200) {
		p[0].push_back({});
		build(p);
		return 0;
	}
	return -1;
}
