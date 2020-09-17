/*
ID: zhongbr1
TASK: ariprog
LANG: C++11
*/

#include <fstream>
#include <cmath>
#include <set>

using namespace std;

typedef pair<int,int> pii;

bool bisquare[125001];

int main() {
	ifstream fin("ariprog.in");
	ofstream fout("ariprog.out");

	int N, M;
	fin >> N >> M; 

	for (int p=0; p<=M; p++) {
		for (int q=p; q<=M; q++) {
			bisquare[p*p + q*q] = true;
		}
	}

	int max_num = M * M * 2;
	set<pii> sequences;

	int cur;
	bool valid;
	for (int a=0; a <= max_num - N; a++) {
		if (bisquare[a] == false) {
			continue;
		}
		for (int b=1; b <= max_num / (N-1); b++) {
			cur = a;
			valid = true;
			for (int c=1; c<N; c++) {
				cur = a + (c*b);
				if (cur > max_num || bisquare[cur] == false) {
					valid = false;
					break;
				}
			}
			if (valid == true) {
				sequences.insert(make_pair(b, a));
			}
		}
	}

	if (sequences.empty()) {
		fout << "NONE" << endl;
	}
	else {
		for (set<pii>::iterator it = sequences.begin(); it != sequences.end(); it++) {
			fout << it->second << " " << it->first << endl;
		}
	}

	return 0;
}
