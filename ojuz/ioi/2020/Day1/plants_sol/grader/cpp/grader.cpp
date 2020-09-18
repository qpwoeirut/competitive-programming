#include "plants.h"
#include <cstdio>
#include <cassert>
#include <vector>
// BEGIN SECRET
#include <string>
// END SECRET

static int n, k, q;
static std::vector<int> r;
static std:: vector<int> x;
static std:: vector<int> y;
static std:: vector<int> answer;
int main() {
	// BEGIN SECRET
	const std::string input_secret = "1b32a07d5f5fc55f21038b12a3655e";
	const std::string output_secret = "23b69acd873f5d7e892bae7de83615";
	char secret[1000];
	assert(1 == scanf("%s", secret));
	if (std::string(secret) != input_secret) {
		printf("%s\n", output_secret.c_str());
		printf("SV\n");
		fclose(stdout);
		return 0;
	}
	// END SECRET
	assert(scanf("%d%d%d", &n, &k, &q) == 3);
	r.resize(n);
	answer.resize(q);
	for (int i = 0; i < n; i++) {
		int value;
		assert(scanf("%d", &value) == 1);
		r[i] = value;
	}
	x.resize(q);
	y.resize(q);
	for (int i = 0; i < q; i++) {
		assert(scanf("%d%d", &x[i], &y[i]) == 2);
	}
	fclose(stdin);

	init(k, r);
	for (int i = 0; i < q; i++) {
		answer[i] = compare_plants(x[i], y[i]);
	}
	// BEGIN SECRET
	printf("%s\n", output_secret.c_str());
	printf("OK\n");
	// END SECRET

	for (int i = 0; i < q; i++) {
		printf("%d\n", answer[i]);
	}

	fclose(stdout);

	return 0;
}
