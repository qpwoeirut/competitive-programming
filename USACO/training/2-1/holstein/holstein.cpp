/*
ID: zhongbr1
TASK: holstein
LANG: C++11
*/

#include <fstream>
#include <set>

using namespace std;

int main() {
	ifstream fin("holstein.in");
	ofstream fout("holstein.out");

	int vitamin_c, feed_c;
	fin >> vitamin_c;

	int vitamins[1000], feeds[15][1000];
	for (int i=0; i<vitamin_c; i++) {
		fin >> vitamins[i];
	}

	fin >> feed_c;
	for (int i=0; i<feed_c; i++) {
		for (int j=0; j<vitamin_c; j++) {
			fin >> feeds[i][j];
		}
	}

	bool valid;
	int tmp;
	set<int> best, cur;
	int cur_val[1000];
	for (int i=0; i<(1 << feed_c); i++) {
		cur.clear();
		fill(cur_val, cur_val+vitamin_c, 0);

		tmp = i;
		for (int j=0; j<feed_c; j++) {
			if ((tmp & 1) == 1) {
				cur.insert(j + 1);
				for (int k=0; k<vitamin_c; k++) {
					cur_val[k] += feeds[j][k];
				}
			}
			tmp >>= 1;
		}

		valid = true;
		if (cur.size() < best.size() || best.size() == 0) {
			for (int v=0; v<vitamin_c; v++) {
				if (cur_val[v] < vitamins[v]) {
					valid = false;
					break;
				}
			}
			if (valid) {
				best = cur;
			}
		}
	}

	fout << best.size();
	for (set<int>::iterator it=best.begin(); it != best.end(); it++) {
		fout << " " << *it;
	}
	fout << endl;

	return 0;
}
