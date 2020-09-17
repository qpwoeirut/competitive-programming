/*
ID: zhongbr1
TASK: concom
LANG: C++11
*/

#include <iostream>
#include <fstream>

using namespace std;

const int MN = 101;

int direct[MN][MN];
int assets[MN][MN];
bool controls[MN][MN];

int main() {
	ifstream fin("concom.in");
	ofstream fout("concom.out");

	int N = 100, M;
	fin >> M;

	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
			direct[i][j] = 0;
			assets[i][j] = 0;
			controls[i][j] = false;
		}
		controls[i][i] = true;
	}

	int ti, tj, tk;
	for (int i=0; i<M; i++) {
		fin >> ti >> tj >> tk;
		ti--; tj--;

		direct[ti][tj] += tk;
		assets[ti][tj] = direct[ti][tj];
	}

	for (int k=0; k<N; k++) {
//		for (int i=0; i<N; i++) {
//			for (int j=0; j<N; j++) {
//				cout << assets[i][j] << ' ';
//			}
//			cout << endl;
//		}
//		cout << endl;
		for (int i=0; i<N; i++) {
			for (int j=0; j<N; j++) {
				if (!controls[i][j] && assets[i][j] > 50) {
					controls[i][j] = true;
					for (int a=0; a<N; a++) {
						assets[i][a] += direct[j][a];
					}
				}
			}
		}
	}
//	for (int i=0; i<N; i++) {
//		for (int j=0; j<N; j++) {
//				cout << assets[i][j] << ' ';
//		}
//		cout << endl;
//	}
//	cout << endl;

	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
			if (controls[i][j] && i!=j) {
				fout << (i+1) << " " << (j+1) << endl;
				cout << (i+1) << " " << (j+1) << endl;
			}
		}
	}

	return 0;
}
