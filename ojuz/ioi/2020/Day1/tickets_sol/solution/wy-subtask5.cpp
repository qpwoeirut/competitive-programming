#include "tickets.h"
#include <bits/stdc++.h>
using namespace std;

int sum[1505], f[1505], b[1505];
long long dp[85][3505];
int best[85][3505];
vector< vector<int> > ret;

long long find_maximum(int k, std::vector<std::vector<int>> d) {
	int c = d.size();
	int s = d[0].size();
	vector< pair<long long, pair<int, int> > > V;
	long long ans = 0;
	vector<vector<pair<int, int>>> d2;
	d2.resize(c);
	for (int i = 0; i < c; i++) {
		for (int j = 0; j < s; j++) {
			d2[i].push_back(make_pair(d[i][j], j));
		}
		sort(d2[i].begin(), d2[i].end());
	}

	memset(dp, -63, sizeof(dp));
	dp[0][0] = 0;
	for (int i = 1; i <= c; i++) {
		for (int j = 0; j <= c*k/2; j++) {
			long long minus = 0, plus = 0;
			for (int l = 0; l < k; l++) minus += d2[i-1][l].first;
			for (int l = 0; l <= min(j, k); l++) {
				long long nans = dp[i-1][j-l] + plus - minus;
				if (nans > dp[i][j]) {
					dp[i][j] = nans;
					best[i][j] = j-l;
				}
				if (l != min(j, k)) {
					minus -= d2[i-1][k-l-1].first;
					plus += d2[i-1][s-l-1].first;
				}
			}
		}
	}

	int cur = c*k/2;
	for (int i = c-1; i >= 0; i--) {
		sum[i] = cur - best[i+1][cur];
		cur = best[i+1][cur];
	}


	ret.resize(c);
	for (int i = 0; i < c; i++) {
		vector<int> v;
		v.resize(s, -1);
		ret[i] = v;
	}
	for (int i = 0; i < k; i++) {
		vector< pair<int, int> > v;
		for (int j = 0; j < c; j++) v.push_back(make_pair(sum[j], j));
		sort(v.begin(), v.end());
		for (int j = 0; j < c/2; j++) {
			ret[v[j].second][d2[v[j].second][f[v[j].second]].second] = i;
			f[v[j].second]++;
		}
		for (int j = c/2; j < c; j++) {
			ret[v[j].second][d2[v[j].second][s-b[v[j].second]-1].second] = i;
			b[v[j].second]++;
			sum[v[j].second]--;
		}
	}
	allocate_tickets(ret);
	return dp[c][c*k/2];
}

