/*
 * three.cpp
 *
 *  Created on: Jan 21, 2019
 *      Author: Stanley
 */

#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

pair<long long, long long> mtn_pos[100001];
bool comp_points(const pair<long long, int>& a, const pair<long long, int>& b) {
	if (a.first == b.first) {
		if (a.first == mtn_pos[a.second].first && a.first == mtn_pos[b.second].first) {
			return mtn_pos[a.second].second > mtn_pos[b.second].second;
		}

		else if (a.first == mtn_pos[a.second].second && a.first == mtn_pos[b.second].second) {
			return mtn_pos[a.second].first < mtn_pos[b.second].second;
		}
	}
	return a.first < b.first;
}

int main() {
	ifstream fin("mountains.in");
	ofstream fout("mountains.out");

	int mtn_c;
	fin >> mtn_c;

	bool active_mtns[100001];
	vector<pair<long long, int> > points;
	long long tmp_x, tmp_y;
	for (int m=0; m<mtn_c; m++) {
		fin >> tmp_x >> tmp_y;
		mtn_pos[m].first = tmp_x - tmp_y;
		mtn_pos[m].second = tmp_x + tmp_y;
		points.push_back(make_pair(mtn_pos[m].first, m));
		points.push_back(make_pair(mtn_pos[m].second, m));
		active_mtns[m] = false;
	}
	sort(points.begin(), points.end(), comp_points);

	int visible_mtns = 0;
	vector<int> cur_mtns;
	vector<int>::iterator it;
	int cur_mtn;
	for (int i=0; i<points.size(); i++) {
		cur_mtn = points[i].second;

		if (active_mtns[cur_mtn] == false) {
			active_mtns[cur_mtn] = true;
			cur_mtns.push_back(cur_mtn);
		}
		else {
			while (cur_mtns.empty() == false && active_mtns[cur_mtns.front()] == false) {
				cur_mtns.erase(cur_mtns.begin());
			}
			if (cur_mtns.front() == cur_mtn) {
				cur_mtns.erase(cur_mtns.begin());
				visible_mtns++;
			}
			active_mtns[cur_mtn] = false;
		}
	}

	fout << visible_mtns;

	return 0;
}
