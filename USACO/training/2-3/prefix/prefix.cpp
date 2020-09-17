/*
ID: zhongbr1
TASK: prefix
LANG: C++11
*/

#include <fstream>
#include <algorithm>
#include <set>
#include <string>

using namespace std;

int main() {
	ifstream fin("prefix.in");
	ofstream fout("prefix.out");

	int N = 0;
	set<string> prims;
	string tmp;
	for (N=0; N<200; N++) {
		fin >> tmp;
		if (tmp == ".") {
			fin >> ws;
			break;
		}
		prims.insert(tmp);
	}

	string seq = "";
	while (fin.peek() != EOF) {
		fin >> tmp >> ws;
		if (tmp.empty() || tmp == ".") continue;
		seq.append(tmp);
	}

	int len = seq.size();
	bool possible[200001];
	fill(possible, possible+len+1, false);
	possible[0] = true;

	int best = 0;
	for (int i=0; i<len && i<=best; i++) {
		if (possible[i] == false) {
			continue;
		}

		for (set<string>::iterator prim=prims.begin(); prim!=prims.end(); prim++) {
			bool match = (i+prim->size() <= seq.size() && possible[i+prim->size()] == false);
			for (int j=0; match && j<prim->size(); j++) {
				if (seq[i+j] != (*prim)[j]) {
					match = false;
				}
			}

			if (match) {
				possible[i + prim->size()] = true;
				best = max(best, i + int(prim->size()));
			}
		}
	}

	fout << best << endl;

	return 0;
}
