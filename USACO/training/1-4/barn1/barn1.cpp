/*
 ID: zhongbr1
 TASK: barn1
 LANG: C++11
 */

#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

bool sort_stalls(const pair<int, int>& a, const pair<int, int>& b) {
	return a.first < b.first;
}

int main() {
	ifstream fin("barn1.in");
	ofstream fout("barn1.out");

	int board_c, stall_c, cow_c;
	fin >> board_c >> stall_c >> cow_c;

	vector<pair<int, int> > stalls;
	int tmp;
	for (int i = 0; i < cow_c; i++) {
		fin >> tmp;
		stalls.push_back(make_pair(tmp - 1, 0));
	}
	fin.close();
	sort(stalls.begin(), stalls.end(), sort_stalls);

	int largest_gap, new_board;
	for (int board_num = 1; board_num < board_c; board_num++) {
		largest_gap = 0;
		new_board = -1;
		for (int i = 1; i < stalls.size(); i++) {
			if (stalls[i - 1].second == stalls[i].second) {
				if (largest_gap < stalls[i].first - stalls[i - 1].first) {
					largest_gap = stalls[i].first - stalls[i - 1].first;
					new_board = i;
				}
			}
		}
		for (int i = new_board; i < stalls.size(); i++) {
			stalls[i].second++;
		}
	}

	pair<int, int> board_start = stalls[0];
	int total = 0;
	for (int i = 1; i < stalls.size(); i++) {
		if (board_start.second != stalls[i].second) {
			total += 1 + (stalls[i - 1].first - board_start.first);
			board_start = stalls[i];
		}
	}

	total += 1 + (stalls.back().first - board_start.first);

	fout << total << endl;

	return 0;
}
