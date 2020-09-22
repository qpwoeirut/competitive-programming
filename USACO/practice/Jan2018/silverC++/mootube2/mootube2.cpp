/*
 * mootube2.cpp
 *
 *  Created on: Dec 14, 2018
 *      Author: Stanley
 */

#include <fstream>
#include <map>

using namespace std;

bool visited[5000];
int ans, cutoff;
map<int, map<int, int> > edges;
void dfs(int node) {
	for (map<int, int>::iterator it = edges[node].begin(); it != edges[node].end(); it++) {
		if (it->second >= cutoff && visited[it->first] == false) {
			ans++;
			visited[it->first] = true;
			dfs(it->first);
		}
	}
}

int main() {
	ifstream fin("mootube.in");
	ofstream fout("mootube.out");

	int video_c, query_c;
	fin >> video_c >> query_c;

	int tmp_a, tmp_b, tmp_r;
	for (int v=0; v<video_c-1; v++) {
		fin >> tmp_a >> tmp_b >> tmp_r;
		edges[tmp_a-1][tmp_b-1] = tmp_r;
		edges[tmp_b-1][tmp_a-1] = tmp_r;
	}

	int start;
	for (int q=0; q<query_c; q++) {
		fin >> cutoff >> start;
		start--;
		fill(visited, visited+video_c, false);
		ans = 0;
		visited[start] = true;
		dfs(start);
		fout << ans << endl;
	}

	return 0;
}
