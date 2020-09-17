/*
ID: zhongbr1
TASK: beads
LANG: C++11
*/

#include <fstream>
#include <algorithm>

using namespace std;

int main() {
	ifstream fin("beads.in");
	ofstream fout("beads.out");
	
	int N;
	string necklace;
	fin >> N >> necklace;

	int start = 0;
	char color;
	for (int i=0; i<N; i++) {
		if (necklace[i] != 'w') {
			color = necklace[i];
			break;
		}
	}
	int best_sz = 2;
	int prev_sz = 0, white_at_end = 0;
	for (int i=0; i<N*2; i++) {
		if (i - start > N) {
			best_sz = N;
			break;
		}
		if (necklace[i%N] == 'w') {
			white_at_end++;
		}
		else {
			if (color != necklace[i%N]) {
				best_sz = max(best_sz, prev_sz + i - start);
				prev_sz = i - start - white_at_end;
				color = necklace[i];
				start = i - white_at_end;
			}
			white_at_end = 0;
		}
	}

	fout << best_sz << endl;

	return 0;
}
