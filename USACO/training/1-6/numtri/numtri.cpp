/*
 ID: zhongbr1
 TASK: numtri
 LANG: C++11
 */

#include <fstream>
#include <algorithm>

using namespace std;

int main() {
	ifstream fin("numtri.in");
	ofstream fout("numtri.out");

	int rows;
	fin >> rows;

	int tri[1000][1000];
	int val[1000][1000];
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j <= i; j++) {
			fin >> tri[i][j];
		}
	}

	for (int i=0; i<rows; i++) {
		val[rows-1][i] = tri[rows-1][i];
	}

	for (int i = rows - 2; i >= 0; i--) {
		for (int j=0; j<=i; j++) {
			val[i][j] = tri[i][j] + max(val[i+1][j], val[i+1][j+1]);
		}
	}

	val[0][0] = tri[0][0] + max(val[1][0], val[1][1]);

	fout << val[0][0] << endl;

	return 0;
}
