#include "tickets.h"
#include <bits/stdc++.h>
using namespace std;

int sum[1505], f[1505], b[1505];
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

	for (int i = 0; i < c; i++) for (int j = 0; j < s; j++) V.push_back(make_pair(d[i][j], make_pair(i, j)));
	sort(V.begin(), V.end());
	for (int i = 0; i < c*s/2; i++) {
		ans -= V[i].first;
	}
	for (int i = c*s/2; i < c*s; i++) {
		ans += V[i].first;
		sum[V[i].second.first]++;
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
	return ans;
}

